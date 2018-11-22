#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

/*
    socket:
    1. 类型
        PF_LOCAL: Unix 本机
        PF_INET : 客户端和服务端在 ipv4 网络上
        PF_INET6: 客户端和服务端在 ipv6 网络上

        SOCK_STREAM | SOCK_DGRAM | SOCK_RAW
    2. 连接
        服务器启动命名套接字
            socket | bind | listen | accept | read | write | close
        客户端启动无名套接字
            socket | connect | read | write | close
        客户端连接后，服务端复制一个子进程和客户端通信，父进程继续接收其他链接
    3. 系统调用
        1. socket:
            int socket(int domain, int type, int protocol)
                1. 创建一个域名是 domain, 类型是 type, 协议是 protocol 的套接字
                2. 调用成功返回对应的文件描述符，失败返回 -1
                3. serverfd = socket(PF_LOCAL, SOCK_STREAM, DEFAULT_PROTOCOL)
        2. bind
            int bind(int fd, const struct sockaddr* address, size_t addressLen)
                1. 将文件描述符 fd 代表的未命名套接字关联到 address 中的套接字地址
                2. addressLen 反应的是地址的长度
                3. 调用成功返回 0, 失败返回 -1
                4. address: sockaddr_un - PF_LOCAL, sockaddr_in - PF_INET
                    * sockaddr_un
                        struct  sockaddr_un{
                            unsigned short sun_family;  PF_LOCAL
                            char sun_path[108];  套接字路径
                        }
                    * sockaddr_in
                        struct sockaddr_in{
                            short int sin_family;  PF_INET
                            unsigned short int sin_port; port必须是网络字节顺序
                            struct in_addr sin_addr;    IP 地址，网络字节顺序
                            unsigned char sin_zero;
                        }
                5. 网络字节顺序
                    1. 每一台机器内部对变量的字节存储顺序不同，而网络传输的数据是一定要统一顺序的
                    2. 内部字节表示顺序与网络字节顺序不同的机器，一定要对数据进行转换
                    3. 本机的内部字节表示顺序与网络字节顺序相同也应该在传输数据以前先调用数据转换函数，以便程序移植到其它机器上后能正确执行
        3. listen
            int liste(int fd, int queueLength)  
            制定未处理连接的最大数量
        4. accept
            int accept(int fd, struct sockaddr* address, int* addressLen)
            监听 fd 指向的服务器套接字，等待接收客户端请求，收到请求创建一个未命名套接字，用语和客户端通信
            调用成功返回新的文件描述符，失败返回 -1
        5. connect
            int connect(int fd,struct sockaddr* address, int addressLen)
            连接地址包含在address所指向的结构中的服务器套接字。调用成功，返回0，客户端可以用fd与服务器的套接字进行通信


        

 */

int main(int argc, char* argv[])
{

    return 0;
}
