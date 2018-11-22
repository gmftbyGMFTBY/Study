#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <signal.h>

/*
   文件系统调用
   1. open
        int open (char* filename, int mode, in permission)
        1. filename: 文件名字符串
        2. mode: 打开模式, O_RDONLY, O_WRONLY, O_RDWR
        3. permission: 文件不存在的时候，创建的属性值

    2. read
        ssize_t read(int fd, void* buf, size_t count)
        1. fd: 文件描述符
        2. buf: 读入缓冲区
        3. count: 读取的字节数目

        文件读取成功，返回读取的字节数亩，否则失败返回 -1
        如果返回 0 ,表示到达文件的末尾

    3. write
        ssize_t write(int fd, void* buf, size_t count)
        从 buf 中读取 count 个数据到指定的文件描述符中,返回文件的写入字节数，否则返回 0

    4. lseek
        off_t lseek(int fd, off_t offset, int mode)
        返回当前文件的指针位置
        1. fd: 文件描述符
        2. offset: 偏移整数
        3. mode: 偏移类型
            1. SEEK_SET
            2. SEEK_CUR
            3. SEEK_END

    5. close
        int close(int fd)
        回收对应的文件的内核资源，一个进程结束的时候，应当对文件进行关闭
        调用成功呢返回0,失败返回 -1
        关闭文件并不会立即写入数据

    6. unlink 
        int unlink(const char* fileName)
        删除文件
        调用成功返回0,失败返回-1

    7. 目录文件
        #include <dirent.h>
        DIR* opendir(const char* dirname);
            打开一个目录文件，创建目录文件流，返回一个目录指针
        int closedir(DIR* dirp);
            关闭目录流文件，成功返回0失败返回-1
        struct dirent* readdir(DIR* dirp);
            调用一次 readdir() 返回指向下一个目录项的指针，到达尾部返回 NULL 
            结构体声明
            struct dirent {
                long d_ino;                 // inode
                _kernel_off td_off;         // 目录开始到现在的偏移文件数目
                unsigned short d_reclen;    // 文件名长度
                char d_name[256];           // 文件名
            }

        定位目录位置
        long int telldir(DIR* dirp);
        指示当前的目录流中的位置

        seekdir(DIR* dirp, long long int loc)
        设定流位置， loc 是 telldir 得到的

        rewinddir(DIR* dir)
        流设定到头

        extern int mkdir(__const char* __path, __mode_t __mode)
        执行成功返回 0, 失败返回 -1
        1. char* 创建的目录的路径
        2. 访问权限

        extern int rmdir(__const char* __path)
        删除的文件的路径，删除成功返回0,是啊比返回 -1

    8. 工作路径
       extern char* getcwd(char* __buf, size_t __size)
        获取当前的工作路径并加入到 buf 中，绝对路径
        如果 buf 是 NULL, getcwd 自动 malloc 但是需要注意使用完之后的释放操作

       cd:
       extern int chdir(__const char* path);
       绝对路径
       执行成功返回0, 失败返回-1
            
 */

 /*
    进程管理，详见 其他笔记
    system(char* cmd)
        执行命令行参数，结果输出到标准输出上

    int nice(int delta)
        nice()在进程的当前优先级中添加delta。合法的优先级值在-20~+19之间。只有超级用户（root）才能指定导致负值的delta。
        如果调用成功，返回新的nice值，调用失败返回-1

    pid_t wait(int* status)     
        1. 子进程结束会给父进程发送信号 SIGCHLD 通知父进程
        2. 返回终止的子程序的名称，状态吗在 status 中保存返还给父进程
        3. 终止的进程在父进程接受它的返回码之前不能离开系统。如果它的父进程已经死亡，它将成为孤儿被init收养。如果它的父进程还活着，但一直都没执行wait()接受子进程的返回码，该进程就成为僵尸进程

  */

 /*
    信号处理 #include <signal.h>
    多进程的情况下，子进程死亡向父进程发送 SIGHLD 信号

    kill -l         # 查看所有信号
    int pause(void)
        挂起调用pause的进程，当进程收到信号的时候返回正常运行，用于高效的等待信号，不返回任何信息

    unsinged int alarm(unsigned int count)
        alarm()指示内核在经过count指定的秒数后发送SIGALARM信号(14)
        默认的动作是终止进程

    void (*signal (int sigCode, void (*func) (int) )) (int)
        SIGKILL / SIGSTP 不可重新编程，因为这两个信号是管理员用来删除指定进程的操作信号
        子进程在fork()执行期间继承父进程的信号设置。当进程执行exec()时，以前被除忽略的信号仍然被忽略
        除了SIGCHLD外，信号不进行堆栈。即，如果一个进程正在休眠，有三个完全相同的信号发送给它，实际处理的只有一个信号
        还可以覆盖信号处理程序,signal允许进程指定在收到特定信号时所执行的操作
        函数失败返回 -1,调用成功返回和 sigCode 前一个关联的函数指针(常用来保护被替换的原来的函数，比如 Ctrl_C)
        1. sigCode: 重新编程的信号值, SIGALARM(14) 均可
        2. func: 
            1. SIG_IGN, 忽略信号
            2. SIG_DEL: 使用内核默认的信号处理程序
            3. 用户定义的函数地址

    kill 系统调用发送信号
    int kill (pid_t pid, int sigCode)
    成功返回0, 失败返回 -1
        发送信号 sigCode 给 pid 进程
        1. 发送进程和接收进程属主相同
        2. 发送进程属主是 root
    运作方式
        1. 如果pid是0，信号发送给发送者的进程组中的所有进程
        2. 如果pid是-1并且发送者由超级用户拥有，信号发送给所有进程，也包括发送进程
        3. 如果如果pid是-1并且发送者不是由超级用户拥有，信号发送给发送进程所有者拥有的全部进程，不包括发送进程

        kill(pid1, SIGSTOP);        // 挂起进程，暂停进程
        kill(pid1, SIGCONT);        // 解挂回复进程
        kill(pid1, SIGINT);         // 终止进程
  */

