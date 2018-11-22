#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/sem.h>
#include <sys/msg.h>

/*
   time_t time(time_t* timer)
    获取当前的系统的时间，返回结果是一个 time_t 大整数表示从1970年到现在的秒数，之后可以用 localtime 转化，但是也不是很必要
 */

/*
    int sprintf(char *str, char * format [, argument, ...]);
    格式化的数据写入字符串中

    int sscanf(char* str, char* format, mixed var1, mixed var2 ... );
    字符串中格式化读取数据

    char *  fgets(char * s, int n,FILE *stream);
         s: 字符型指针，指向存储读入数据的缓冲区的地址。
         n: 从流中读入n-1个字符
         stream ： 指向读取的流。
          1. 当 n <= 0 时返回NULL，即空指针。
          2. 当 n = 1 时，返回空串"".
          3. 如果读入成功，则返回缓冲区的地址。
          4. 如果读入错误或遇到文件结尾(EOF)，则返回NULL.
*/

/*
    Linux 进程通信
    1. Linux 内部的进程的通信方式
        * 管道通信
            * 命名管道
            * 无名管道
        * 信号
        * 共享内存
        * 信号量机制
        * 消息缓冲队列

    2. 无名管道
       父子进程和兄弟进程之间通信，无名管道使用临时文件的方式实现进程之间的通信
       建立的管道文件只存在于内存中，无法在文件系统中看到
       数据在管道中单向流动，一个进程只能读或者写
        #include <unistd.h>
        int pipe (int fdes[2]);
            * fdes[0]: 只读端文件描述符
            * fdes[1]: 只写端文件描述符
       当读一个写入端已被关闭的管道时(读取剩余的管道数据)，在所有数据都被读取后，read返回0，指示结束
       当写一个读取端已被关闭的管道时(生产者没有任何的意义去生产，没有消费者了)，则产生信号SIGPIPE指示管道破裂，默认动作为结束进程，如果忽略或者捕捉该信号后返回，write返回-1
       在创建管道后关闭不需要的文件描述符，避免错误操作

       当父进程与子进程处于相同程序时(子进程没有 exec)，共享管道文件描述符
       但当子进程通过exec调用，启动了一个新的可执行文件时，子进程需要知道应该访问哪一个文件描述符
            方式: 将管道文件描述符传递给用exec启动的可执行文件

    3. 复制文件描述符
        #include <unistd.h>
        int dup(int filedes);
            dup 函数由系统自动分配当前可用的最小文件描述符,返回新的文件描述符
        int dup2(int filedes, int filedes2);
            dup2 函数可由第二个参数指定新描述符的数值，如果该描述符已被打开，则将其先关闭,返回新的文件描述符


        指使用另外一个文件描述符指向**同一个打开的文件**，即创建一个与给定描述符等价的新描述符，不同于文件描述符变量自身的复制
        复制成功返回新的文件描述符

    4. 管道用作标准输入输出
        1. 结合dup2函数，使用管道将进程中的标准输入输出替换，可将read/write转化为一般化的输入和输出操作
        2. 0, 1, 2 - 标准输入，标准输出，标准错误

    5. 自动化管道处理
        这两个函数可以简化管道的使用方式
        管道的使用流程:
            1. 管道创建
            2. fork() 生成子进程
            3. 关闭管道的无用端
            4. 执行外部命令或程序
            5. 以及等待执行完毕后返回等一系列操作都会由系统自动完成
        FILE * popen(const char cmdstring, const char *openmode);     // 开启管道
            cmdstring:
                一个完整的 shell 命令行
                popen()会调用fork()产生子进程，然后从子进程中调用/bin/sh -c 来执行参数command 的指令。
                参数 openmode 可使用 "r"代表读取，"w"代表写入。依照此 openmode 值，popen()会建立管道连到子进程的标准输出设备或标准输入设备
                    然后返回一个文件指针。随后进程便可利用此文件指针来读取子进程的输出设备或是写入到子进程的标准输入设备中。
                此外，所有使用文件指针(FILE*)操作的函数也都可以使用，除了fclose()以外。
                返回值：若成功则返回文件指针, 否则返回NULL, 错误原因存于errno 中.
            openmode:
                * r: 读管道，那么管道的输入端与子进程的标准输出端相连，子进程写入数据，从子进程读
                * w: 写管道，那么管道的输出端与子进程的标准输入端相连，子进程接收数据，写入子进程
        int pclose(FILE *fp);       // 等待命令执行结束关闭管道

    6. 命名管道
        1. 特殊设备文件
        2. 命名管道突破了无名管道对于进程间关系的限制，可以被任何知道其名字的进程所使用
        3. 创建命名管道后必须显式打开才能使用，使用完毕后要显式删除，否则将一直存在
        4. 命名管道的行为与功能类似于无名管道
        5. e.g.:
            #include <sys/stat.h>
            #include <sys/types.h>
            #include <unistd.h>
            #include <fcntl.h>

            int mkfifo(const char *pathname, mode_t mode);
                尽可能使用
                mode 不能是读写模式，只能是读或者是写模式
            int mknod(const char* pathname, mode_t mode, dev_t dev);
                可以用来创建其他的特殊类型的文件，命名管道 dev = 0
            在打开管道文件时，如果未使用O_NONBLOCK标志，则先执行的读取操作会暂时阻塞，在其他进程打开管道并写入后才会返回。
            同样地，先执行的写入操作也会暂时阻塞，在其他进程打开管道并读取后返回
        6. 打开方式
            // O_NONBLOCK: 非阻塞方式
            open调用的阻塞是什么一回事呢？很简单，对于以只读方式（O_RDONLY）打开的FIFO文件
            如果open调用是阻塞的（即第二个参数为O_RDONLY），除非有一个进程以写方式打开同一个FIFO，否则它不会返回；
            如果open调用是非阻塞的的（即第二个参数为O_RDONLY | O_NONBLOCK）
            则即使没有其他进程以写方式打开同一个FIFO文件，open调用将成功并立即返回。
            open(const char *path, O_RDONLY);//1  
            open(const char *path, O_RDONLY | O_NONBLOCK);//2  
            open(const char *path, O_WRONLY);//3  
            open(const char *path, O_WRONLY | O_NONBLOCK);//4 

    7. IPC
        1. IPC 对象在文件系统中不可见，长期驻留在内存中，知道进程显示释放或者系统关闭.定义了一系列的函数调用
        2. 每一个 IPC 都分配了一个 32 的系统标识，全局可见
        3. 引用标识符，32位，是一个对对应于系统标识的可以操作的对象
        4. 共享内存 (最快的 IPC, 不经过内核彼此传递数据)
            * 共享内存为进程提供了直接通过内存进行通信的有效手段，是最快速高效的一种IPC方式
            * 两个或者更多进程可以共享一个内存区，一个进程也可以使用多个共享内存区
            * 留意读写同步的问题

            struct shmid_ds {
               struct ipc_perm shm_perm;    // 用户权限
               size_t          shm_segsz;   // 共享内存大小
               time_t          shm_atime;   // 上次访问时间
               time_t          shm_dtime;   // 上次释放时间
               time_t          shm_ctime;   // 上次修改时间
               pid_t           shm_cpid;    // 创建进程的 PID
               pid_t           shm_lpid;    // 上一次执行shmat(2)/shmdt(2)的进程的 PID
               shmatt_t        shm_nattch;  // 当前进程
               ...
            }
            #include <sys/shm.h>
            #include <sys/ipc.h>
                int shmget(key_t key, size_t size, int shmflg);
                    创建共享内存,失败返回-1,成功返回共享内的标识码(32位)
                    * key: 共享内存的名字,如果key之前是存在的一个共享内存的标识符的话   直接返回该共享内存的标识符
                    * size: 共享内存的大小
                    * shmflg: 共享内存的使用权限,9个权限你懂的
                        创建新的共享内存区，需要在 flag 中指定 IPC_CREAT 标识
                        shmflg = IPC_CREAT | 0666
                void *shmat(int shmid, const void *shmaddr, int shmflg);
                    将共享内存连接到进程的地址空间,返回共享内存的地址指针
                    * shmid: 共享内存的标识(shmget返回的标识符)
                    * shmaddr: 连接的地址
                        1. NULL: 内核自动识别第一个地址
                        2. 不是 NULL 但是 shmflg 没有 SHM_RND 标记，则使用 shmaddr
                        3. 不是 NULL 但是 shmflg 设置了 SHM_RND 标记，使用 shmaddr - (shmaddr % SHMLBA)
                        4. shmflg = SHM_RDONLY 表示是只读共享内存
                    * shmflg: SHM_RND / SHM_RDONLY 权限,一般是0
                int shmdt(const void *shmaddr);
                    将共享内存脱离当前进程的地址空间，成功返回0失败返回-1
                    shmaddr: 要指定脱离的共享内存的指针
                int shmctl(int shmid, int cmd, struct shmid_ds *buf);
                    控制共享内存,成功返回0失败返回-1
                    * shmid: 共享内存的标识码(shmget 返回)
                    * cmd: 执行的动作
                        1. IP_STAT: 将共享内存的相关参数写入到shmid_ds数据结构中返回获取
                        2. IP_SET: 将共享内存的相关参数设置成是 shmid_ds 数据结构中的参数
                        3. IPC_RMID: 删除共享内存
                    * buf: 指向一个辅助的数据结构

    8. 消息队列
        #include <sys/msg.h>
        1. 进程之间的通信使用消息队列建立，消息队列使用前申请使用后删除，进程不需要对消息队列进行附加或者解除操作
        2. 消息队列中的消息并不随着发送进程的关闭而删除，除非消息队列删除或者内核重启
        3. 消息队列发送按照顺序，但是接收并不一定按照顺序
        4. 消息被进程接收之后会从队列中删除
        5. 消息队列允许多个进程向它写入或读取消息
        6. 消息的基本结构
            struct my_msg
            {
                long mtype;             // 必须使用一个长整形开始指定消息的种类
                char mtext[LENGTH];     // 消息的内容数组随意
                ...                     // 除了第一个必须是一个长整形以外，其他的数据可以自定义
            }
        7. API
            1. 消息队列的获取
                int msgget(key_t key, int flag);
            2. 消息队列的控制
                int msgctl(int msqid, int cmd, struct msqid_ds *buf);
            3. 消息发送
                int msgsnd(int msgid, const void* msgp, size_t msgsz, int msgflg);
                    消息队列已满表示需要阻塞等待，但是可以再 msgflg 中立即返回错误信息
                * msgid: 消息队列的引用标识符
                * msgp: 要发送的消息的指针
                * msgsz: 消息的长度
            4. 消息的接收
                int msgrcv(int msgid, void *msgp, size_t msgsz, long int msgtype, int msgflg);
                * msgp: 接收消息的指针
                * msgsz: 接收缓冲区的大小
                    如果接收的消息大于缓冲区的大小
                    1. 默认操作为返回错误信息，消息依然留在队列中,接收操作失败
                    2. 可在 msgflg 中指定 MSG_NOERROR，则消息会以被截短的形式接收
                * msgtype: 接收消息的类型
                    1. msgtype = 0：返回队列中的第一个消息（忽略类型，按照消息的发送顺序接收）
                    2. msgtype > 0：返回队列中消息类型值为type的第一个消息
                    3. msgtype < 0：返回队列中消息类型值小于或等于type绝对值的一个消息，如果有多个满足条件的消息，则取类型值最小的第一个消息
                * msgflg:
                    1. 如果在消息队列中不存在等待消息，默认接收进程进入阻塞状态
                       同样可在 msgflg 中指定 IPC_NOWAIT 立即返回错误信息
                    2. 在 msgflg 中指定 IPC_EXCEPT 可返回消息队列中第一个与给定消息类型号不相等的消息
    
    9. 信号量机制
        1. 信号量是一个计数器用来对多进程的共享数据结构进行受限访问
        2. IPC信号量机制中采用信号量集（semaphore array），其中可包含一个或者多个信号量
        3. 信号量需要显示的申请和删除
        4. e.g.
            #include <sys/sem.h>
            int semget(key_t key, int nsems, int semflg);
                创建或者引用信号量集,返回引用的标识符 semid，失败返回-1
                1. key: 信号量集的关键字
                2. nsems: 信号量集中的信号量的个数
                    1. 创建信号量集的时候必须指定
                    2. 如果引用一个现有的信号量集，则将nsems置为0
                3. semflg: 包括权限的指定以及 IPC_CREAT、IPC_EXCL 等标志
                    1. IPC_CREAT | 0666
                    2. IPC_CREAT | IPC_EXCL : 创建一个信号量，如果信号量已经存在返回错误
        5. API
            操作模板
                struct sembuf
                {
                    ushort sem_num;     // 要操作的信号量在信号量集中的索引编号
                    short sem_op;       // 对信号量进行的操作值（可为正、负或0）
                    short sem_flg;      // 操作标志
                } 
                1. 资源不可以满足要求进程默认进入等待状态
                2. 若在 sem_flg 中指定标记 IPC_NOWAIT ，则进程不会等待，直接返回错误信息
                   若在 sem_flg 中指定 SEM_UNDO 标记，则系统会记录一个与调用进程相关的 UNDO 记录
                   用于当进程意外崩溃或是运行结束忘记释放资源时，系统会自动回滚操作，恢复信号量的计数值
                3. sem_op值为正，对应于进程释放资源数(V操作 +1)；sem_op值为负，对应于进程请求资源数(P操作 -1)

            int semop(int semid, struct sembuf semarray[], unsigned int nsops);
                改变信号量的值
                1. semarray[ ]中记录了一系列对于信号量集的操作，即通过多个操作模板的指定
                   可以通过一次执行semop函数，**批量**地对信号量进行不同的操作
                2. nsops表示需要执行的semarray[ ]中的元素数目，>= 1

            int semctl(int semid, int semnum, int cmd, union semun arg)
                该函数用来直接控制信号量信息
                1. cmd: 具体的操作
                    1. SETVAL: 用来把信号量初始化为一个已知的值,这个值通过union semun中的val成员设置，其作用是在信号量第一次使用前对它进行设置
                        初始化信号量使用
                    2. IPC_RMID:
                        用于删除一个已经无需继续使用的信号量标识符
                    3. GETVAL： 返回某个信号量成员的当前值,**不需要 arg 参数,函数返回值就是对应的信号量的值**
                    4. SETALL： 设置所有信号量成员的值
                    5. GETNCNT：返回当前等待资源的进程个数
                2. 结构 semun 用于设置或者返回信号量信息，具体功能依赖于cmd的取值
                    union semun
                    {
                        int val;                    // 用于信号量的赋值
                        struct semid_ds *buf;       // 用于返回信号量集信息
                        unsigned short *array;      // 用于设置或者获取信号量集成员的取值
                    } 

            P/V 操作的封装
            1. P
                void p(int sem_id, int sem_num)
                {
                    struct sembuf xx;
                    xx.sem_num = sem_num;       // 设置需要操作的信号量在信号量集中的索引编号
                    xx.sem_op = -1;             // P
                    xx.sem_flg = 0;
                    semop(sem_id, &xx, 1);      // 信号量执行 P 操作
                }

            2. V
                void v(int sem_id, int sem_num)
                {
                    struct sembuf xx;
                    xx.sem_num = sem_num;
                    xx.sem_op = 1;
                    xx.sem_flg = 0;
                    semop(sem_id, &xx, 1);
                }
*/

