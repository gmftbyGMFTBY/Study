import socket
s = socket.socket()

host = "www.baidu.com"
port = 1234
s.connect((host,port))
print(s.rev(1024))
