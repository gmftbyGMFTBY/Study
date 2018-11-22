## C网络编程

### 基本概念

1. IP地址

   * IP地址是用来表示全球中个的一台计算机的一种特定的符号，表示的时候采用32位长度二进制数字表示(4个字节)
   * IP地址又称逻辑地址，可以改变主机IP地址，MAC地址是不可变动

   ```bash
   ifconfig
   ```

2. 端口

   * 用来标识在计算机中访问互联网的计算机进程(区分网络通信中的主机中不同的网络应用程序)，相当于是一个网络进程表示符号，标识一个网络数据从属于某一个进程
   * 0~65535(1~1024是系统预定的端口)

3. 域名

   代替IP地址的直观性表示符号，可以进行转化

   ```bash
   ping IP    # IP来ping 
   ping www.baidu.com    # 域名
   ```

4. TCP / UDP

   两种在网络中数据传输的约定，主要区别在于我们在传输的时候两台计算机是否进行连接

   * TCP

     面向连接的网络传输方式，面向连接的可靠的信息传输方式，有点事可靠，缺点是传输过程复杂和占用过多的网络资源

   * UDP

     无连接的网络传输方式没传输效率高，不占用过多的网络资源，但是并不保证消息的可靠性，并不建立连接

5. 套接字

   * 用来描述计算机中不同程序和其他计算机程序之间的通信方式
   * **因为可能多个网络程序都要使用同一个TCP/UDP的端口进行数据的发送和接受，所以为了区分不同的网络应用程序，需要使用套接字来进行区分**
   * 套接字三个参数
     * 目的IP地址
     * 端口号
     * 协议(TCP / UDP)
   * 一个套接字相当于一个接口，可以实现不同计算机程序之间的信息传输

6. 基本头文件包含

   ```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <netinet/in.h>
   #include <arpa/inet.h>
   #include <unistd.h>
   #include <fcntl.h>
   #include <sys/stat.h>
   #include <sys/types.h>
   #include <sys/socket.h>
   ```

### 基本数据类型

1. **保存套接字信息**的结构体

   ```C
   // 1
   struct sockaddr
     {
       unsigned short int sa_family;    //通信的地址类型，TCP/IP - AF_INET
       char sa_data[14];    // xxx.xxx.xxx : xxxxx,保存IP和端口信息
     };
   //2
   struct socketaddr_in
     {
       unsigned short int sin_family;   //同上
       uint16_t sin_port;    //端口
       struct in_addr sin_addr;    //存储IP
       unsigned char sin_zero[8];　　//未使用字段
     };
   struct in_addr
     {
       uint32_t s_addr;
     };
   //连个套接字保存到的信息都是一致的，可以使用类型转换
   ```

2. 套接字类型

   套接字类型指代的是网络通信中不同的数据传输方式

   * `SOCK_STREAM`面向连接的可靠通信 - TCP
   * 数据报 - UDP
   * `SOCK_RAW`原始套接字，用来访问其他的协议

### 域名和IP地址

1. 域名和IP的转化

   只能利用IP地址来记性通信，我们对于知道的域名，需要转化成IP地址才可以使用

2. 域名 -> IP

   ```C
   //name是字符串，将域名字符串转换成主机地址的结构体并返回
   struct hostent *gethostbyname(const char* name);

   struct hostent
     {
       char* h_name;    //主机名称
       char** h_aliases;   //主机别名
       int h_addrtype;  //主机名的类型
       int h_length;   //地址长度
       char** h_addr;   //主机的IP地址
     };
   ```

3. 示例

   ```c
   // 1.h_errno
   // 2.hstrerro(h_errno)
   // 3.inet_ntoa(struct in_addr) ->　转换成对应的IP字符串
   #include <stdio.h>
   #include <sys/socket.h>
   #include <netdb.h>
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   #include <arpa/inet.h>   //inet_ntoa,将10进制的数字转化成IP字符串

   int main(int argc , char* argv[])
   {
       struct hostent * host;
       char hostname[] = "www.163.com";
       char hostname2[] = "www.akaskfasf.com";   //Unknow
       struct in_addr in;
       struct sockaddr_in addr_in;
       extern int h_errno;    //error number
       
       if((host = gethostbyname(hostname)) != NULL)
       {
           memcpy(&addr_in.sin_addr.s_addr , host->h_addr , 4);
           in.s_addr = addr_in.sin_addr.s_addr;
           printf("Domain name : %s\n" , hostname);
           printf("IP length : %d\n" , host->h_length);
           printf("Type : %d\n" , host->h_addrtype);
           printf("IP : %s\n", inet_ntoa(in));
       }
       if((host = gethostbyname(hostname2)) == NULL)
       {
           printf("%s\n" , hostname2);
           printf("error : %d\n" , h_errno);    //extern导入的变量，表示错误代号
           printf("%s\n" , hstrerror(h_errno));   //根据h_errno显示打印我们的错误信息
       }
   }
   ```

