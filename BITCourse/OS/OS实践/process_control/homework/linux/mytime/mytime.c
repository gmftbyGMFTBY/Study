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
   模拟 time 命令，计算程序运行的时间
 */

int main(int argc, char* argv[])
{
    // 异常检测
    if (argc > 2)
    {
        printf("Too many feature, WRONG!\n");
        exit(0);
    }

    pid_t pid;

    if((pid = fork()) < 0)
    {
        printf("fork failed.\n");
    }
    else if( pid == 0 )
    {
        // 子进程开启
        execv(argv[1], 0);
    }
    else
    {
        // 父进程统计时间
        struct timeval t1;
        gettimeofday(&t1);
        wait(0);
        struct timeval t2;
        gettimeofday(&t2);
        printf("%d (s), %d (us)\n", t2.tv_sec - t1.tv_sec, t2.tv_usec - t1.tv_usec);
    }
    return 0;
}
