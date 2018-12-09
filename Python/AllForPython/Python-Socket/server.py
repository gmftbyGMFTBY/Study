#!/usr/bin/python

'''
# 可以实现简易的全双工模式，但是会将没有写完的数据覆盖无效掉

import socket

# use multi threading to send and recive the message from the client
import threading

host = ''
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
    s.bind((host, port))
    s.listen(5)

    # begin to wait for the connection
    print('Begining ...')
    while True:
        conn, addr = s.accept()
        print("connect by", addr)
    
    # get the connection 
        with conn:
            # data = conn.recv(1024)
            # print(data)
            # print(data.decode('utf8'))
            # get the data from stdin
            # data = input().encode('utf8')
            # if not data:
            #     break
            # conn.sendall(data)
            get_thread = threading.Thread(target = get_msg, args = (conn,))
            send_thread = threading.Thread(target = send_msg, args = (conn,))
            get_thread.start()
            send_thread.start()
            get_thread.join()
            send_thread.join()
            print('over')

'''

# 采用 select 实现全双攻模式多路复用 I/O
import time
import select
import socket
import sys

host = ''
port = 50022
backlog = 5
size = 1024
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host,port))
server.listen(backlog)
raw_input = [server,sys.stdin]
running = 1

print('waiting connection...')
client, address = server.accept()
print("connecte to...",address)
raw_input.append(client)

while running:
    print('>')
    inputready,outputready,exceptready = select.select(raw_input,[],[], 3)

    # print(len(inputready), len(outputready), len(exceptready))
    # print(inputready, server.fileno(), client.fileno())
   
    for s in inputready:
       
        if s == sys.stdin:
            # handle standard input
            serMsg = input()
            if serMsg == '^c':
                running = 0
                client.send(serMsg)
                client.close()
                break
            client.send(("server at -%s-:\n%s"%(time.ctime(),serMsg)).encode())
        else:
            # handle all other sockets
            print('ready to set the timeout to 1')
            s.settimeout(1)
            print(s.gettimeout())
            data = s.recv(size)
            if data:
                print(data.decode())
            else:
                s.close()
                # 移除关闭的文件是非常重要的
                raw_input.remove(s)
                             
server.close()
print('server is over')
