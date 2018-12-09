from socket import *

host = '192.168.2.16'
port = 12345
addr = (host,port)
bufsize = 1024

client = socket(AF_INET,SOCK_STREAM)
client.connect(addr)

while True:
    data = input(">>> ")
    if not data:break
    client.send(data.encode())
    data = client.recv(bufsize)
    print(data.decode())

client.close()
