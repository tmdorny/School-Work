from socket import *
from EXPO import expo

#PA2 CS5490 Tim Dorny u0829896

# Set up socket
server_port = 2114
server_socket = socket(AF_INET,SOCK_STREAM)
server_socket.bind(('',server_port))
server_socket.listen(1)
print 'Bob waiting for contact from alice...'
try:
    connection_socket, addr = server_socket.accept()
except:
    print "Connection Error..."
    server_socket.close()
    # Recieve Data
try:
    bob_secret = expo(1907, 12067, 784313)
    from_alice = int(connection_socket.recv(2048))
    connection_socket.send(str(bob_secret))
    shared_secret = expo(from_alice, 12067, 784313)
    with open('pa2-bob output', 'w') as f:
        f.write('Bob sends {0} to Alice\n'.format(bob_secret))
        f.write('Bob computes shared secret: {0}.\n'.format(shared_secret)) 
except KeyboardInterrupt:
    server_socket.close()
