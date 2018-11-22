import socket
s = socket.socket()

host = socket.gethostname()
port = 1234
#print(host)
s.bind((host,port))
s.listen(5)

while True:
    c,add = s.accept()
    print("Get connection from",add)
    c.send("Thank you for your conection!")
    c.close()