4. IP返回域名

   ```c
   struct hostent* gethostaddr(const void* addr , socklen_t len , int type);    //IP , IP地址的长度 , AF_INET
   ```

   ```C
   #include <stdio.h>
   #include <sys/socket.h>
   #include <netdb.h>
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   #include <arpa/inet.h>   //inet_ntoa,将10进制的数字转化成IP字符串

   int main(int argc , char* argv[])
   {
       struct hostent * host;
       char addr[] = "202.108.249.216";
       struct in_addr in;
       struct sockaddr_in addr_in;
       extern int h_errno;    //error number

       if((host = gethostbyaddr(addr , sizeof(addr) , AF_INET)) != (struct hostent*)NULL)
       {
           memcpy(&addr_in.sin_addr.s_addr , host->h_addr , 4);    //将h_addr的char类型用内存赋值的方式赋值4个字节，刚好是IP的大小
           in.s_addr = addr_in.sin_addr.s_addr;
           printf("Domain name : %s\n" , host->h_name);
           printf("IP length : %d\n" , host->h_length);
           printf("Type : %d\n" , host->h_addrtype);
           printf("IP %s\n" , inet_ntoa(in));
       }
       else
       {
           printf("error : %d\n" , h_errno);
           printf("%s\n" , hstrerror(h_errno));
       }
   }
   ```

### 网络协议

1. 协议结构体

   ```c
   //协议结构体
   //netdb.h
   struct protoent
     {
       char* p_name;    //协议名称
       char** p_aliases;    //协议别名
       int p_proto;    //协议的序号
     };
   ```

2. 根据协议名称字符串获取协议数据结构体

   ```C
   struct protoent* getprotobyname(char* name);
   ```

3. 示例

   ```c
   #include <stdio.h>
   #include <sys/socket.h>
   #include <netdb.h>
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   #include <arpa/inet.h>   //inet_ntoa,将10进制的数字转化成IP字符串

   int main(int argc , char* argv[])
   {
       struct protoent* pro;
       pro = getprotobyname("icmp");
       printf("protocol name : %s\n" , pro->p_name);
       printf("protocol alias_name : %s\n" , pro->p_aliases[0]);
       printf("protocol number : %d\n" , pro->p_proto);

       pro = getprotobyname("tcp");
       printf("protocol name : %s\n" , pro->p_name);
       printf("protocol alias_name : %s\n" , pro->p_aliases[0]);
       printf("protocol number : %d\n" , pro->p_proto);

       pro = getprotobyname("udp");
       printf("protocol name : %s\n" , pro->p_name);
       printf("protocol alias_name : %s\n" , pro->p_aliases[0]);
       printf("protocol number : %d\n" , pro->p_proto);
   }
   ```

4. 根据协议编号获取协议数据结构体

   ```c
   struct protoent* getprotobynumber(int proto);    // /etc/protocols
   ```

5. 示例

   ```c
   #include <stdio.h>
   #include <sys/socket.h>
   #include <netdb.h>
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   #include <arpa/inet.h>   //inet_ntoa,将10进制的数字转化成IP字符串

   int main(int argc , char* argv[])
   {
       struct protoent* pro;
       for(int i = 0;i < 5;i++)
       {
           pro = getprotobynumber(i);
           printf("protocol name : %s\n" , pro->p_name);
           printf("protocol number : %d\n" , pro->p_proto);
           printf("protocol alias : %s\n" , pro->p_aliases[0]);
       }
   }
   ```

6. 获取系统支持的所有的协议

   ```c
   //循环获取protoent部分的内容最后返回空 , while
   struct protoent* getprotoent(void);
   ```

### 网络服务

一台主机为另一组实现网络功能的实现

