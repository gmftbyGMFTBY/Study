#include <stdio.h>
#include <stdlib.h>

/*
   choose the end-time as the optimal option
 */

struct program {
    int start;
    int end;
}buf[100];

int cmp (const void* a, const void* b) {
    struct program arg1 = *(const struct program*) a;
    struct program arg2 = *(const struct program*) b;

    return arg1.end - arg2.end;
}

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &buf[i].start, &buf[i].end);
        }

        qsort(buf, n, sizeof(buf[0]), cmp);

        int time = 0, result = 0;
        for (int i = 0; i < n; i++) {
            if (time <= buf[i].start) {
                time = buf[i].end;
                result ++;
            }
        }

        printf("%d\n", result);
    }
    return 0;
}
