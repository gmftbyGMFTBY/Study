#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

/*
   change all the different base number into the 10 base and change the 10 base into 
   another base which we want.

   change the number with Aab3 the base 15 into the base 7
   Input:
       15 Aab3 7    // Noted that `A` is the same mean as the `a`
   Output:
       210306
 */

using namespace std;

int main () {
    int a, b;
    char str[50];

    while (scanf("%d%s%d", &a, str, &b) != EOF) {
        // tmp save the 10 base number, c means the weight
        int tmp = 0, lenth = strlen(str);
        int c = 1;

        for (int i = lenth - 1; i >= 0; i--) {
            int x;
            if (str[i] >= '0' && str[i] <= '9') x = str[i] - '0';
            else if (str[i] >= 'a' && str[i] <= 'z') x = str[i] - 'a' + 10;
            else x = str[i] - 'A' + 10;

            tmp += x * c;
            c *= a;
        }

        char ans[50], size = 0;
        
        // reverse it or print it reversely
        while (tmp) {
            int x = tmp % b;
            ans[size ++] = (x < 10) ? x + '0' : x - 10 + 'A';
            tmp /= b;
        }

        for (int i = size - 1; i >= 0; i --) {
            printf("%c", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
