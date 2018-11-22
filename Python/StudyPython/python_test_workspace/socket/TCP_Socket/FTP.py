from ftplib import FTP

ftp = FTP()
timeout = 30
port = 21
ftp.connect('192.168.1.188',port,timeout)
ftp.login("Username",'888888')
print(ftp.getwelcome())
ftp.cwd('file/test')
list = ftp.nlst()
for name in list:
    print(name)
path = 'd:/data/' + name
f = open(path,'wb')
filename = 'RETR' + name
ftp.retrbinary(filename,f.write)
ftp.delete(name)
ftp.quit()
