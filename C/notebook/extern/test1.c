#include <stdio.h>

int func();

int main(int argc, char* argv[])
{
    func();
    extern int num;
    printf("%d\n", num);
    return 0;
}

int num = 3;
int func()
{
    printf("%d\n", num);
}
