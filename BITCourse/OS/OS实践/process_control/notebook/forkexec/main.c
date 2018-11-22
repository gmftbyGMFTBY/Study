#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>       // 进程等待
#include <sys/stat.h>       // 文件信息
#include <fcntl.h>          // 文件操作库函数
#include <dirent.h>         // 目录操作

/*
fork:
   1. 子进程是父进程的一个副本，具有独立的地址空间，变量不共享
   2. 子进程的修改不会影响父进程
   3. 函数返回进程的 pid, 父进程返回子进程 pid, 子进程返回 0, -1 fork 错误

        // the definiation of the fork function
        pid_t fork(void);
 */

/*
vfork:
   1. 返回值的定义和 fork 相同
   2. 在子进程 exec / exit 之前，父进程挂起，子进程先运行
   3. 在子进程 exec / exit 之前，父进程和子进程共享地址空间,共享内存
   4. 因为在没有 exec / exit 之前，因为地址空间共享，子进程可以对父进程的数据空间进行修改

        // the definiation of the vfork function
        pid_t vfork(void);
 */

/*
getpid:
   获取当前进程的 pid
   pid_t getpid(void)
getppid：
   获取父进程的 pid
   pid_t getppid(void)
 */

/*
exit:
   关闭所有的 I/O 标准流,清理 I/O 缓冲区,进入操作系统内部进行系统调用回收进程
_exit:
   直接进入核心，操作系统调用处理进程回收工作
 */

/*
exec函数族:
进程调用运行外部程序，原来进程的代码段，数据段，堆栈段废弃，系统重新分配,新进程从 main 来时执行，进程号保持不变
    1. int execl (const char *path, const char *arg0, ..., (char *)0);
        二进制可执行文件，可以是 linux 命令
    2. int execlp (const char *file, const char *arg0, ..., (char *)0);
        可执行 shell 脚本
    3. int execle (const char *path, const char *arg0, ..., (char *)0, char *const envp[]);
        二进制可执行文件，可以是 linux 命令,可以指定环境
    4. int execv (const char *path, char *const argv[] );
        二进制可执行文件，可以是 linux 命令
    5. int execvp (const char *file, char *const argv[] );
        可以执行 shell 脚本
    6. int execve (const char *path, char *const argv[], char *const envp[] );
        二进制可执行文件,可以指定环境

    **子进程执行完挖补程序之后直接结束，不会返回父进程的代码，直接 exit 并向父进程报告状态**
    **甚至可以调用 python 程序，理论上是任何在系统中可以执行的程序 (x 权限)**
 */

/*
wait:
父进程等待子进程终止
    #include <sys/wait.h>
    pid_t wait(int *statloc);
    int* statloc 保存子进程终止状态码,可以显示子进程是如何技术,返回值是子进程的 pid

waitpid
    #include <sys/types.h>
    #include <sys/wait.h>
    pid_t waitpid(pid_t pid, int *statloc, int options)
    * 父进程可以指定等待 pid 号子进程
        1. pid > 0: pid 完全匹配
        2. pid = 0: 匹配是同一个进程组的任何子进程
        3. pid = -1: 匹配任何子进程
        4. pid < -1: 匹配任何进程组标识等于 pid 绝对值的任何终止子进程
    * options = WNOHANG,表示没有任何子进程终止立即返回0
    * wait 表示如果没有子进程结束，父进程一直等待，waitpid 可以选择不挂起立即返回(options选项)
 */

/*
pause:
进程暂停,进程挂起知道捕捉到一个新信号然后处理程序返回
    int pause();
 */

/*
slepp:
进程的挂起
unsigned int sleep(unsigned int seconds);    // 秒单位
void usleep(unsigned long usecs);            // 微妙单位, 1 s = 1e-6 微秒

当进程接收到信号并从处理程序返回之后，sleep函数直接结束返回剩余的秒数
 */

/*
　  文件系统
        1. S_ISREG(st_mode): 一般意义上的文件
        2. S_ISDIR(st_mode): 目录文件
        3. S_ISCHR(st_mode): 字符设备文件,无缓冲的方式提供对设备的可变长访问
        4. S_ISBLK(st_mode): 块设备文件,缓冲的方式提供对设备的固定长度访问
        5. S_ISLNK(st_mode): 符号连接文件
        6. S_ISFIFO(st_mode): 命名管道文件，进程通信
        7. S_ISSOCK(st_mode): 网络套接字文件,进程网络通信
    文件的属性信息
        struct:
            1. dev_t: 文件的设备号
            2. ino_t: inode 节点编号
            3. mode_t: 文件类型
            4. st_nlink: 硬链接数目
            5. st_uid: 文件拥有者的 ID
            6. st_gid: 文件的属主的 ID
            7. st_rdev: 设备种类
            8. st_size: 文件的大小
            9. st_blksize: I/O 块的长度
            10. st_blocks: 实际分配的块数
            11. st_atime: 最后访问时间戳
            12. st_mtime: 内容最后修改时间
            13: st_ctime: 文件最后状态改变时间
    文件信息提取函数族
        #include <sys/stat.h>
        struct stat buf;    // 文件属性的结构体

        int stat(const char* filename, struct stat* buf): 统计符号链接文件指向的文件
        int lstat(const char* filename, struct stat* buf): 统计符号连接文件本身
        int fstat(int filedes, struct stat* buf)
            1. filename: 文件位置路径
            2. buf: 文件的信息统计描述
            3. filedes: 文件描述符  
 */

