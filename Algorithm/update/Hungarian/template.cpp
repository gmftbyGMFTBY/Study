#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstring>
#define N 2005

using namespace std;

int visit[N];      //visit数组记录我们的当前的该店的访问情况
int map[N][N];     //map记录我们的图的邻接关系
int link[N];    //Link记录我们的连接关系
int n,m;    //n,m代表不同的点集的点的数目
int sum = 0;

int match(int x)
{
    for(int i = 1; i <= n; i++)
    {
        if(visit[i] == 0 && map[x][i] == 1)
        {
            visit[i] = 1;
            if(link[i] == 0 || match(link[i]) == 1)
            {
                link[i] = x;
                link[x] = i;
                cout << i << ' ' << x << endl;
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    cin >> n >> m ;
    memset(map,0,sizeof(map));
    memset(link,0,sizeof(link));
    memset(visit,0,sizeof(0));

    while(m--)
    {
        int x,y;
        cin >> x >> y;
        map[x][y] = map[y][x] = 1;
    }

    for(int i = 1; i <= n ; i++)
    {
        memset(visit,0,sizeof(visit));
        if(match(i)) sum ++;
    }

    cout << "The max matches is " << sum << endl;
    memset(visit,0,sizeof(visit));
    for(int i = 1;i <= n;i++)
    {
        if(!visit[i] && link[i] != 0)
        {
            cout << i << " - " << link[i] << endl;
            visit[i] = visit[link[i]] = 1;
        }
    }
    cout << "Upper is the matches!" << endl;
    return 0;
}
