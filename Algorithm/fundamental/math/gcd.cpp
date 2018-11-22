#include <stdio.h>
#include <iostream>
#include <stdlib.h>

/*
   gcd (a, b): find the max c which match that a % c = 0 and b % c = 0

   gcd (a, b) = gcd (b, a % b)
 */

using namespace std;

// gcd function 
int gcd (int a, int b) {
    if (b == 0) return a;   // if one is 0, return another
    else return gcd(b, a % b);
}

int main () {
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        printf("%d\n", gcd(a, b));
    }
    return 0;
}