#define SEMKEY 300

union semun
{
   int val;
   struct semid_ds *buf;
   unsigned short *array; 
};

struct my_msg
{
   long type;
   char text[200];
};

void unname_pipeline()
{
    // 子进程通过管道向父进程发送消息
    pid_t pid;
    int fdes[2];
    char str[50] = "pipe message";
    char buf[50];
    // 创建管道
    pipe(fdes);
    pid = fork();
    if (pid == -1) 
    {
        printf("WRONG!");
        return ;
    }
    if(pid > 0) {
        // 父进程
        // 关闭写入端，只负责读取
        close(fdes[1]);
        wait(0);    // 等待子进程结束
        memset(buf, '\0', sizeof(buf));
        read(fdes[0], buf, 50);     // 从文件描述符中读取缓存数据
        printf("parent receive: %s\n", buf);
    } 
    else {
        // 子进程
        // 关闭读取端，只负责写入
        close(fdes[0]);
        write(fdes[1], str, strlen(str));
        printf("child send: %s\n", str);
    }
}

void unname_pipeline_foreign()
{
    // 调用功能外部程序的无名管道， foreign.c
    pid_t pid;
    int fdes[2];
    char buf[50], param[50];
    pipe(fdes);
    pid = fork();
    if(pid > 0) {
        // 父进程，父进程关闭写入端，只负责读取
        close(fdes[1]);
        sleep(1);   // 休眠 1s
        memset(buf, '\0', sizeof(buf));
        read(fdes[0], buf, 50);       // 从管道中读取文件
        printf("parent receive: %s\n", buf);
    }
    else {
        // 子进程，子进程只写入数据
        close(fdes[0]);
        sprintf(param, "%d", fdes[1]);
        execl("./foreign", "other", param, NULL);    // argv[0] = "other"
        exit(0);
    }
}