服务和协议是不同的，一个协议可能会支持很多的网络服务功能

```C
// /etc/services
struct servent
  {
    char* s_name;    //服务名称
    char** s_aliases;    //服务可能的别名
    int s_port;    //服务端口
    char* s_proto;    //服务使用的协议
  };
```

```c
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>   //inet_ntoa,将10进制的数字转化成IP字符串

int main(int argc , char* argv[])
{
    struct servent* ser;
    while(ser = getservent())
    {
        printf("name : %s\n" , ser->s_name);
        printf("port : %d\n" , ntohs(ser->s_port));
        printf("protocols : %s\n" , ser->s_proto);
        printf("alias : %s\n" , ser->s_aliases[0]);
    }
}
```

```c
struct servent* getserverbyname(char* name , char* proto);
```

```c
struct servent* getserverbyport(int port , char* proto);   //这里的int必须使用htons进行包装
struct servent* getserverbyport(htons(23) , "tcp");
```

### 网络地址转换

1. IP地址使用的是一个十进制的长整形数来进行存储，头文件

   ```c
   #include <sys/socket.h>
   #include <netinet/in.h>
   #include <arpa/inet.h>
   long inet_addr(char* cp);    //使用字符串并将其转换成对应的长整形
   char* inet_ntoa(struct in_addr);    //将无符号长整形包装成的IP转换成对应的IP字符串
   ```


2. 主机字符顺序和网络字符顺序的转换

   * IP - int 转换
   * port - int 转换(见上getservbyport实现)

   ```c
   #include <arpa/inet.h>
   uint32_t htonl(uint32_t hostlong);    //主机地址字符顺序转网络字符顺序
   uint32_t ntohl(uint32_t netlong);　　　//相反
   ```

### 错误处理

````c
// 1 
herror();    //显示上一个网络错误
// 2
extern int h_errno;
char* hstrerror(h_errno);    //现实捕捉的错误消息
````

## UDP

1. 建立socket

   ```c
   int socket(int domain , int type , int protocol);
   //domain 地址类型
   //type 是通信协议
   //protocol 传输协议编号，一般默认是0
   //套接字建立成功会返回套接字的编号，不成功会返回-1
   ```

2. 无连接的套接字UDP

   因为是没有连接的套机字，首先我们就不需要对服务器和客户端之间有明显的区别，都是需要

   * 创建套接字
   * 绑定端口和计算机(服务器绑定自己，客户端绑定服务器)
   * 发送和接收消息

