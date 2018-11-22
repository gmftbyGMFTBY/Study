#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct nn
{
    int x,y,z;
}path;

char map[35][35][35];
int vis[35][35][35];
int k,n,m,sx,sy,sz,ex,ey,ez;
int to[6][3] = {{0,0,1},{0,0,-1},{0,1,0},{0,-1,0},{1,0,0},{-1,0,0}};
int eye_alien = 0;    // the see sight of the alien
int step_sum = 0;   //the sum step of the alien
path sumpath[100];   //the path of the alien

struct node
{
    int x,y,z,step;
    int step_alien;
};

int check(int x,int y,int z , int s)
{
    if(x<0 || y<0 || z<0 || x>=k || y>=n || z>=m)
        return 1;
    if(map[x][y][z] == '#')
        return 1;
    if(vis[x][y][z])
        return 1;
    path step = sumpath[s];    // make sure the point of the block
    if(eye_alien == 0)    // special judge the case of the eye_alien = 0
        if(step.x == x && step.y == y && step.z == z) return 1;
    int dx = x;
    int dy = y;
    int dz = z;
    for(int i = 0;i < 6;i++)
    {
        for(int j = 1;j <= eye_alien;j++)
        {
            dx += to[i][0];
            dy += to[i][1];
            dz += to[i][2];
            if(dx == x && dy ==y && dz == z) return 1;  
        }
    }
    return 0;
}

int bfs()
{
    int i;
    node a,next;
    queue<node> Q;
    a.x = sx,a.y = sy,a.z = sz;
    a.step = 0;
    a.step_alien = 0;    // init the first step of the alien
    vis[sx][sy][sz] = 1;
    Q.push(a);
    while(!Q.empty())
    {
        a = Q.front();
        Q.pop();
        if(a.x == ex && a.y == ey && a.z == ez)
            return a.step;
        for(i = 0; i<6; i++)
        {
            next = a;
            next.x = a.x+to[i][0];
            next.y = a.y+to[i][1];
            next.z = a.z+to[i][2];
            next.step_alien = (next.step_alien + 1) % step_sum ;
            if(check(next.x,next.y,next.z , next.step_alien))
                continue;
            vis[next.x][next.y][next.z] = 1;
            next.step = a.step+1;
            Q.push(next);
        }
    }
    return 0;
}

int main()
{
    int i,j,r;
    while(scanf("%d%d%d",&k,&n,&m),n+m+k)
    {
        for(i = 0; i<k; i++)
        {
            for(j = 0; j<n; j++)
            {
                scanf("%s",map[i][j]);
                for(r = 0; r<m; r++)
                {
                    if(map[i][j][r] == 'S')
                    {
                        sx = i,sy = j,sz = r;
                    }
                    else if(map[i][j][r] == 'E')
                    {
                        ex = i,ey = j,ez = r;
                    }
                }
            }
        }
        scanf("%d%d" , &step_sum,&eye_alien);    // get the step of the path
        for(int i = 0; i < step_sum ;i++) 
        {
            scanf("%d%d%d", & sumpath[i].x , &sumpath[i].y , &sumpath[i].z);
        }
        for(int i = 1; i <= step_sum - 1 ;i++)
        {
            sumpath[step_sum - 1 + i].x = sumpath[step_sum - 1 - i].x;
            sumpath[step_sum - 1 + i].y = sumpath[step_sum - 1 - i].y; 
            sumpath[step_sum - 1 + i].z = sumpath[step_sum - 1 - i].z;
        }
        step_sum = step_sum * 2 - 2;
        if(step_sum == 0) step_sum = 1;
//        printf("%d\n" , step_sum);
//        for(int i = 0;i < step_sum;i++) printf("%d %d %d \n" , sumpath[i].x , sumpath[i].y , sumpath[i].z);
        memset(vis,0,sizeof(vis));
        int ans;
        ans = bfs();
        if(ans)
            printf("Escaped in %d minute(s).\n",ans);
        else
            printf("-1\n");
    }
    return 0;
}
