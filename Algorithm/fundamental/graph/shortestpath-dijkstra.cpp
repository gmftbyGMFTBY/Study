#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#define INF 0x3f3f3f3f
/*
   HDU 2544
 */

using namespace std;

struct Edge {
    int node;
    int cost;
};

vector<Edge> edge[101];
bool mark[101];
int dis[101];

int dijstra (int n) {
    // init 
    for (int i = 1; i <= n; i ++) {
        dis[i] = INF;
        mark[i] = false;
    }

    for (int i = 0; i < edge[1].size(); i ++) {
        dis[edge[1][i].node] = edge[1][i].cost;
    }

    mark[1] = true;
    int p;
    
    // dijstra
    for (int i = 1; i <= n; i ++) {
        int minn = INF;
        // find the min node to use
        for (int j = 1; j <= n; j ++) {
            if (mark[j] == false && dis[j] < minn) {
                minn = dis[j];
                p = j;
            }
        }

        // optimize the node
        mark[p] = true;
        for (int j = 0; j < edge[p].size(); j ++) {
            int to = edge[p][j].node;
            int w  = edge[p][j].cost;
            if (dis[to] > dis[p] + w) {
                dis[to] = dis[p] + w;
            }
        }
    }

    return dis[n];
}

int main () {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 0 && m == 0) break;

        // init the map
        for (int i = 0; i <= n; i ++) edge[i].clear();

        // input
        for (int i = 0; i < m; i ++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            struct Edge tmp;
            tmp.cost = c;
            tmp.node = b;
            edge[a].push_back(tmp);
            tmp.node = a;
            edge[b].push_back(tmp);
        }

        printf("%d\n", dijstra(n));
    }
    return 0;
}
