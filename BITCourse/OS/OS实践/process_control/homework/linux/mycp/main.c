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
   实现 mycp 对目录的拷贝,链接文件的追踪(No)
 */

char* check_file_PL(struct stat buf)
{
    int mode = buf.st_mode;
    char* show = (char *)malloc(sizeof(char) * 4);
    show[0] = show[1] = show[2] = show[3] = '0';

    switch(S_IRWXU & mode)
    {
        case S_IRUSR|S_IWUSR|S_IXUSR:show[1] = '7';break; 
        case S_IWUSR:show[1] = '2';break;  
        case S_IXUSR:show[1] = '1';break; 
        case S_IRUSR:show[1] = '4';break;  
        case S_IWUSR|S_IXUSR:show[1] = '3';break;  
        case S_IRUSR|S_IXUSR:show[1] = '5';break;  
        case S_IRUSR|S_IWUSR:show[1] = '6';break;  
        default:show[1] = '0';
    }

    switch(S_IRWXG & mode)
    {
        case S_IRGRP|S_IWGRP|S_IXGRP:show[2] = '7';break;  
        case S_IWGRP:show[2] = '2';break;  
        case S_IXGRP:show[2] = '1';break; 
        case S_IRGRP:show[2] = '4';break;  
        case S_IWGRP|S_IXGRP:show[2] = '3';break;  
        case S_IRGRP|S_IXGRP:show[2] = '5';break;  
        case S_IRGRP|S_IWGRP:show[2] = '6';break;  
        default:show[2] = '0';break;  
    }

    switch(S_IRWXO & mode)
    {
        case S_IROTH|S_IWOTH|S_IXOTH:show[3] = '7';break;  
        case S_IWOTH:show[3] = '2';break;  
        case S_IXOTH:show[3] = '1';break; 
        case S_IROTH:show[3] = '4';break;  
        case S_IWOTH|S_IXOTH:show[3] = '3';break;  
        case S_IROTH|S_IXOTH:show[3] = '5';break;  
        case S_IROTH|S_IWOTH:show[3] = '6';break;  
        default:show[3] = '0';break; 
    }
    return show;
}

void change_file_PL(char* path, char* mode)
{
    // 因为是 chmod, 不需要考虑掩码的问题
    // 8 进制转换
    int n_mode = atoi(mode);
    int mode_u = n_mode / 100;                    //文件所有者权限  
    int mode_g = (n_mode - (mode_u*100))/10;          //所属组权限  
    int mode_o = n_mode - (mode_u*100) - (mode_g*10);      //其他人权限  
    int modep = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;    //转换成八进制 
    chmod(path, modep);
}

int check_file(char* path)
{
    // 普通文件 - 1
    // 目录文件 - 0 
    // 其他文件 - -1
    struct stat buf;
    int res = stat(path, &buf);
    if (S_ISDIR(buf.st_mode)) {
        // 是目录
        return 0;
    }
    else if(S_ISREG(buf.st_mode)) {
        // 是普通的文件
        return 1;
    }
    else {
        // 其他的文件
        return -1;
    }
}

void file2file(char* spath, char* dpath)
{
    // 文件复制操作，spath -> dpath
    int fdread;
    int fdwrite;
    char t[100];    // 读写缓冲区
    fdread = open(spath, O_RDONLY);
    fdwrite = open(dpath, O_WRONLY|O_CREAT);

    // 查找文件的权限
    struct stat buf;
    int res = stat(spath, &buf);
    char* pl = check_file_PL(buf);

    int cur;
    while ((cur = read(fdread, &t, 100)) != 0) {
        write(fdwrite, &t, cur);
    }

    close(fdread);
    close(fdwrite);
    // 修改文件的权限保持一致
    change_file_PL(dpath, pl);
}

char* getfilename(char* path)
{
    int length = strlen(path);
    char* pp = (char*)malloc(sizeof(char) * strlen(path));
    strcpy(pp, path);
    int flag = 0;
    for (int i = 0; i < length; i++) {
        if (pp[i] == '/') flag = i;
    }
    if (flag != 0) flag += 1;
    char* res = (char *)malloc(sizeof(char) * length);
    for (int i = 0; i < (length - flag); i++) {
        res[i] = pp[flag + i];
    }
    return res;
}

