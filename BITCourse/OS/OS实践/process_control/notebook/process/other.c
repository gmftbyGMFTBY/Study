#include <stdio.h>                                                                         #include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>

#define SHMKEY 100

int main()
{
    int *pint, shmid;
    char* addr;
    time_t now;
    // 外部进程通过描述符获取到共享内存 100
    shmid = shmget(SHMKEY, 1024, 0666);
    addr = shmat(shmid, 0, 0);
    sleep(1);
    time(&now);
    pint = (int*)addr;
    printf("%d: process #3 read: %d\n", now, *pint);
    sleep(3);
    time(&now);
    pint = (int*) addr;
    printf("%d process #3 read: %d\n", now, *pint);
    shmdt(addr);        // 解除共享内存
    return 0;
}