3. `sendto` / `resvfrom`

   1. `sendto`可以通过一个已经建立的套接字**将一段信息发送到另一个程序的套机字中**

      ```c
      //传送成功，返回产送的字符的个数，否则返回-1表示传送失败
      int sendto(int s,void* msg , int len , unsigned int flags , struct sockaddr* to , int tolen);
      //s是建立的套接字编号
      //msg是发送的字符串
      //len是发送的字符串长度
      //flags默认是0
      //tolen是sockaddr的长度,可以使用sizeof获得
      ```

   2. `recvfrom`

      ```c
      //调用成功返回接收的字符串的个数，否则返回-1
      int recvfrom(int s , void* buf , int len , unsigned int flags , struct sockaddr* from , int* fromlen);
      //buf用来接收信息到本地的内存
      //flags默认一般是设置成0
      //fromlen是sockaddr的长度，可以使用sizeof获得
      //小心最后的参数是指针类型的
      ```

   3. 构建C / S模型的UDP服务端和客户端

      ```c
      //必要的库函数
      // 1
      int inet_addr(char*);    //转化成对应的十进制数字
      // 2
      htonl(INADDR_ANY);     //INADDR_ANY本身就是10进制的字符串
      // 3
      bzero(m , sizeof(m));    //类似于memset,清空数据
      ```

      * 客户端

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>
        #include <unistd.h>
        #include <fcntl.h>
        #include <sys/stat.h>
        #include <sys/types.h>
        #include <sys/socket.h>

        #define REMOTEPORT 4567
        #define REMOTEIP "127.0.0.1"

        int main()
        {
            int s , len;
            struct sockaddr_in addr;
            int addr_len;
            char msg[256];
            int i = 0;

            if((s = socket(AF_INET , SOCK_DGRAM , 0)) < 0)
            {
                perror("error.");
                exit(1);
            }
            else
            {
                printf("socket created .\n");
                printf("socket id %d\n" , s);
                printf("remote ip %s\n" , REMOTEIP);
                printf("remote port %d\n" , REMOTEPORT);
            }

            addr_len = sizeof(addr);
            bzero(&addr , sizeof(addr));    //清空内存
            addr.sin_family = AF_INET;
            addr.sin_port = htons(REMOTEPORT);
            addr.sin_addr.s_addr = inet_addr(REMOTEIP);

            while(1)
            {
                bzero(msg , sizeof(msg));
                len = read(STDIN_FILENO , msg , sizeof(msg));     //从标准输入读取数据
                sendto(s , msg , len , 0 , &addr , addr_len);     //只读填充部分
                printf("\nInput the message : %s \n" , msg);
                len = recvfrom(s , msg , sizeof(msg) , 0 , &addr , &addr_len);    //一次清全读取

                printf("%d : " , i++);
                printf("Received message : %s\n" , msg);
            }
            return 0;
        }
        ```

      * 服务端

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>
        #include <unistd.h>
        #include <fcntl.h>
        #include <sys/stat.h>
        #include <sys/types.h>
        #include <sys/socket.h>

        #define LOCALPORT 4567

        int main()
        {
            int mysock , len;
            struct sockaddr_in addr;
            int i = 0;
            char msg[256];    //按照字符串的形式接收

            int addr_len;
            if((mysock = socket(AF_INET , SOCK_DGRAM , 0)) < 0)
            {
                perror("error");
                exit(1);
            }
            else
            {
                printf("socket created\n");
                printf("socket id %d\n" , mysock);
            }

            addr_len = sizeof(struct sockaddr_in);
            bzero(&addr , sizeof(addr));
            addr.sin_family = AF_INET;
            addr.sin_port = htons(LOCALPORT);
            addr.sin_addr.s_addr = htonl(INADDR_ANY);

            addr_len = sizeof(struct sockaddr_in);
            bzero(&addr , sizeof(addr));
            addr.sin_family = AF_INET;
            addr.sin_port = htons(LOCALPORT);    //host to net (htons) function , 将本地的字符顺序装花城网络的字符顺序
            addr.sin_addr.s_addr = htonl(INADDR_ANY);    //表示本地主机的所有的可行的IP地址，转化成网络字节顺序(0.0.0.0 , 十进制的0)

            if(bind(mysock , &addr , sizeof(addr)) < 0)    //绑定socket到对应的网络端口和IP上，这里是服务器绑定到本地上
            {
                perror("connect");
                exit(1);
            }
            else
            {
                printf("bind ok.\n");
                printf("local port %d\n" , LOCALPORT);
            }

            while(1)
            {
                bzero(msg , sizeof(msg));
                len = recvfrom(mysock , msg , sizeof(msg) , 0 , &addr , &addr_len);
                printf("%d " , i++);
                printf("message length : %d\n" , len);
                printf("message %s \n" , msg);
                sendto(mysock , msg , len , 0, &addr , addr_len);
            }
            return 0;
        }
        ```

## TCP

![1](/home/lantian/File/Study/Linux/Linux_C/1.png)

1. 流程

   * 服务器建立套接字开始监听
   * bind绑定端口号和IP地址，要帮对具体的端口和IP地址
   * 服务器listen进入锦绣厅状态等待客户机的连接
   * 客户机登录并建立远程服务器的对应的套接字
   * 客户机connect注定发起连接
   * 服务端用accept函数接收远程计算机的连接，并建立通信
   * 双方开始read / write读写数据
   * 客户机完成任务关闭套接字退出连接

