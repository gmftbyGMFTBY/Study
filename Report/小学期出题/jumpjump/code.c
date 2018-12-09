#include <stdio.h>
#include <stdlib.h>
#define N 100000

int begin = 0;
int end = 0;
int array[N];
int n;

int max_mine(int a , int b)
{
    if(a >= b) return a;
    else return b;
}

int main()
{
    int count = 0;
    int max_length = 0;
    scanf("%d\n" , &n);
    for(int i = 0;i < n;i++) 
    {
        scanf("%d" , &array[i]);
    }
    while(end < n - 1)
    {
        count ++;
        for(int p = begin;p <= end;p++)
        {
            max_length = max_mine(max_length , p + array[p]);
        }
        begin = end + 1;
        end = max_length;
    }
    printf("%d\n" , count);
    return 0;
}
