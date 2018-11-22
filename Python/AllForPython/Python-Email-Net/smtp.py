#!/usr/bin/python

import smtplib
from email import encoders
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.header import Header
from email.utils import parseaddr , formataddr

'''
def _format_addr(s):
    name, addr = parseaddr(s)
    return formataddr((Header(name, 'utf-8').encode(), addr))
'''

# from_addr = input('From: ')
from_addr = '18811371908@163.com'
# password = input('Password: ')
password = 'lt970106'
#to_addr = input('To (Group send , separate): ')
to_addr = 'maoxl@bit.edu.cn'
# smtp_server = input('SMTP server: ')    # smtp.163.com / smtp.qq.com
smtp_server = 'smtp.163.com'
mail_head = input('Mail Head: ')


context = []
eof = input('Input msg, Input your eof char: ')
print('-' * 20)
while True:
    line = input().strip()
    if line == eof: break
    context.append(line)
print('-' * 20)

msg = MIMEMultipart()
msg.attach(MIMEText('\n'.join(context), 'plain', 'utf-8'))
msg['From'] = from_addr
msg['To'] = to_addr 
msg['Subject'] = Header(mail_head, 'utf-8').encode()

server = smtplib.SMTP(smtp_server, 25)
server.login(from_addr, password)
server.sendmail(from_addr, list(to_addr.split(',')), msg.as_string())
server.quit()

print('-' * 20)
print('Send successfully')