void copy_file()
{
    int fd, fd2;
    char buf[50];
    fd = open("./foreign.c", O_RDONLY);
    // fd2 = fd;       // 错误的复制文件描述符
    // 文件开启了两个文件描述符，关闭其中一个对另一个文件描述符不存在影响
    fd2 = dup(fd);
    close(fd);
    read(fd2, buf, sizeof(buf));
    printf("%s\n", buf);
    close(fd2);
}

void change_pipeline_to_stdio()
{
    // 父进程向子进程通信
    int fdes[2];
    pid_t pid;
    char buf[50];                   // 子进程
    char str[50] = "pipe-message";  // 父进程
    pipe(fdes);
    pid = fork();
    if(pid == 0) {
        // 子进程，关闭写入端只负责读取
        close(fdes[1]);
        dup2(fdes[0], 0);   // 子进程的端替换成标准输入
        memset(buf, '\0', sizeof(buf));
        scanf("%s", buf);  // 通过标准输入将数据写入到管道中
        printf("%s\n", buf);
    }
    else {
        // 父进程，关闭读取端父进程负责写入
        close(fdes[0]);
        dup2(fdes[1], 1);   // 将标准输入的文件描述符替换成管道的输入端
        printf("%s", str);
    }
}

void check_popen()
{
    // 外部调用函数 foreign2.c
    char line[30];
    FILE *fpin, *fpout;
    fpin = fopen("./daxie", "r");
    fpout = popen("./foreign2", "w");       // 创建管道，子进程从管道中接收数据,读取代码文本，父进程是写入端
    while(fgets(line, sizeof(line) - 1, fpin) != NULL)          // 从文件中接收输入
    {
        fputs(line, fpout);
    }
    pclose(fpout);
    return ;
}