/*
   文件是否存在
       #include <fcntl.h>
       access(const char* path, mode)
       文件如果不存在返回 -1
   文件打开操作:
       #include <fcntl.h>
       int open(const char* filename, int oflg, mode_t mode);

       1. filename: 文件路径信息
       2. oflg: 文件打开方式,必选项并且一次只可以选中一个
            * O_RDONLY: 只读
            * O_WRONLY: 只写
            * O_RDWR: 可读可写
       3. mode: 文件的权限信息,当指定的文件不存在的时候，该参数可以用来创建对应权限的文件
       文件打开成功返回文件描述符(非负整数),否则返回 -1

    文件关闭操作:
        #include <unistd.h>
        int close(int fd);    // 按照问价描述符关闭文件
        操作成功返回0,失败返回-1

    文件创建操作:
        int creat(const char* pathname, mode_t mode);
            新文件采用只写方式打开，关闭之前不能读取
            mode的格式:
                00xxx - umask
                e.g.:
                    00400: 只有拥有者有可读的权限
        int unlink(const char* pathname);
            根据路径删除文件

    文件读写操作:
        ssize_t read(int fd, void* buf, size_t nbytes);
            * 读取成功返回读取的字节数
            * 如果在文件的末尾返回 0
            * 读取失败返回 -1
            * 实际中在快读取到文件的末尾的时候，返回值(实际督导的字节数目)很可能小于指定的长度
        ssize_t write(int fd, const void* buf, size_t nbytes);
            * 成功写入返回写入的字节数目
            * 写入失败返回 -1


            1. fd: 文件描述符
            2. buf: 文件读取和写入的缓冲区
            3. nbytes: 制定读去和写入的字节数目
            4. read / write 会更改文件的读写指针

    文件指针重定位
        int lseek(int fd, long offset, int sbase);
        * sbase: 偏移位置,0绝对偏移地址，文件开始
                 1,当前位置 SEEK_CUR
                 2,文件末尾 SEEK_END
        * offset: 偏移的数目
        * fd: 文件描述符

        函数成功执行，返回新的读写位置，定位的位置小于文件开始则从文件开始定位，定位的位置可以大于文件的长度，中间的位置使用0填充

    检查是否可以对文件执行某种操作
        检查调用进程是否可以对指定的文件执行某种操作。   
        #include <unistd.h>
        #include <fcntl.h>

        int access(const char *pathname, int mode);   
  
        参数： 
        pathname: 需要测试的文件路径名。   
        mode: 需要测试的操作模式，可能值是一个或多个R_OK(可读?), W_OK(可写?), X_OK(可执行?) 或 F_OK(文件存在?)组合体。 
  
        返回说明： 
        成功执行时，返回0。失败返回-1，errno被设为以下的某个值 
        EINVAL： 模式值无效   
        EACCES： 文件或路径名中包含的目录不可访问 
        ELOOP ： 解释路径名过程中存在太多的符号连接 
        ENAMETOOLONG：路径名太长 
        ENOENT：  路径名中的目录不存在或是无效的符号连接 
        ENOTDIR： 路径名中当作目录的组件并非目录 
        EROFS： 文件系统只读 
        EFAULT： 路径名指向可访问的空间外 
        EIO：  输入输出错误 
        ENOMEM： 不能获取足够的内核内存 
        ETXTBSY：对程序写入出错
 */

/*
   文件的硬链接和软链接
   int link(const char* oldpath, const char* newpath);
        硬链接
   int symlink(const char* oldpath, const char* sympath);
        符号链接
 */

/*
目录的创建和删除
    int mkdir(cosnt char* dir_pathname, mode_t name);
    int rmdir(const char* dir_pathname);    // 只可以删除空目录

目录的打开，读取，关闭
    DIR * opendir(const char* name);        // 打开目录
    struct dirent* readdir(DIR* dir);       // 读目录,可以重复调用，顺序访问所有的目录项
    int closedir(DIR* dir);                 // 关闭目录

    struct dirent
    {
       ino_t d_ino;                 // inode 索引节点号
       char d_name[NAME_MAX+1];     // 文件名数组
    }

当前目录的定位和获取
    int chdir(const char* path);
        更换当前的工作目录到指定的路径上
    int fchdir(int fd);
        更换当前的工作目录到一个打开的文件描述符上(打开目录)
    char* getcwd(char* buf, size_t size);
        获取当前的工作目录，将绝对路径复制到 buf
        if size > 0,size过小可能会导致获取失败
        buf 可以是 NULL, 系统自动分配空间,当是 NULL 的时候，将结果当成字符串
        size 如果是0,系统自动的分配空间
 */

