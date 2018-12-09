#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char c;
    while((c=getchar()) != EOF)
    {
        // 标准输入的大小写转换输出
        if(isupper(c))
        {
            c = tolower(c);
        }
        putchar(c);
    }
    return 0;    
}