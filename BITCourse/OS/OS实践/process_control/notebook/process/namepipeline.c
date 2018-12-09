#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    char buf[50];
    int fd;
    while(1) {
        fd = open("/tmp/myfifo", O_RDONLY);    // 只读
        memset(buf, '\0', sizeof(buf));
        read(fd, buf, 50);
        printf("receive: %s\n", buf);
    }
    close(fd);
}