int exist_file(char* path)
{
    // 检验文件是否存在, 0不存在
    int res = access(path, R_OK);
    if (res != -1) return 1;
    else return 0;
}

char* get_new_filename(char* filename, char* path)
{
    int length = strlen(path);
    if (path[length - 1] != '/') {
        path[length] = '/';
        path[length + 1] = '\0';
    }
    char* res = (char*)malloc(sizeof(char) * strlen(path));
    strcpy(res, path);
    return strcat(res, filename);
}

void file2dir(char* spath, char* dpath)
{
    // 创建同名文件
    int fdread;
    int fdwrite;
    char t[100];   // 读写缓冲区
    fdread = open(spath, O_RDONLY);
    fdwrite = open(dpath, O_RDWR);
    // 获取文件名
    char* filename = getfilename(spath);
    char* newfilename = get_new_filename(filename, dpath);

    file2file(spath ,newfilename);
}

void dir2dir(char* spath, char* dpath)
{
    // 创建目录, cp -r
    // dpath 不存在，创建一个性的目录并将文件全部复制
    // dpath 存在，将目录全部复制到 dpath 下
    // 子目录的递归

    int flag = 0;
    char* filename;
    char* n_dpath;
    char* m_dpath;

    m_dpath = (char*) malloc(sizeof(char) * strlen(dpath));
    strcpy(m_dpath, dpath);

    if (exist_file(dpath) == 0) {
        // 目标目录不存在，完全复制目录
        // 创建目录并复制权限
        struct stat buf;
        stat(spath, &buf);
        char* pl = check_file_PL(buf);
        mkdir(m_dpath, R_OK);
        change_file_PL(m_dpath, pl);
        flag = 0;
    }
    else {
        // 在目标目录下创建目录
        struct stat buf;
        stat(spath, &buf);
        char* pl = check_file_PL(buf);

        // 新的目录的路径生成
        filename = getfilename(spath);
        n_dpath = get_new_filename(filename, dpath);
        mkdir(n_dpath, R_OK);
        change_file_PL(n_dpath, pl);
        flag = 1;
    }

    // 文件复制
    DIR * dirptr = NULL;
    struct dirent* entry = NULL;

    dirptr = opendir(spath);

    while (entry = readdir(dirptr)) {
        if (entry->d_name[0] == '.' && entry->d_name[1] == '.' && strlen(entry->d_name) == 2) continue;
        if (entry->d_name[0] == '.' && strlen(entry->d_name) == 1) continue;
        struct stat buf;
        char* fn = get_new_filename(entry->d_name, spath);
        stat(fn, &buf);
        if (flag == 1) {
            if (S_ISDIR(buf.st_mode)) {
                // 存在子目录
                dir2dir(fn, n_dpath);
            }
            else {
                // 不是子目录
                file2dir(fn, n_dpath);
            }
        }
        else {
            // 目录不存在
            if (S_ISDIR(buf.st_mode)) {
                // 存在子目录
                dir2dir(fn, m_dpath);
            }
            else {
                // 不是子目录
                file2dir(fn, m_dpath);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    // 命令行参数错误
    if (argc != 3)
    {
        printf("WRONG!");
        exit(0);
    }
    
    // 源确认
    int sou_file = check_file(argv[1]);
    int des_file = check_file(argv[2]);

    if (sou_file == -1) {
        printf("WRONG!");
        exit(0);
    } else if (sou_file == 0 && des_file == 0) {
        // 目录复制到目录下
        dir2dir(argv[1], argv[2]);
    } else if (sou_file == 0 && des_file == 1) {
        // 目录复制到文件下, ok
        printf("WRONG!");
        exit(0);
    } else if (sou_file == 1 && des_file == 0) {
        // 普通文件复制到目录下, ok
        file2dir(argv[1], argv[2]);
    } else if (sou_file == 1 && des_file == 1) {
        // 文件复制, ok
        file2file(argv[1], argv[2]);
    }
    return 0;
}
