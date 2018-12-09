'''Ready to grasp the directionary information from the Gopher using our python socket module
This is the client try to visit the Gopher

But in the coding,i find the python2 and python3 in the socket has a lot of differences:

TypeError:'str' does not support the buffer interface
The answer is that：
在python3中，我们的buffer传输必须是bytes的类型，并且标准输出使用string类型
我们的string类型需要encode()成bytes类型，bytes类型需要decode()成string类型'''
import sys,socket		#include the module:sys and socket

port = 70

host = sys.argv[1]

filename = sys.argv[2]

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

s.connect((host,port))
 
a = filename+'\r\n'

s.send(a.encode())

while True:
    buf = s.recv(2048).decode()
    if not len(buf):break
    sys.stdout.write(buf)

s.close()
