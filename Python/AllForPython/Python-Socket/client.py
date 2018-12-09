#!/usr/bin/python


'''
import socket
import threading

host = '127.0.0.1'
port = 50008

def get_msg(conn):
    while True:
        data = conn.recv(1024)
        print(data.decode('utf8'))

def send_msg(conn):
    while True:
        data = input().encode('utf8')
        conn.sendall(data)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((host, port))
    print('connect to', (host, port))
    get_thread = threading.Thread(target = get_msg, args = (s,))
    send_thread = threading.Thread(target = send_msg, args = (s,))
    get_thread.start()
    send_thread.start()
    get_thread.join()
    send_thread.join()
    print('over!')
'''
import sys
import select
from socket import *
from time import ctime

HOST = 'localhost'
PORT = 50022
size = 1024
addr = (HOST,PORT)

client = socket(AF_INET,SOCK_STREAM)
client.connect(addr)
raw_input = [sys.stdin,client]

running = 1

while running:
    print('>')
    readyInput,readyOupt,readyException = select.select(raw_input,[],[])
   
    for c in readyInput:

        if c == client:
            data = client.recv(size).decode()
            if data == '^c':
                running = 0
                print('server exist')
                c.close()
                print('client is over')
                break
            print(data)
        else:
            cliMsg = input()
            if cliMsg == "exit": 
                client.shutdown(SHUT_WR)
                exit()
            client.send(("client at -%s-:\n%s"%(ctime(),cliMsg)).encode())
