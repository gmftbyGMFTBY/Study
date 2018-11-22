#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

int n;
int a[N]; 
int b[N];

int judge()
{
    for(int i = 0;i < n;i++)
    {
        int t = 0;
        for(int j = 0;j < n;j++)
        {
            if(b[j] == a[i]) t ++;
        }
        if(t != b[i]) return 0;
    }

    int sum = 0;
    for(int i = 0;i < n;i ++) sum += b[i];
    if(sum != n) return 0;

    sum = 0;
    for(int i = 0;i < n;i++) sum += a[i] * b[i];
    if(sum != n) return 0;
    return 1;
}

int dfs(int s , int now)
{
    if(now == n && s == n)
    {
        if(judge()) return 1;
        else return 0;
    }
    else
    {
        if(now == n) return 0;
        for(int i = 0 ; i <= n - s ; i++)
        {
            b[now] = i;
            if(dfs(s + i , now + 1) == 1) return 1;
            b[now] = 0;    //其实这一步没有必要
        }
    }
    return 0;
}

int main()
{
    scanf("%d" , &n);
    for( int i = 0; i < n;i++ )
    {
        scanf("%d" , &a[i]);
    }

    //如果存在多种情况，输出第一个数字最小的那个,不存在输出n个0
    if(dfs(0 , 0) == 0) 
    {
        printf("do not exist\n");
    }
    else
    {
        for(int i = 0;i < n - 1;i++) printf("%d " , b[i]);
        printf("%d\n" , b[n - 1]);
    }
    return 0;
}