void name_pipeline_send()
{
    // 接收进程在 namepipeline.c 中
    int fd;
    mkfifo("/tmp/myfifo", 0777);
    while(1) {
        fd = open("tmp/myfifo", O_WRONLY);      // 只写
        write(fd, "pipeline message", 16);
        printf("send: pipeline message\n");
    }
    close(fd);
}

void share_memory()
{
    int SHMKEY = 100;
    int *pint, shmid;
    pid_t pid, pid2;
    char *addr;
    time_t now;         // 记录操作时间
    // 创建共享内存
    shmid = shmget(SHMKEY, 1024, 0666|IPC_CREAT);
    pid = fork();
    if(pid > 0) {
        // 父进程
        pid2 = fork();
        if(pid2 == 0) {
            // 子进程2执行外部程序 other
            execl("other", "other", 0);
        }
        // 父进程或者子进程2连接到共享内存
        addr = shmat(shmid, 0, 0);
        // 向共享内存中写入数据 20
        pint = (int *)addr;
        *pint = 20;
        time(&now);     // 获取时间戳
        printf("%d: process #1 write: %d\n", now, *pint);
        sleep(5);       // 休眠 5s等待另一个进程去读
        time(&now);     // 获取时间戳
        printf("%d: process #1 read: %d\n", now, *pint);
        shmdt(addr);
    } else if(pid == 0) {
        // 子进程1
        addr = shmat(shmid, 0, 0);
        sleep(1);
        pint = (int*)addr;
        time(&now);
        printf("%d: process #2 read: %d\n", now, *pint);
        sleep(1);
        time(&now);
        *pint = 500;
        printf("%d: process #2 write: %d\n", now, *pint);
        shmdt(addr);
    }
}

