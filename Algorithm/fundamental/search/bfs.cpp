#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

/*
   BFS can find the shortest result of the problem 
   and the first node will not be expendded twice.
 */

using namespace std;

struct node {
    int x, y, z;
    int t;
};

// mark save the state of the maze
bool mark[50][50][50];
// save the state of the maze, 1 means the wall which can not access
int maze[50][50][50];

queue<node> Q;

// move state
int movement[6][3] = {
    1, 0, 0,
    -1, 0, 0,
    0, 1, 0,
    0, -1, 0,
    0, 0, 1,
    0, 0, -1
};

int bfs (int a, int b, int c) {
    while (Q.empty() == false) {
        struct node now = Q.front();
        Q.pop();
        for (int i = 0; i < 6; i ++) {
            int nx = now.x + movement[i][0];
            int ny = now.y + movement[i][1];
            int nz = now.z + movement[i][2];

            if (nx < 0 || nx >= a || ny < 0 || ny >= b || nz < 0 || nz >= c)
                continue;

            if (maze[nx][ny][nz] == 1) continue;
            if (mark[nx][ny][nz] == true) continue;

            struct node tmp;
            tmp.x = nx;
            tmp.y = ny;
            tmp.z = nz;
            tmp.t = now.t + 1;

            Q.push(tmp);
            mark[nx][ny][nz] = true;
            if (nx == a - 1 && ny == b - 1 && nz == c - 1) return tmp.t;
        }
    }

    return -1;
} 

int main () {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b, c, t;
        scanf("%d%d%d%d", &a, &b, &c, &t);

        // init the maze and the mark
        for (int i = 0; i < a; i ++) {
            for (int j = 0; j < a; j ++) {
                for (int k = 0; k < c; k ++) {
                    scanf("%d", &maze[i][j][k]);
                    mark[i][j][k] = false;
                }
            }
        }

        while (Q.empty() == false) Q.pop();
        mark[0][0][0] = true;

        struct node tmp;
        tmp.t = tmp.y = tmp.x = tmp.z = 0;
        Q.push(tmp);

        int result = bfs (a, b, c);
        if (result <= t) printf("%d\n", result);
        else printf("-1\n");
    }
    return 0;
}
