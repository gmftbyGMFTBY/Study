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

#define MINE_RAND_MAX 5
#define MAX_LENGTH    6     // 缓冲区长度

/*
    随机数
        1. 设置种子: srand(int)
        2. 获得随机数: rand() % RAND_MAX
*/

/*
    切忌一定运行过一次后一定要删除对应的信号量
    ipcrm -a
*/

union semun
{
   int val;
   struct semid_ds *buf;
   unsigned short *array; 
};

// 消息队列数据结构
struct pos_msg
{
    // 6, 7
   long type;
   int pos;
};

struct data_msg
{
    // 0, 5
    long type;
    char text[10];
};

// P, V 操作封装
void P(int sem_id)
{
    struct sembuf xx;
    xx.sem_num = 0;             // 设置需要操作的信号量在信号量集中的索引编号
    xx.sem_op = -1;             // P
    xx.sem_flg = 0;
    semop(sem_id, &xx, 1);      // 信号量执行 P 操作
}

void V(int sem_id)
{
    struct sembuf xx;
    xx.sem_num = 0;
    xx.sem_op = 1;
    xx.sem_flg = 0;
    semop(sem_id, &xx, 1);
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
    int ans = semctl(id, 0, GETVAL);
    if (ans == -1) {
        printf("error to get value from mutex_sem.\n");
        exit(0);
    }
    else {
        printf("get the sem value %d\n", ans);
    }
}

void get_msgfifo_to_show(int msgid, struct data_msg dmsgr, int pos)
{
    // 取出缓冲区所有数据
    for (int i = 1; i <= 6; i++) {
        msgrcv(msgid, &dmsgr, sizeof(dmsgr), i, 0);
        if (dmsgr.text[0] == '\0') {
            printf("[    ] ");
        }
        else {
            printf("[%s] ", dmsgr.text);
        }
        msgsnd(msgid, &dmsgr, sizeof(dmsgr), 0);   
    }
    printf("\n");
    printf("            ");
    for (int i = 1; i < pos; i++) {
        printf("       ");
    }
    printf("......\n");
}

int main(int argc, char* argv[])
{
    // 初始化消息队列
    int msgid = msgget(103, 0666 | IPC_CREAT);

    int length;                 // 缓冲区长度 6
    char share[MAX_LENGTH][10];
    int flag;                   // 生产者消费者标识
    struct pos_msg pmsgs, pmsgr;
    struct data_msg dmsgs, dmsgr;
    time_t now;
    int mutex_semid, empty_semid, full_semid;

    // 初始化 mutex 信号量
    mutex_semid = semget((key_t)1234, 1, 0666|IPC_CREAT);
    set_semvalue(mutex_semid, 1);

    // 初始化 empty 信号量
    empty_semid = semget((key_t)1235, 1, 0666|IPC_CREAT);
    set_semvalue(empty_semid, 6);

    // 初始化 full 信号量
    full_semid  = semget((key_t)1236, 1, 0666|IPC_CREAT);
    set_semvalue(full_semid, 0);

    // 产生生产者和消费者并分配编号
    for(int i = 0; i < 5; i++) {
        int pid = fork();
        if (pid == -1) {
            // fork 失败，退出程序
            printf("fork fail.\n");
            exit(0);
        }

        if (pid > 0) {
            if (i == 4) {
                // 父进程最后一次循环，进行消息队列的初始化操作，推入编号为 1 ~ 6 总计 6 个消息作为缓冲区
                for (int j = 0; j < 6; j++) {
                    memset(dmsgs.text, '\0', 10);
                    dmsgs.type = j + 1;
                    msgsnd(msgid, &dmsgs, sizeof(dmsgs), 0);
                }

                // 推入两个指针
                pmsgs.type = 7;
                pmsgs.pos = 1;
                msgsnd(msgid, &pmsgs, sizeof(pmsgs), 0);

                pmsgs.type = 8;
                pmsgs.pos = 1;
                msgsnd(msgid, &pmsgs, sizeof(pmsgs), 0);

                flag = -1;
            }
        }
        else {
            // 子进程出循环，准备执行
            flag = i;
            break;
        }
    }

    // 开始生产者消费者模型,进入临界区
    // 7空余，8满
    if (flag < 2 && flag != -1) {
        int msgtype = 7;
        int pos;
        char pmsg[10];
        // 生产者, 持续 12 次
        for (int i = 0; i < 12; i++) {
            // 随机休眠 <= 7 s
            srand(i);
            int hour = rand() % 7;
            sleep(hour);

            // 申请信号量
            P(empty_semid);
            P(mutex_semid);

            // 接收 7 号消息，指示缓冲区中的下一个空余的位置
            int res = msgrcv(msgid, &pmsgr, sizeof(pmsgr), msgtype, IPC_NOWAIT);
            if (res == -1) {
                // 出错，消息队列中不存在数据，可能属于第一次发送的情况
                printf("the msgfifo do not have the %d msg!\n", msgtype);
                pos = 1;
            }
            else {
                // 获取消息队列中的数据
                pos = pmsgr.pos;
            }

            msgrcv(msgid, &dmsgr, sizeof(dmsgr), pos, 0);
            sprintf(pmsg, "p%d: %d\n", flag, pos);
            // printf("%s\n", pmsg);
            strcpy(dmsgs.text, "Data");
            dmsgs.type = pos;
            msgsnd(msgid, &dmsgs, sizeof(dmsgs), 0);
            
            pmsgs.pos = (pos + 1) % 7;
            if (pmsgs.pos == 0) pmsgs.pos = 1;

            pmsgs.type = 7;
            msgsnd(msgid, &pmsgs, sizeof(pmsgs), 0);

            printf("[Producer]: ");
            get_msgfifo_to_show(msgid, dmsgr, pos);

            // 释放信号量
            V(mutex_semid);
            V(full_semid);
        }
    }
    else if (flag > 1) {
        // 消费者, 持续 8 次
        int msgtype = 8;
        int pos;
        char pmsg[10];
        for (int i = 0; i < 8; i++) {
            // 随机休眠 <= 7 s
            srand(i);
            int hour = rand() % 7;
            sleep(hour);

            P(full_semid);
            P(mutex_semid);

            int res = msgrcv(msgid, &pmsgr, sizeof(pmsgr), msgtype, IPC_NOWAIT);
            if (res == -1) {
                // 出错，消息队列中不存在数据，可能属于第一次发送的情况
                printf("the msgfifo do not have the %d msg!\n", msgtype);
                pos = 1;
            }
            else {
                // 获取消息队列中的数据
                pos = pmsgr.pos;
            }

            msgrcv(msgid, &dmsgr, sizeof(dmsgr), pos, 0);
            sprintf(pmsg, "\t\tc%d: %d\n", flag, pos);
            // printf("%s\n", pmsg);
            dmsgs.text[0] = '\0';
            dmsgs.type = pos;
            msgsnd(msgid, &dmsgs, sizeof(dmsgs), 0);
            
            pmsgs.pos = (pos + 1) % 7;
            if (pmsgs.pos == 0) pmsgs.pos = 1;

            pmsgs.type = 8;
            msgsnd(msgid, &pmsgs, sizeof(pmsgs), 0);

            printf("[Consumer]: ");
            get_msgfifo_to_show(msgid, dmsgr, pos);

            V(mutex_semid);
            V(empty_semid);
        }
    }
    else {
        // father process is here
    }
    // printf("process #%d finish the work.\n", flag);
    return 0;
}
