#include <stdio.h>
#include <iostream>
#include <stdlib.h>

/*
   0-1 pack problem

   dp[i][j]: first i elements in the j volume pack's max value

   dp[i][j] = max{dp[i - 1][j - w] + v, dp[i - 1][j]}
 */

using namespace std;

int max (int a, int b) {
    return a > b ? a : b;
}

struct thing {
    int w;
    int v;
}list[101];

// we can use the rolling array to decay the mat of dp
// into dp[1001]
int dp[101][1001];

int main () {
    int s, n;
    while (scanf("%d%d", &s, &n) != EOF) {
        for (int i = 1; i <= n; i ++) {
            scanf("%d%d", &list[i].w, &list[i].v);
        }

        for (int i = 0; i <= s; i ++) {
            dp[0][i] = 0;
        }

        for (int i = 1; i <= n; i ++) {
            for (int j = s; j >= list[i].w; j --) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - list[i].w] + list[i].v);
            }

            // this for statement will not need any more, if we use rolling 
            // array
            for (int j = list[i].w - 1; j >= 0; j--) {
                dp[i][j] = dp[i - 1][j];
            }
        }

        printf("%d\n", dp[n][s]);
    }
    return 0;
}
