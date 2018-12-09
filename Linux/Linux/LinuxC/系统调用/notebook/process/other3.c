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

#define SEMKEY 300

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

int main()
{
    int semid;
    semid = semget(SEMKEY, 0, 0666);
    sem_use(semid, "./sem_test", getpid());
}