void protect_ctrl_c()
{
    void (*oldhandle)();    // hold the function of the ctrl-c
    printf("change the ctrl-c\n");
    oldhandle = signal(SIGINT, SIG_IGN);
    sleep(3);
    printf("restore the ctrl-c\n");
    signal(SIGINT, oldhandle);
    sleep(3);
}

int alarmflag = 0;

void alarmhandle()
{
    printf("get an alarm clock signal!\n");
    // change the variable
    alarmflag = 1;
}

void change_alram_func()
{
    // 使用函数 void alarmhandle() 作为自定义函数
    signal(SIGALRM, alarmhandle);

    // 3s 后发出 14 信号
    alarm(3);
    printf("looping ...\n");

    while (!alarmflag) {
        pause();
    }
    printf("end the looping\n");
}

void solve_alarm()
{
    alarm(1);
    // 1s 之后终止循环
    while(1);
}

void nice()
{
    system("ps -l");
}

void get_cwd()
{
    char buf[100];
    memset(buf, '\0', sizeof(buf));
    getcwd(buf, sizeof(buf));
    printf("%s\n", buf);
}

void changedir()
{
    int res = chdir("/home/lantian");
    if (res == -1) {
        printf("chaneg dir error!\n");
    }
    get_cwd();
}

void read_dir(char* dirname)
{
    long long int first_no;
    DIR* dirp;
    struct dirent* dp;
    dirp = opendir(dirname);
    int ti = 0;
    while ((dp = readdir(dirp)) != NULL) {
        if (ti == 1) first_no = telldir(dirp);
        ti++;
        if (dp->d_name[0] == '.') continue;
        printf("filename: %s, ", dp->d_name);
        long long int res = telldir(dirp);
        printf("telldir: %lld\n", res);
    }

    rewinddir(dirp);
    dp = readdir(dirp);
    printf("%s\n", dp->d_name);
    closedir(dirp);
}

void unlink_hard(char* filename)
{
    int res = unlink(filename);
    if (res != -1) {
        printf("delete successfully!\n");
    }
    else {
        printf("delete error!\n");
    }
}

int open_file()
{
    int fd;
    fd = open("test", O_RDONLY, 0600);
    if (fd == -1) {
        printf("Open the file error!\n");
        return -1;
    }
    else {
        printf("Open correctly!\n");
        return fd;
    }
}

int read_file()
{
    int fd = open_file();
    char buf[10];
    memset(buf, '\0', sizeof(buf));
    int res = read(fd, buf, sizeof(buf));
    buf[9] = '\0';
    printf("%d: %s\n", res, buf);
    return 1;
}

int main(int argc, char* argv)
{
    protect_ctrl_c();
    return 0;
}