void msgfifo()
{
    int MSGKEY = 200;
    int msgid;
    struct my_msg msgs, msgr;
    pid_t pid, pid2;
    time_t now;
    msgid = msgget(MSGKEY, 0666 | IPC_CREAT);
    pid = fork();
    if(pid > 0)
    {
        // 父进程
        pid2 = fork();
        if(pid2 == 0)
        {
            // 子进程2,执行外部程序 other2, other2 只负责接收
            execl("other2", "other2", 0);
        } 

        // 父进程发送,发 2 收 1
        msgs.type = 1;  // 定义1号类型数据
        sprintf(msgs.text, "message #1 type=%d", msgs.type);    // 写入1号类型数据的消息
        msgsnd(msgid, &msgs, strlen(msgs.text) + 1, 0);         // 发送1号消息到消息队列
        time(&now);                                             // 计算发送时间
        printf("%d: process #1 send: %s\n", now, msgs.text);    
      
        msgs.type = 2;  // 定义2号类型数据
        sprintf(msgs.text, "message #2 type=%d", msgs.type);
        msgsnd(msgid, &msgs, strlen(msgs.text)+1, 0);
        time(&now);
        printf("%d: process #1 send: %s\n", now, msgs.text);

        sleep(5);       // 休眠 5(s)
        time(&now);
        memset(msgr.text,'\0', sizeof(msgr.text));
        msgrcv(msgid, &msgr, sizeof(msgr.text), 0, 0);      // 返回消息队列的第一个消息
        printf("%d: process #1 receive: %s\n", now, msgr.text);
    }
    else if (pid == 0) {
        // 子进程1, 收 1 发 2
        sleep(2);
        time(&now);
        memset(msgr.text, '\0', sizeof(msgr.text));
        msgrcv(msgid, &msgr, sizeof(msgr.text), 0, 0);      // 返回消息队列的第一个消息
        printf("%d process #2 receive:%s\n", now, msgr.text);
      
        sleep(1);
        // 发送 1 号消息
        msgs.type = 1;
        sprintf(msgs.text, "message #3 type=%d", msgs.type);
        msgsnd(msgid, &msgs, strlen(msgs.text)+1, 0);
        
        time(&now);
        printf("%d: process #2 send: %s\n", now, msgs.text);

        // 发送 2 号消息
        msgs.type = 2;
        sprintf(msgs.text, "message #4 type=%d", msgs.type);
        msgsnd(msgid, &msgs, strlen(msgs.text)+1, 0);
        time(&now);
        printf("%d: process #2 send: %s\n", now, msgs.text);
    }
}

