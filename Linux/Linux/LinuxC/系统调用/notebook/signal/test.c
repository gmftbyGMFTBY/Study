#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/*
   父进程创建子进程
   子进程结束发送信号 SIGCHLD 给父进程
   重写父进程的 SIGCHLD 信号处理函数，提前终止父进程
 */

int delay;
void childhandle();

int main(int argc, char* argv[])
{
    int pid;
    signal(SIGCHLD, childhandle);
    pid = fork();

    if (pid == 0) {
        execvp(argv[2], argv[2]);
    }
    else {
        sscanf(argv[1], "%d", &delay);
        sleep(delay);
        printf("child %d execeed limit and is being killed\n", pid);
        kill(pid, SIGINT);      // send the signal to the child to end, child will send the SIGCHLD signal to the parent process to execute the childhandle function
    }
    return 0;
}

void childhandle()
{
    int childpid, childstatus;
    childpid = wait(&childstatus);
    printf("child %d terminated within %d s\n", childpid, delay);
    exit(0);
}