2. 具体细节

   * 绑定端口`bind`

     socket套接字建立之后需要在这个套接字上绑定一个具体的端口

     ```c
     int bind(int sockfd , struct sockaddr_in* my_addr , int addrlen);
     //sockfd 已经建立的socket的编号
     //my_addr是指向具体的套接字的结构体
     //addrlen表示my_addr套接字结构体的大小
     //绑定成功返回0否则返回-1
     ```

   * 监听

     监听 : 套接字的端口处于等待状态，等待客户端的请求

     监听只是让socket进入listen坚挺模式，真正执行连接的是accept函数

     **服务端申请监听之后，客户端的所有的连接都会被接入到服务端进行处理，但是最好处理之后就FD_ZERO**

     ```c
     int listen(int s , int backlog);
     //s是建立的套接字的识别编号
     //backlog表示可以同时处理的最大请求数目，如果超过该数目，会返回拒绝连接的错误给客户 max = 128
     //函数调用成功返回0，否则返回-1
     ```

   * 发起连接

     ```c
     int connect(int sockfd , struct sockaddr* serv_addr , int addrlen);
     //sockaddr是套接字的编号
     //serv_addr存放这远程服务器的IP和端口信息(套接字的一部分)
     //sizeof(serv_addr)
     //函数执行成功，客户端会连接到服务端上等待服务端accept处理，函数执行成功返回0否则返回-1
     ```

   * 接收连接

     对用户的请求，放入等待队列中，当系统空闲处理用户的连接

     ```c
     int accept(int s , struct sockaddr_in* addr , int* addrlen);
     //s是socket的编号
     //addr会将远程发起连接的主机的信息保存在该套接字中
     //sizeof(addr)

     //accept函数会返回一个新的socket编号，以后的数据读取和发送都是利用新的socket编号处理，函数失败返回-1
     ```

   * 数据接收

     1. `recv`

        ```c
        int recv(int s , void* buf , int len , unsigned int flags);
        //s是已经建立的socket连接的编号，客户端就是scoket,服务端是新的socket编号
        //buf是数据指针，接收到的数据会保存在其中
        //len是数组的长度,sizeof
        //flags = 0默认

        //函数返回接收到的数据的字符的个数，错误返回-1
        ```

     2. `read`

        ```c
        ssize_t read(int fd , void* buf , size_t count);
        //fd是套接字(服务器是新的accept返回的套接字编号)
        //count表示buf的总长度
        //函数返读取的字节的个数
        ```

   * 数据发送

     1. `send`

        ```c
        int send(int s , const void* msg , int len , unsigned int flags);
        //flags = 0
        //函数执行陈宫返回传送的字符的个数( > 0)，否则返回-1
        ```

     2. `write`

        ```c
        int write(int fd , const void* buf , size_t count);
        //成功返回字节个数(> 0 )，否则返回-1
        ```

   * `select`的使用

     **摘引自 :  [http://linux.chinaunix.net/techdoc/develop/2006/09/08/939732.shtml]**

     Select在Socket编程中还是比较重要的，可是对于初学Socket的人来说都不太爱用Select写程序，他们只是习惯写诸如

     connect、accept、recv或recvfrom这样的阻塞程序（所谓阻塞方式block，顾名思义，就是进程或是线程执行到这些函数时必须等待某个事件的发生，如果事件没有发生，进程或线程就被阻塞，函数不能立即返回）。可是使用Select就可以完成非阻塞（所谓非阻塞方式non-block，就是进程或线程执行此函数时不必非要等待事件的发生，一旦执行肯定返回，以返回值的不同来反映函数的执行情况，如果事件发生则与阻塞方式相同，若事件没有发生则返回一个代码来告知事件未发生，而进程或线程继续执行，所以效率较高）方式工作的程序，**它能够监视我们需要监视的_文件描述符_的变化情况——读写或是异常。**

     下面详细介绍一下！

     Select的函数格式(我所说的是Unix系统下的伯克利socket编程，和windows下的有区别，一会儿说明)：

     ```c
     int select(int maxfdp ,
                fd_set *readfds ,
                fd_set *writefds,
                fd_set *errorfds,
                struct timeval *timeout
               );
     ```

     **先说明两个结构体：**

     1. struct fd_set

        可以理解为一个集合，这个集合中存放的是**文件描述符(filedescriptor)，即文件句柄**，这可以是我们所说的普通意义的文件，当然Unix下任何设备、管道、FIFO等都是文件形式，全部包括在内，所以毫无疑问一个socket就是一个文件，socket句柄就是一个文件描述符。fd_set集合可以通过一些宏由人为来操作，比如

        * `FD_ZERO(fd_set * )` : 清空集合,**服务端每一次循环都清空一次**,不清空会导致别的连接进不来
        * `FD_SET(int ,fd_set* )` : 将一个给定的文件描述符加入集合之中
        * `FD_CLR(int,fd_set* )` : 将一个给定的文件描述符从集合中删除*
        * `FD_ISSET(int ,fd_set* )` : 检查集合中指定的文件描述符是否可以读写(比如是否可以从socke编号中读取和写入文件)

     2. struct timeval

        这是一个大家常用的结构，用来代表时间值，有两个成员，一个是秒数，另一个是毫秒数。

     **具体解释select的参数：**

     1. int maxfdp

        是一个整数值，**是指集合中所有文件描述符的范围，即所有文件描述符的最大值加1**

     2. fd_set* readfds

        是指向fd_set结构的指针，这个集合中应该包括文件描述符，**我们是要监视这些文件描述符的读变化的**即我们关心是否可以从这些文件中

        读取数据了，**如果这个集合中有一个文件可读，select就会返回一个大于0的值，表示有文件可读**，如果没有可读的文件，则根据timeout参数再判断是否超时，若超出timeout的时间，select返回0，若发生错误返回负值。**可以传入NULL值，表示不关心任何文件的读变化**。

     3. fd_set *writefds

        是指向fd_set结构的指针，这个集合中应该包括文件描述符，**我们是要监视这些文件描述符的写变化的**，即我们关心是否可以向这些文件

        中写入数据了，如果这个集合中有一个文件可写，select就会返回一个大于0的值，表示有文件可写，如果没有可写的文件，则根据timeout参数再判

        断是否超时，若超出timeout的时间，select返回0，若发生错误返回负值。**可以传入NULL值，表示不关心任何文件的写变化**。

     4. fd_set *errorfds

        同上面两个参数的意图，用来监视文件错误异常。

     5. struct timeval* timeout

        是select的超时时间，这个参数至关重要，它可以使select处于三种状态

        * 若将NULL以形参传入，即不传入时间结构，就是将select置于阻塞状态，一定等到监视文件描述符集合中某个文件描述符发生变化为止(阻塞到有变化为止，相当于是一个阻塞任意时限长度,timeout可以很大也可以很小，取决于事件到来的时间)
        * 若将时间值设为0秒0毫秒，就变成一个纯粹的非阻塞函数，不管文件描述符是否有变化，**都立刻返回继续执行**，文件无变化返回0，有变化返回一个正值
        * timeout的值大于0，这就是等待的超时时间，即select在timeout时间内阻塞，超时时间之内有事件到来就返回了，否则在超时后不管怎样一定返回，返回值同上述。

     **返回值：**

     * 负值：select错误
     * 正值：某些文件**可读写**或出错
     *  0：等待超时，没有可读写或错误的文件(常用来continue)

     **举个简单的例子，就是从网络上接受数据写入一个文件中。** 

     ```c
     #include <stdio.h>
     #include <stdlib.h>
     #include <netinet/in.h>
     #include <arpa/inet.h>
     #include <unistd.h>
     #include <fcntl.h>
     #include <sys/stat.h>
     #include <sys/types.h>
     #include <sys/socket.h>

     int main() 
     { 
         int sock; 
         FILE *fp; 
         struct fd_set fds; 
         struct timeval timeout={3,0}; //select等待3秒，3秒轮询，要非阻塞就置0 
         char buffer[256]={0}; //256字节的接收缓冲区 
         /* 
         假定已经建立UDP连接，具体过程不写，简单，当然TCP也同理，主机ip和port都已经给定，要写的文件已经打开 
         sock=socket(...); 
         bind(...); 
         fp=fopen(...); 
         */ 

         while(1) 
         { 
             FD_ZERO(&fds); //每次循环都要清空集合，否则不能检测描述符变化
             FD_SET(sock,&fds); //添加描述符 
             FD_SET(fp,&fds); //同上
             maxfdp = sock > fp ? sock+1 : fp+1;    //描述符最大值加1
             switch(select(maxfdp,&fds,&fds,NULL,&timeout))   //select使用 
             { 
                 case -1: exit(-1);break; //select错误，退出程序 
                 case 0:break;  //再次轮询
                 default: 
                       if(FD_ISSET(sock,&fds)) //测试sock是否可读，即是否网络上有数据
                       { 
                             recvfrom(sock,buffer,256,.....);//接受网络数据 
                             if(FD_ISSET(fp,&fds)) //测试文件是否可写 
                                 fwrite(fp,buffer...);//写入文件 
                              //buffer清空; 
                        }
               }
          }
     }
     ```

     ​