void sem_use(int semid, char* filepath, int pid)
{
    // P 操作
    struct sembuf se;
    time_t now;
    int i;
    se.sem_num = 0;
    se.sem_op = -1;
    se.sem_flg = 0;
    semop(semid, &se, 1);

    // 临界区
    // 追加方式打开文件
    FILE *file;
    file = fopen(filepath, "a");

    for(i = 0; i < 3; i++)
    {
        time(&now);
        fprintf(file, "%d: file operation by process %d\n", now, getpid());
        sleep(1);
    } 

    // V 操作
    se.sem_num = 0;
    se.sem_op = 1;
    se.sem_flg = 0;
    semop(semid, &se, 1);
}

void set_semvalue(int id, int val)
{
    union semun sem;
    sem.val = val;
    if (semctl(id, 0, SETVAL, sem) == -1) {
        printf("error to set value about mutex_sem.\n");
        exit(0);
    }
}

void get_semvalue(int id)
{
    union semun sem;
    int ans = semctl(id, 0, GETVAL);
    if (ans == -1) {
        printf("error to get value from mutex_sem.\n");
        exit(0);
    }
    else {
        printf("get the sem value %d\n", ans);
    }
}

void sem_main()
{
    union semun sem_val;
    int semid, pid, pid2;
    
    // 获取信号量标识符
    semid = semget(SEMKEY, 1, 0666|IPC_CREAT);
    
    // 信号量初始化
    sem_val.val = 1;
    semctl(semid, 0, SETVAL, sem_val);

    get_semvalue(semid);

    pid = fork();
    if(pid > 0) {
        // 父进程
        pid2 = fork();
        if(pid2 == 0)
        {
            // 子进程2, other3.c
            printf("child2: %d\n", getpid());
            execl("./other3", "other3", 0);
        }
        sem_use(semid, "./sem_test", getpid());
        printf("father: %d\n", getpid());
    }
    else {
        // 子进程1
        printf("child1: %d\n", getpid());
        sem_use(semid, "./sem_test", getpid());
    }
}

int main(int argc, char* argv[])
{
    // unname_pipeline();
    // unname_pipeline_foreign();
    // copy_file();
    // change_pipeline_to_stdio();
    // check_popen();
    // name_pipeline_send();
    // name_pipeline_receive();
    // share_memory();
    // msgfifo();
    sem_main();
    return 0;
}
