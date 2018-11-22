#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define N 10000001

/*
   Union-find
      * count the Connected component
      * count the size of the set, which used the extension array to solve it
      * Used by the MST (Minimum-cost spanning tree)
 */

using namespace std;

int Tree[N];    // Tree[i] save the father node of the i node, -1 means is the root node 
int sum[N];     // sum[i] means the size of the set which root is i, only Tree[i] = -1 is useful

// add the path decay into the function
int findroot (int x) {
    if (Tree[x] == -1) return x;
    else {
        int tmp = findroot (Tree[x]);
        Tree[x] = tmp;    // make all the node point to the root
        return tmp;
    }
}

int main () {
    int n, m;
    while (scanf("%d", &n) != EOF && n != 0) {
        scanf("%d", &m);
        // init
        for (int i = 1; i <= n; i ++) Tree[i] = -1;

        while (m --) {
            int a, b;
            scanf("%d%d", &a, &b);
            a = findroot(a);
            b = findroot(b);
            if (a != b) Tree[a] = b;
        }

        // count the number of the set tree
        int ans = 0;
        for (int i = 1; i <= n; i ++) {
            if (Tree[i] == -1) ans ++;
        }

        // only need ans - 1
        printf("%d\n", ans - 1);
    }
    return 0;
}
