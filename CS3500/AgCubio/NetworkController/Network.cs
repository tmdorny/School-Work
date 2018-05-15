using AgCubio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace AgCubio
{
    public static class Network
    {
        public static Socket Connect_to_Server(Action<State> callback_function, string hostname)
        {
            TcpClient client = new TcpClient(hostname, 11000);
            Socket socket = new Socket(SocketType.Stream, ProtocolType.Tcp);
            State myState = new State(callback_function, socket);
            socket.BeginConnect(hostname, 11000, new AsyncCallback(Connected_to_Server), myState);
            
            return socket;
        }

        public static void Connected_to_Server(IAsyncResult state_in_an_ar_object)
        {
            
            State StateObject = state_in_an_ar_object.AsyncState as State;
            Socket socket = StateObject.Socket;

            // Call Callback Function
            StateObject.Callback(StateObject);

            StateObject.Bytes = new byte[1024];
            socket.BeginReceive(StateObject.Bytes, 0, 1024, new SocketFlags(), new AsyncCallback(ReceiveCallback), StateObject);
            
            
        }

        public static void ReceiveCallback(IAsyncResult state_in_an_ar_object)
        {
            State StateObject = state_in_an_ar_object.AsyncState as State;
            int BytesRecieved = StateObject.Socket.EndReceive(state_in_an_ar_object);
            //Console.Write(BytesRecieved);
            if (BytesRecieved == 0)
            {
                // Connection has been closed.
            }
            else
            {
                //Console.Write(BytesRecieved);
                Socket socket = StateObject.Socket;

                // Call Callback Function
                StateObject.Callback(StateObject);
            }
        }

        public static void i_want_more_data(State state)
        {
            Socket socket = state.Socket;

            socket.BeginReceive(state.Bytes, 0, 1024, new SocketFlags(), new AsyncCallback(ReceiveCallback), state);
        }

        public static void Send(Socket socket, String data)
        {
            if (socket != null)
            {
                byte[] toBytes = Encoding.ASCII.GetBytes(data);
                //Console.Write(data);
                socket.BeginSend(toBytes, 0, toBytes.Length, new SocketFlags(), new AsyncCallback(SendCallBack), new State(null, socket));
            }
        }

        public static void SendCallBack(IAsyncResult state_in_an_ar_object)
        {
            State StateObject = (State) state_in_an_ar_object.AsyncState;
            StateObject.Socket.EndSend(state_in_an_ar_object);
            //Console.Out.WriteLine("DATA SENT");
        }
    }
}
