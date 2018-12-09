#!/usr/bin/python

import socketserver
import threading
import socket
import time

class MyTCPHandle(socketserver.BaseRequestHandler):
    def handle(self):
        # self.request is the TCP socket for the remote client
        p = self.request.recv(1024)
        while p:
            print(p)
            p = self.request.recv(1024)
            # print the client_address
        print("connected by", self.client_address, threading.current_thread())
        data = self.data.decode() + str(threading.current_thread)
        self.request.sendall(data.encode())

class myTCPHandle(socketserver.StreamRequestHandler):
    def handle(self):
        while self.rfile.readline().strip():
            self.data = self.rfile.readline().strip()
            print("connected by", self.client_address, threading.current_thread(), self.data)
            self.wfile.write(self.data)

class threadedtcpserver(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

def client(ip, port, message):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((ip, port))
        data = message + '\n'
        sock.sendall(data.encode())
        response = sock.recv(1024).decode()
        print('response', response)
        time.sleep(10)

def client_slow(ip, port):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((ip, port))
        for i in range(1000):
            sock.send(str(i).encode())
            print(i)
            time.sleep(1)

if __name__ == "__main__":
    host, port = '', 9998
    
    server = threadedtcpserver((host, port), MyTCPHandle)
    with server:
        ip, port = server.server_address
        server.serve_forever()
        # slow_thread = threading.Thread(target = client_slow, args = (ip, port, ))
        # slow_thread.start()
        # client(ip, port, "fuck you 1")
        # client(ip, port, "fuck you 2")
        # client(ip, port, "fuck you 3")
