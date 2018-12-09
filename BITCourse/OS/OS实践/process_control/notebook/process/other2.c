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

#define MSGKEY 200

struct my_msg
{
   long type;
   char text[200];
};

int main()
{
    int msgid;
    // 外部进程只责接收
    struct my_msg msgr;
    time_t now;
    // 创建过了 200 号消息队列，这里打开消息队列
    msgid = msgget(MSGKEY, 0666);

    sleep(1);
    time(&now);
    memset(msgr.text, '\0', sizeof(msgr.text));
    msgrcv(msgid, &msgr, sizeof(msgr.text), 2, 0);      // 接收父进程发送的 2 号消息

    printf("%d: process #3 receive %s\n", now, msgr.text);
    sleep(3);
    time(&now);
    memset(msgr.text, '\0', sizeof(msgr.text));
    msgrcv(msgid, &msgr, sizeof(msgr.text), 2, 0);
    printf("%d: process #3 receive %s\n", now, msgr.text);
    return 0;
}