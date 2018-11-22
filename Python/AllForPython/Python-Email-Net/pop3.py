#!/usr/bin/python3
# SMTP for sending, POP3 for receving, curl the mail from MDA to MUA
# poplib and email module
# 1. poplib recive the email, 2. email decode

from email import encoders
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.header import Header, decode_header
from email.utils import parseaddr , formataddr
from email.parser import Parser
import poplib
import ipdb

def print_info(msg, indent=1):
    if indent == 0:
        for header in ['From', 'To', 'Subject']:
            value = msg.get(header, '')
            if value:
                if header =='Subject':
                    value = decode_str(value)
                else:
                    hdr, addr = parseaddr(value)
                    name = decode_str(hdr)
                    value = u'%s <%s>' % (name, addr)
            print('%s%s: %s' % ('  ' * indent, header, value))
    if (msg.is_multipart()):
        parts = msg.get_payload()
        for n, part in enumerate(parts):
            print('%spart %s' % ('  ' * indent, n))
            print('%s--------------------' % ('  ' * indent))
            print_info(part, indent + 1)
    else:
        content_type = msg.get_content_type()
        if content_type=='text/plain' or content_type=='text/html':
            content = msg.get_payload(decode=True)
            charset = guess_charset(msg)
            if charset:
                content = content.decode(charset)
            print('%sText: %s' % ('  ' * indent, content + '...'))
        else:
            print('%sAttachment: %s' % ('  ' * indent, content_type))

def decode_str(s):
    value, charset = decode_header(s)[0]
    if charset:
        value = value.decode(charset)
    return value

def guess_charset(msg):
    charset = msg.get_charset()
    if charset is None:
        content_type = msg.get('Content-Type', '').lower()
        pos = content_type.find('charset=')
        if pos >= 0:
            charset = content_type[pos + 8:].strip()
    return charset

def init(email, password, pop3_server):
    email = "18811371908@163.com"
    password = "lt970106"
    pop3_server = "pop.163.com"
    
    server = poplib.POP3(pop3_server)
    # server.set_debuglevel(1)
    print(server.getwelcome().decode('utf-8'))
    
    server.user(email)
    server.pass_(password)

    print('Messages: %s. Size: %s' % server.stat())
    print('Init POP3 server successfully !')
    
    return server, server.stat()[0]

def show_help():
    help_str = '''This client is the POP3 client for mail.163.com\n
    1. `show` command show the help msg\n
    2. `list` command show 10 (default) the email on the MDA\n
    3. `retr num` command receive the email index is [num] from MDA to this terminal\n
    4. `print` command show the retr email in the buffer\n
    5. `quit` command quit the POP3 process\n
    6. `del num` command delete the email [num] in the MDA\n'''
    print(help_str)

if __name__ == "__main__":
    email = input('Email: ')
    password = input('Password: ')
    pop3_server = input('POP3 server: ')
    # init the pop3 client
    server, size = init(email, password, pop3_server)
    buf = None
    show_help()

    while True:
        # ipdb.set_trace()
        try:
            command = input("Input the command: ").strip()
            if not command.strip(): continue
        
            if command.split()[0] not in ['show', 'list', 'retr', 'print', 'quit', 'del']:
                print('Wrong command, input again !')
                continue
            
            elif command == "list":
                resp, mails, octets = server.list()
                # ipdb.set_trace()
                for idx in range(size, size - 10, -1):
                    try:
                        _, lines, _ = server.retr(idx)
                        print(idx, '\t', lines[0].decode())
                    except:
                        # maybe not enough mail
                        break
        
            elif command.split()[0] == "retr":
                index = int(command.split()[1])
                resp, lines, octets = server.retr(index)
                buf = Parser().parsestr(b'\n'.join(lines).decode('utf-8'))
            
            elif command == "print":
                # the msg may containe the other file with the mail, so need to recursive show msg
                print('-' * 50)
                if buf: print_info(buf)
                print('-' * 50)
             
            elif command == "quit":
                server.quit()
                print('Bye')
                break
            
            elif command.split()[0] == "del":
                server.dele(int(command.split()[1]))
            
            elif command == "show":
                show_help()

            else:
                pass
        except:
            print('Bye')
            server.quit()
            break
