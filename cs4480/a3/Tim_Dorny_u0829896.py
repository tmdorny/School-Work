# imports taken from example_switch_13.py
from ryu.base import app_manager
from ryu.controller import ofp_event
from ryu.controller.handler import CONFIG_DISPATCHER, MAIN_DISPATCHER
from ryu.controller.handler import set_ev_cls
from ryu.ofproto import ofproto_v1_3
from ryu.lib.packet import packet
from ryu.lib.packet import ethernet
from ryu.lib.packet import arp
from ryu.lib.packet import ether_types

# tells controller which server to direct traffic to
next_request = 5

class LoadBalancingSwitch(app_manager.RyuApp):
    OFP_VERSIONS = [ofproto_v1_3.OFP_VERSION]
    # From simple_switch.py
    def __init__(self, *args, **kwargs):
        super(LoadBalancingSwitch, self).__init__(*args, **kwargs)
        self.mac_to_port = {}
        
    #from example_switch_13.py
    @set_ev_cls(ofp_event.EventOFPSwitchFeatures, CONFIG_DISPATCHER)
    def switch_features_handler(self, ev):
        datapath = ev.msg.datapath
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        # install table-miss flow entry
        #
        # We specify NO BUFFER to max_len of the output action due to
        # OVS bug. At this moment, if we specify a lesser number, e.g.,
        # 128, OVS will send Packet-In with invalid buffer_id and
        # truncated packet data. In that case, we cannot output packets
        # correctly.  The bug has been fixed in OVS v2.1.0.
        match = parser.OFPMatch()
        actions = [parser.OFPActionOutput(ofproto.OFPP_CONTROLLER,
                                          ofproto.OFPCML_NO_BUFFER)]
        self.add_flow(datapath, 0, match, actions)
    # adds initial table-miss flow
    def add_flow(self, datapath, priority, match, actions, buffer_id=None):
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS,
                                             actions)]
        if buffer_id:
            mod = parser.OFPFlowMod(datapath=datapath, buffer_id=buffer_id,
                                    priority=priority, match=match,
                                    instructions=inst)
        else:
            mod = parser.OFPFlowMod(datapath=datapath, priority=priority,
                                    match=match, instructions=inst)
        datapath.send_msg(mod)
        
    @set_ev_cls(ofp_event.EventOFPPacketIn, MAIN_DISPATCHER)
    #The first argument of the decorator calls this function everytime 
    #a packet_in message is received. The second argument indicates the switch state.
    def _packet_in_handler(self, ev):
        global next_request
        msg = ev.msg # Object representing a packet_in data structure.
        datapath = msg.datapath # Switch Datapath ID
        ofproto = datapath.ofproto # OpenFlow Protocol version the entities negotiated. In our case OF1.3
        parser = datapath.ofproto_parser
        in_port = msg.match['in_port']
        print('Packet received in port: %s\n' %in_port)

        pkt = packet.Packet(msg.data) 
        eth = pkt.get_protocol(ethernet.ethernet) 
        arp_pkt = pkt.get_protocol(arp.arp)
        
        # if received packet is an ARP
        if arp_pkt is not None:
            # get dst_ip and dst_mac AND src_ip and src_mac
            dst_ip = arp_pkt.dst_ip
            dst_mac = arp_pkt.dst_mac # 0
            src_ip = arp_pkt.src_ip
            src_mac = arp_pkt.src_mac
            print('ARP INFO: sip: %s | smac: %s | dip: %s | dmac: %s\n' %(src_ip, src_mac, dst_ip, dst_mac))
            # arp to server(s)
            if dst_ip == '10.0.0.10':
                print('dst match')
                if next_request == 5:
                    # direct to h5
                    print('directing to h5')
                    dst_mac = '00:00:00:00:00:05'
                    dst_ip = '10.0.0.5'
                    server_port = 5
                    next_request = 6
                else:
                    # direct to h6
                    print('directing to h6')
                    dst_mac = '00:00:00:00:00:06'
                    dst_ip = '10.0.0.6'
                    server_port = 6
                    next_request = 5
                    
                # add flows 
                # client to server
                match = parser.OFPMatch(in_port=in_port, ipv4_dst='10.0.0.10', eth_type=0x800)
                actions = [parser.OFPActionSetField(ipv4_dst=dst_ip), parser.OFPActionOutput(server_port)]
                inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS, actions)]
                mod = parser.OFPFlowMod(datapath=datapath, priority=1, match=match, instructions=inst)
                datapath.send_msg(mod)        
                
                # send arp reply to client
                actions = [parser.OFPActionOutput(ofproto.OFPP_IN_PORT)]
                arp_reply = packet.Packet()
                arp_reply.add_protocol(ethernet.ethernet(ethertype=ether_types.ETH_TYPE_ARP, 
                                  src=dst_mac, dst=src_mac))
                arp_reply.add_protocol(arp.arp(opcode=arp.ARP_REPLY, src_ip='10.0.0.10', src_mac=dst_mac,
                                  dst_ip=src_ip, dst_mac=src_mac))
                arp_reply.serialize()
                out = parser.OFPPacketOut(datapath=datapath, buffer_id=ofproto.OFP_NO_BUFFER,
                                  in_port=in_port, actions=actions, data=arp_reply.data)
                datapath.send_msg(out)             
            #arp from server
            else:
                # send arp reply to server
                if dst_ip == '10.0.0.1':
                    dst_mac = '00:00:00:00:00:01'
                    out_port = 1
                elif dst_ip == '10.0.0.2':
                    dst_mac = '00:00:00:00:00:02'
                    out_port = 2
                elif dst_ip == '10.0.0.3':
                    dst_mac = '00:00:00:00:00:03'
                    out_port = 3
                elif dst_ip == '10.0.0.4':
                    dst_mac = '00:00:00:00:00:04'
                    out_port = 4
                    
                # server to client flow
                match = parser.OFPMatch(in_port=in_port, ipv4_dst=dst_ip, eth_type=0x800)
                actions = [parser.OFPActionSetField(ipv4_src='10.0.0.10'), parser.OFPActionOutput(out_port)]
                inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS, actions)]
                mod = parser.OFPFlowMod(datapath=datapath, priority=1, match=match, instructions=inst)
                datapath.send_msg(mod)
                
                # send arp reply to server
                actions = [parser.OFPActionOutput(ofproto.OFPP_IN_PORT)]
                arp_reply = packet.Packet()
                arp_reply.add_protocol(ethernet.ethernet(ethertype=ether_types.ETH_TYPE_ARP, 
                                  src=dst_mac, dst=src_mac))
                arp_reply.add_protocol(arp.arp(opcode=arp.ARP_REPLY, src_ip=dst_ip, src_mac=dst_mac,
                                  dst_ip=src_ip, dst_mac=src_mac))
                arp_reply.serialize()
                out = parser.OFPPacketOut(datapath=datapath, buffer_id=ofproto.OFP_NO_BUFFER,
                                  in_port=in_port, actions=actions, data=arp_reply.data)
                datapath.send_msg(out)
