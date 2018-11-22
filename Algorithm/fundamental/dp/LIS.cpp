#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/*
   LIS
   get the subsequence {ai1, ai2, ..., ain} from {a1, a2, ..., an}
       * i1 < i2 < ... < in
       * ix > iy and aix > aiy
   the subsequence is the LIS

   F[i]: the sub LIS's length which end with ai, F[1] = 1 
   F[x] = max{1, F[i] + 1 | ai < ax && i < x} need to search all the i
    
   O(n * n)
 */

using namespace std;

/*
    Question:
        F[1] = 1
        F[i] = max{1, F[j] + 1 | j < i && aj > ai}
 */

int max (int a, int b) {
    return a > b ? a : b;
}

int list[26];
int dp[26];

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i ++) {
            scanf("%d", &list[i]);
        }

        for (int i = 1; i <= n; i ++) {
            int tmax = 1;

            for (int j = 1; j < i; j ++ ) {
                if (list[j] >= list[i]) {
                    tmax = max(tmax, dp[j] + 1);
                }
            }

            dp[i] = tmax;
        }

        int ans = 1;
        for (int i = 1; i <= n; i ++) {
            ans = max(ans, dp[i]);
        }

        printf("%d\n", ans);
    }
    return 0;
}
