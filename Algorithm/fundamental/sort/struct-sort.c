#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   sort the struct array
 */

struct E {
    char name[101];
    int age;
    int score;
}buf[1000];

int cmp(const void* a, const void* b) {
    struct E arg1 = *(const struct E*)a;
    struct E arg2 = *(const struct E*)b;

    // negative return value: swap (a, b) to (b, a)
    // positive return value: do not swap (a, b)
    if (arg1.score != arg2.score) 
        return arg1.score - arg2.score;
    int temp = strcmp(arg1.name, arg2.name);
    if (temp != 0) 
        return temp;
    else 
        return arg1.age - arg2.age;
}

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i ++) {
            scanf("%s%d%d", buf[i].name, &buf[i].age, &buf[i].score);
        }
        // sort
        qsort(buf, n, sizeof(buf[0]), cmp) ;
        for (int i = 0; i < n; i ++) {
            printf("%s %d %d\n", buf[i].name, buf[i].age, buf[i].score);
        }
    }
    return 0;
}
