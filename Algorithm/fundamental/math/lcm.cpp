#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/*
   The LCM which is suit for the GCD
   find the min c which match that c % a = 0 and c % b = 0
   
   LCM = a * b / gcd (a, b)
 */

using namespace std;

int gcd (int a, int b) {
    return b != 0 ? gcd (b, a % b) : a;
}

int main () {
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        printf("%d\n", a * b / gcd (a, b));
    }
    return 0;
}
