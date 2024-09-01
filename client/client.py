import socket

clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientsocket.connect(('localhost', 3000))

for i in range(10):
    
    clientsocket.send(b'HELLO WORLD')
    data = clientsocket.recv(1024)
    print(data)

clientsocket.send(b'exit')
data = clientsocket.recv(1024)
print(data)

clientsocket.close()
