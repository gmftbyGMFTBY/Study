import sys
from socket import *

host = sys.argv[1]

service = {
'21':'FTP',
'23':'Telnet',
'25':'SMTP',
'53':'DNS',
'69':'TFTP',
'80':'HTTP',
'135':'RPC',
'137':'NetBIOS',
'139':'Samba',
'1521':'Oracle',
'1433':'SQL_server',
'3306':'MySQL',
'3389':'Remote_Desktop'
}

ports = [21,23,25,53,69,80,135,137,1521,1433,3306,3389]

print("Please Waiting...")

client = socket(AF_INET,SOCK_STREAM)

for p in ports:
    try:
        client.connect((host,p))
        print(service[str(p),p,'ON'])
    except Exception as e:
        print(service[str(p)],p,"OFF")
client.close()
