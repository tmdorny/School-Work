from socket import *
from EXPO import expo

#PA2 CS5490 Tim Dorny u0829896

try:
    server_name = ''
    server_port = 2114
    client_socket = socket(AF_INET, SOCK_STREAM)
    client_socket.connect((server_name,server_port))
    alice_secret = expo(1907, 160011, 784313)
    client_socket.send(str(alice_secret))
    from_bob = int(client_socket.recv(2048))
    shared_secret = expo(from_bob, 160011, 784313)
    with open('pa2-alice output', 'w') as f:
        f.write('Alice sends {0} to Bob.\n'.format(alice_secret))
        f.write('Alice computes shared secret: {0}.\n'.format(shared_secret))
except KeyboardInterrupt:
    client_socket.close()