/*
获取时间 - gettimeofday()
    #include <sys/time.h>
    int gettimeofday(struct timeval* tv, struct timezone *tz);
    程序执行成功返回0, 失败返回-1

    1. 时间值
    struct timeval{
      long tv_sec;      // 1970 ~ current 秒
      long tv_usec;     // 微秒，当前秒数下的微妙
    }

    2. 时区
    struct timezone{
      int tz_minuteswest;  // 和格林尼治相差的时间(分钟)
      int tz_dsttime;
    }
 */

void test_fork()
{
    int glob = 3;
    pid_t pid;
    int loc = 3;
    printf("before fork, glob = %d, loc = %d.\n", glob, loc);
    if ((pid = fork()) < 0)
    {
        printf("fork failed.\n");
        exit(0);
    }
    else if (pid == 0)
    {
        // 子进程
        glob ++;
        loc --;
        printf("child process change the glob and loc.\n");
        printf("glob = %d, loc = %d.\n", glob, loc);
    }
    else
    {
        printf("father process do not change.\n");
        printf("glob = %d, loc = %d\n", glob, loc);
    }
    return ;
}

void test_vfork()
{
    int glob = 3;
    pid_t pid;
    int loc = 3;
    printf("before fork, glob = %d, loc = %d.\n", glob, loc);
    if((pid = vfork()) < 0)
    {
        printf("vfork failed!\n");
        exit(0);
    }
    else if(pid == 0)
    {
        // 子进程
        glob ++;
        loc --;
        printf("child process change the glob and loc.\n");
        printf("glob = %d, loc = %d.\n", glob, loc);
        // 子进程必须及时结束
        exit(0);
    }
    else
    {
        printf("father process do not change the glob and loc.\n");
        printf("glob = %d, loc = %d.\n", glob, loc);
    }
}

void test_exec()
{
    // 调用 foreign 可执行程序，打印命令行参数
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        execl("./foreign", "arg1", "arg2", "arg3", 0);
    }
    // 父进程等待子进程结束才结束
    wait(0);
    exit(0);
}

void check_file_stat()
{
    int i;
    struct stat buf;
    stat("./foreign", &buf);
    if (S_ISREG(buf.st_mode))
    {
        printf("regular file.\n");
    }
    else if(S_ISLNK(buf.st_mode))
    {
        printf("link file.\n");
    }
    else
    {
        printf("other file.\n");
    }
    printf("size: %ld bytes.\n", buf.st_size);
    printf("last access: %ld.\n", buf.st_atime);
}

void check_file_lstat()
{
    int i;
    struct stat buf;
    lstat("./ppp", &buf);
    if (S_ISREG(buf.st_mode))
    {
        printf("regular file.\n");
    }
    else if(S_ISLNK(buf.st_mode))
    {
        printf("link file.\n");
    }
    else
    {
        printf("other file.\n");
    }
    printf("size: %d bytes\n", buf.st_size);
    printf("last access: %d\n", buf.st_atime);
}

void check_file_fstat()
{
    int i;
    struct stat buf;
    int fd;
    // 打开文件，获得文件描述符 fd
    fd = open("./ppp", O_RDONLY);
    fstat(fd, &buf);

    if (S_ISREG(buf.st_mode))
    {
        printf("regular file.\n");
    }
    else
    {
        printf("other file.\n");
    }
}

void create_file()
{
    int mode = 00772;
    int res = creat("./made.c", mode);
    close(res);
}

void delete_file()
{
    int res = unlink("./made.c");
}

void read_file()
{
    int fd;
    char t[10];    // 缓冲区
    char r[10] = "newline\n";
    // 可读可写
    fd = open("made.c", O_RDWR);
    read(fd, &t, 5);
    printf("%s\n", t);
    // 当前向下偏移 7 个字节
    lseek(fd, 7, SEEK_CUR);
    read(fd, &t, 5);
    printf("%s\n", t);
    // 定位到文件最后
    lseek(fd, 0, SEEK_END);
    // 在最后写入新行
    write(fd, &r, strlen(r));
    close(fd);
}

void get_dir()
{
    char* p;
    DIR * dirptr = NULL;
    struct dirent* entry = NULL;
    // 切换到制定的目录并打印
    chdir("../");
    p = getcwd(NULL, 0);
    printf("Current Dir: %s\n", p);
    // 打开当前目录
    dirptr = opendir(".");
    while (entry = readdir(dirptr))
    {
        printf("%s\n", entry->d_name);
    }
    closedir(dirptr);
}

void get_time()
{
    struct timeval tv;
    gettimeofday(&tv);
    printf("tv_sec: %d\n", tv.tv_sec);
    printf("tv_usec: %d\n", tv.tv_usec);
}

int main()
{
    // test_vfork();
    // test_exec();
    // check_file_fstat();
    // create_file();
    // delete_file();
    // read_file();
    get_dir();
    // get_time();
    return 0;
}
