#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>  

/*
显示文件权限，修改文件权限使用函数
chmod(const char* path, int mode);
*/

int main(int argc, char* argv[])
{
    struct stat buf;
    int ret = stat("a", &buf);

    argv[1] = "a";
    char* show = "0000";

    switch(S_IRWXU & buf.st_mode)
    {
        case S_IRUSR|S_IWUSR|S_IXUSR:printf("owner of %s has rwx permission \n",argv[1]);show[1] = '1';break;  
        case S_IWUSR:printf("owner of %s has w permission\n",argv[1]);break;  
        case S_IXUSR:printf("owner of %s has x permission\n",argv[1]);break; 
        case S_IRUSR:printf("owner of %s has r permission \n",argv[1]);break;  
        case S_IWUSR|S_IXUSR:printf("owner of %s has wx permission \n",argv[1]);break;  
        case S_IRUSR|S_IXUSR:printf("owner of %s has rx permission \n",argv[1]);break;  
        case S_IRUSR|S_IWUSR:printf("owner of %s has rw permission \n",argv[1]);break;  
        default:printf("owner of %s has no permission\n", argv[1]);  
    }

    switch(S_IRWXG & buf.st_mode)
    {
        case S_IRGRP|S_IWGRP|S_IXGRP:printf("group of %s has rwx permission \n",argv[1]);break;  
        case S_IWGRP:printf("group of %s has w permission\n",argv[1]);break;  
        case S_IXGRP:printf("group of %s has x permission\n",argv[1]);break; 
        case S_IRGRP:printf("group of %s has r permission \n",argv[1]);break;  
        case S_IWGRP|S_IXGRP:printf("group of %s has wx permission \n",argv[1]);break;  
        case S_IRGRP|S_IXGRP:printf("group of %s has rx permission \n",argv[1]);break;  
        case S_IRGRP|S_IWGRP:printf("group of %s has rw permission \n",argv[1]);break;  
        default:printf("group of %s has no permission\n", argv[1]);  
    }

    switch(S_IRWXO & buf.st_mode)
    {
        case S_IROTH|S_IWOTH|S_IXOTH:printf("owner of %s has rwx permission \n",argv[1]);break;  
        case S_IWOTH:printf("owner of %s has w permission\n",argv[1]);break;  
        case S_IXOTH:printf("owner of %s has x permission\n",argv[1]);break; 
        case S_IROTH:printf("owner of %s has r permission \n",argv[1]);break;  
        case S_IWOTH|S_IXOTH:printf("owner of %s has wx permission \n",argv[1]);break;  
        case S_IROTH|S_IXOTH:printf("owner of %s has rx permission \n",argv[1]);break;  
        case S_IROTH|S_IWOTH:printf("owner of %s has rw permission \n",argv[1]);break;  
        default:printf("owner of %s has no permission\n", argv[1]);  
    }


    return 0;
}
