#!/usr/bin/python3

'''
1. ftp = FTP(host, user, passwd): support `with`
2. ftp.login(user, passwd)
3. ftp.cwd('path'): change pwd
4. ftp.retrlines('LIST'): list cmd
5. ftp.retrbinary('RETR README', open('README', 'wb').write)
   ftp.retrlines(...): only for text file, above for binary file
6. ftp.quit(): exe after close()
7. ftp.set_debuglevel(1)
8. ftp.getwelcome()
9. ftp.sendcmd(cmd_str): send the cmd and return response
10. ftp.dir(): list the dir
11. ftp.delete(filename)
12. ftp.mkd(pathname)
13. ftp.pwd()
14. ftp.close()
15. ftp.connect(host, port)
16. ftp.storbinary('STOR remotepath', open(localpath, 'rb'), bufsize)
    ftp.storlines(...)
'''

from ftplib import FTP
import ipdb

def init():
    host = input("FTP: ")
    user = input("User: ")
    password = input("Pass: ")

    host = "127.0.0.1"
    user = "lantian"
    password = "lt970106"

    ftp = FTP(host, user, password)
    ftp.getwelcome()
    ftp.set_debuglevel(1)
    return host, ftp

def show_help():
    help_msg = '''
    Show help msg about the ftp\n
    1. `ls` list the path\n
    2. `pwd` show the current path\n
    3. `download filename localfile` download the file\n
    4. `upload localfile remotefile` upload the file to ftp server\n
    5. `show`: show the help msg\n
    6. `rm filename`: delete the file on the ftp server\n
    7. `quit`: exit the ftp server\n
    8. `rename old new`: rename the file on ftp server\n
    9. `cd path`: change the path of the current path\n
    '''
    print(help_msg)

if __name__ == "__main__":
    host, ftp = init()
    show_help()

    try:

        while True:
            command = input('Input cmd: ').strip()
            if not command: 
                print()
                continue 

            if command == "ls": 
                ftp.dir()
                print()

            elif command == "pwd": 
                print(host + ':' + ftp.pwd() + '\n')

            elif command.split()[0] == "rm":
                ftp.delete(command.split()[1])
                print('Delete the file successfully !\n')

            elif command.split()[0] == "download": 
                # for text file, not binary file
                ftp.retrlines('RETR ' + command.split()[1], open(command.split()[2], 'wb').write)
                print('Download the file successfully !\n')

            elif command.split()[0] == "upload":
                # test file all is text file, not binary file
                ftp.storlines('STOR ' + command.split()[2], open(command.split()[1], 'r'))
                print('Upload the file successfully !\n')

            elif command == "show": 
                show_help()

            elif command == "quit":
                ftp.close()
                print('Bye')
                break

            elif command.split()[0] == "rename":
                ftp.rename(command.split()[1], command.split()[2])
                print('Rename the file into another name\n')

            elif command.split()[0] == "cd":
                ftp.cwd(command.split()[1])
                print(host + ':' + ftp.pwd() + '\n')

            else: 
                print('Wrong command, input again\n')

    except Exception as e:
        print(e)
        ftp.close()
        print('Bye')
