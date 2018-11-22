#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>

/*
   DAG can judge that whether the graph has the cycle
   <queue>
        Q.push(x)     push the x into thr queue
        x = Q.front() read the queue head to the x
        Q.pop()       pop the queue head 
        Q.empty()     judge whether the queue is empty

    queue save the node which input degree is zero 
 */

using namespace std;

vector<int> edge[501];
queue<int> Q;

int main () {
    int indegree[501];
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 0 && m == 0) break;

        // init
        for (int i = 0; i < n; i ++) {
            indegree[i] = 0;
            edge[i].clear();
        }

        while (m --) {
            int a, b;
            scanf("%d%d", &a, &b);
            indegree[b] ++;
            edge[a].push_back(b);
        }

        while (Q.empty() == false) Q.pop();

        for (int i = 0; i < n; i ++) {
            if (indegree[i] == 0) Q.push(i);
        }

        int cnt = 0;
        while (Q.empty() == false) {
            int now = Q.front();
            Q.pop();
            cnt ++;    // node which access
            for (int i = 0; i < edge[now].size(); i ++) {
                indegree[edge[now][i]] -- ;

                if (indegree[edge[now][i]] == 0) Q.push(edge[now][i]);
            }
        }

        if (cnt == n) puts("YES");
        else puts("NO");
    }
    return 0;
}
