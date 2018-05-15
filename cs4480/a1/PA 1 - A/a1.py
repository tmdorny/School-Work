from socket import *
from urlparse import urlparse
import threading
import sys


def a(connectionSocket):
    '''
    Function that handles incoming connections to the proxy server
    '''
    gotRequest = 0
    connectionClosed = 0
    # Dictionary to store any headers passed
    headers = {}
    # Recieve Data
    while 1:
        request = connectionSocket.recv(2048)
        if request == "\r\n":
            break
        elif gotRequest == 0:
            try:
                method,url,http = request.split()
                gotRequest = 1
            except:
                connectionSocket.send("HTTP/1.0 400 Malformed request\r\n\r\n")
                connectionSocket.close()
                connectionClosed = 1
                break
        else:
            try:
                headerName,headerValue = request.split()
                if headerName.endswith(":"):
                    headers[headerName] = headerValue
                else:
                    connectionSocket.send("HTTP/1.0 400 Malformed request\r\n\r\n")
                    connectionSocket.close()
                    connectionClosed = 1
                    break
            except:
                connectionSocket.send("HTTP/1.0 400 Malformed request\r\n\r\n")
                connectionSocket.close()
                connectionClosed = 1
                break
    if connectionClosed == 1:
        return
    if method != 'GET':
        connectionSocket.send("HTTP/1.0 501 Not implemented\r\n\r\n")
        connectionSocket.close()
        return
    #parsed URL
    purl = urlparse(url)
    remotePort = 80
    if purl.port:
        remotePort = purl.port
    if headers.has_key('Connection:'):
        if headers['Connection:'] != 'close':
            headers['Connection:'] = 'close'
    # Add host to dict if not provided by client
    if not headers.has_key('Host:'):
        headers['Host:'] = purl.hostname
    # Build request string
    # main request first,
    requestToSend = method + ' ' + purl.path + ' ' + http + '\r\n'
    # followed by all of the headers
    for key in headers:
        requestToSend += key + ' ' + headers[key] + '\r\n'
    # final carriage return
    requestToSend += '\r\n'

    # send request to remote server
    remoteSocket = socket(AF_INET, SOCK_STREAM)
    try:
        remoteSocket.connect((purl.hostname,remotePort))
        remoteSocket.send(requestToSend)
        remoteReturn = ''
        while 1:
            remoteRecv = remoteSocket.recv(2048)
            if remoteRecv == "":
                break
            else:
                remoteReturn += remoteRecv
    except:
        connectionSocket.send("HTTP/1.0 400 Malformed request\r\n\r\n")
        connectionSocket.close()
        return
    connectionSocket.send(remoteReturn)
    connectionSocket.close()
    return;


serverPort = input('Enter port number:')
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(1)
while 1:
    print 'Server on port', serverPort, 'waiting for connection...'
    try:
        connectionSocket, addr = serverSocket.accept()
    except:
        print "Connection Error..."
        sys.exit(-1)
    connectionThread = threading.Thread(target=a, args=(connectionSocket,))
    connectionThread.start()