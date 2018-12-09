#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char str[50] = "pipe message";
    int filedes;
    // 从字符串参数中获取文件描述符
    sscanf(argv[1], "%d", &filedes);
    write(filedes, str, strlen(str));
    printf("other send: %s\n", str);
    return 0;
}