import socket
import sys
import time

host, port = '', 9998
data = 'lantianishere'

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((host, port))
    sock.sendall(data.encode())

    received = sock.recv(1024).decode()
    time.sleep(10)

print("input", data)
print('output', received)
