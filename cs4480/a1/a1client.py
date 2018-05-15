from socket import *
serverName = ''
serverPort = 2114
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName,serverPort))
request = raw_input('Enter HTTP request:')
fullRequest = 'GET ' + request + ' HTTP/1.0'
clientSocket.send(fullRequest)
returnedRequest = clientSocket.recv(2048)
print 'Got: ', returnedRequest, 'from sever lel'
clientSocket.close()
x
