#include <stdio.h>
#include <stdlib.h>

/*
 sort the int array
 */

int cmp(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    // return negative do not swap, return positive swap (a, b)
    return (arg1 > arg2 ) - (arg1 < arg2);
}

int main () {
    int n;
    int buf[10000];
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i ++) {
            scanf("%d", &buf[i]);
        }
        qsort(buf, n, sizeof(int), cmp);
        for (int i = 0; i < n; i++) {
            printf("%d ", buf[i]);
        }
        printf("\n");
    }
    return 0;
}
