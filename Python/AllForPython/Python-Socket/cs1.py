#!/usr/bin/python

import socket
import sys
import time

host, port = '', 9998
data = "lantian\n"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((host, port))
    for i in range(1000):
        data = str(i) + '\n'
        sock.send(data.encode())
        time.sleep(1)
        print(i)
