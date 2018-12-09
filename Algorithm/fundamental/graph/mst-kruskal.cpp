#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#define N 101

/*
    MST:
        Kruskal:
            1. init all the node to the lonly set
            2. sort the edge and add the edge which two nodes are not in the same set
               and add it into the MST
            Noted: Used Union-fing
 */

using namespace std;

int Tree[N];
int findroot (int x) {
    if (Tree[x] == -1) return x;
    else {
        int tmp = findroot(Tree[x]);
        Tree[x] = tmp;
        return tmp;
    }
}

struct Edge {
    int a, b;
    int cost;
}edge[6000];

int cmp (const void* a, const void* b) {
    struct Edge arg1 = *(const struct Edge*)a;
    struct Edge arg2 = *(const struct Edge*)b;

    return arg1.cost - arg2.cost;
}

int main () {
    int n;
    while (scanf("%d", &n) != EOF && n != 0) {
        // init
        for (int i = 1; i <= n * (n - 1) / 2; i ++) {
            scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].cost);
        }

        qsort(edge, n * (n - 1) / 2, sizeof(edge[0]), cmp);

        // init the Union-find
        for (int i = 1; i <= n; i ++) {
            Tree[i] = -1;
        }

        int ans = 0;
        for (int i = 1; i <= n * (n -1) / 2; i ++) {
            int a = findroot(edge[i].a);
            int b = findroot(edge[i].b);
            if (a != b) {
                ans += edge[i].cost;
                Tree[a] = b;
            }
        }

        printf("%d\n", ans);
    } 
    return 0;
}
