#include <stdio.h> 
#include <stdlib.h>

/*
   input n number, output top m number 
   number are all in [-500000, 500000]
   n and m constraints: 0 < n < m < 1000000

   Can not use sort, O(nlogn) exceed the 1000000
   Use the hash (-500000, 500000)
 */

int hash[1000001];

int main () {
    int n, m;

    // init
    while (scanf("%d%d", &n, &m) !=EOF) {
        for (int i = -500000; i <= 500000; i ++) {
            hash[i + 500000] = 0;
        }
    
        for (int i = 1; i <= n; i ++) {
            int x;
            scanf("%d", &x);
            hash[x + 500000] = 1;    // save but not count
        }

        for (int i = 500000; i >= -500000; i --) {
            if (hash[i + 500000] == 1) {
                printf("%d", i);
                m --;
                if (m != 0) printf(" ");
                else {
                    printf("\n");
                    break;
                }
            }
        }
    }
    return 0;
}
