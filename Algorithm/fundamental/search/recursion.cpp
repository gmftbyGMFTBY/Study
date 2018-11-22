#include <stdio.h>
#include <iostream>
#include <stdlib.h>

/*
   book page 171
 */

using namespace std;

long long F (int num) {
    if (num == 1) return 2;
    else return 3 * F (num - 1) + 2;
}

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {
        // lld means the long long int 
        printf("%lld\n", F(n));
    }
    return 0;
}
