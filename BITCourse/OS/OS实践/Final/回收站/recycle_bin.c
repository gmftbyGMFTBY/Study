#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/*
   recycle bin 是使用 C 语言编写的一个对 rm, rmdir 等删除命令的一个封装
   本质目的在于，给予用户一个后悔的机会去回复删除的文件，文件在执行了对 
   rm, rmdir 等删除操作之后，并不是完全的从磁盘上删除数据，本质的是将数
   据从当前的工作目录移除到制定的临时文件夹下，并允许用户在之后的适当时
   机恢复到原来的工作目录中
 */

int check_log_file(char* dirname, char* filename, char* file_msg[])
{
    // 首先判断文件手否存在，文件不存在或者打开失败创建文件

    if (access(dirname, F_OK) == -1) {
        // 创建目录
        mkdir(dirname, 666);
        creat(filename, 666);
        return -1;
    }
    else if (access(filename, R_OK) == -1) {
        creat(filename, 666);
        return -1;
    }
    else return 0;
}

void move_file(char* filename, char* recycle)
{

}

int move(int argc, char* argv[])
{
    char* file_msg[3];  // 0 - 文件名, 1 - 原工作目录, 2 - 删除时间戳
    // argv 存放需要删除的文件的路径，可以存在多个删除目标，删除目标的数目需要 argv 来指定
    for (int i = 1; i < argc; i++) {
        // 检测和创建文件
        int res = check_log_file("/tmp/recycle_bin/", "/tmp/recycle_bin/recycle_log", file_msg);
        if (res != 0) printf("the file or the dir may occur error, already fix it!\n");

        // 移动文件
        move_file(argv[i], "/tmp/recycle_bin/");

        // 记录添加
        // append_log_file("/tmp/recycle_bin/recycle_log");
    }
}

void show_manal()
{
    // this function try to show the manal for the user.
    printf("-r: 回复回收站内的文件的内容到原本的工作目录下\n");
    printf("    * 允许指定回复的文件\n");
    printf("    * 不指定默认回收站的内的数据全部恢复\n");
    printf("-c: 清空回收站\n");
    printf("    * 制定删除的文件\n");
    printf("    * 不指定文件默认回收站的文件全部删除\n");
    printf("-h: 帮助信息\n\n");

    printf("回收站目录: /tmp/recycle_bin\n");
}

int main(int argc, char* argv[])
{
    /* 检测命令行参数
       1. -r: 恢复回收站内的内容到指定的目录下
            * 指定恢复的文件
            * 不指定默认全部恢复
            如果恢复失败，尝试将文件回复在 ~ 下并报出异常
       2. -c: 清空回收站
            * 指定删除的文件
            * 不指定默认全部删除
       3. -h: 帮助模式
     */

    int flag = 0;       // 记录工作状态

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            // 恢复模式, 1
            flag = 1;
            break;
        }
        else if (strcmp(argv[i], "-c") == 0) {
            // 清除模式, 2
            flag = 2;
            break;
        }
        else if (strcmp(argv[i], "-h") == 0) {
            // 帮助模式
            flag = 3;
            break;
        }
        else if (argv[i][0] == '-') {
            // 其他的非法的工作模式，需要给予用户使用说明
            flag = -1;
            break;
        }
    }

    if (flag == -1 || flag == 3 || argc == 1) {
        show_manal();
        exit(0);
    }
    else if (flag == 1) {
        // restore(argc, argv);
    }
    else if (flag == 2) {
        // delete(argc, argv);
    }
    else if (flag == 0) {
        move(argc, argv);
    }
    else {
        printf("something wrong with the executer!\n");
    }
    return 0;
}
