#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/*
   quick way to get the a^b

   For example, b's binary description is 1010 (10)
   which is means a^10 can be divide into a^2 * a^8

   O(n) to O(logn) which n is the size of b
 */

using namespace std;

int qpow (int a, int b) {
    int ans = 1;    // ans save the result
    while (b != 0) {
        if (b % 2 == 1) {
            ans *= a;   // only when the binary pos is 1, ans save the number result of a
            ans %= 1000;    // get the last three number
        } 
        
        // else continue multiply the a and decay the b
        b /= 2;
        a *= a;
        a %= 1000;
    }
    return ans;
}

int main () {
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        if (a == 0 && b == 0) break;
        printf("%d\n", qpow(a, b));
    }
    return 0;
}
