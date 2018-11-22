#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   binarysearch change the O(L) to O(logL)
   need to sort first
 */

struct student {
    char no[100];
    char name[100];
    int age;
    char sex[5];
}buf[1001];

int cmp (const void* a, const void* b) {
    struct student arg1 = *(const struct student*) a;
    struct student arg2 = *(const struct student*) b;
    return strcmp(arg1.no, arg2.no);
} 

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {
       for (int i = 0; i < n; i ++) {
           scanf("%s%s%s%d", buf[i].no, buf[i].name, buf[i].sex, &buf[i].age);
       } 

       qsort(buf, n, sizeof(buf[0]), cmp);

       // binary search
       int t;
       scanf("%d", &t);
       while (t--) {
           int ans = -1;
           char x[30];
           scanf("%s", x);    // target

           int top = n - 1;
           int base = 0;

           while (top >= base) {
               int mid = (top + base) / 2;
               int tmp = strcmp(buf[mid].no, x);
               if (tmp == 0) {
                   ans = mid;
                   break;
               }
               else if (tmp > 0) top = mid - 1;
               else base = mid + 1;
           }

           if (ans == -1) {
               printf("No Answer!\n");
           }
           else printf("%s %s %s %d\n", buf[ans].no, buf[ans].name, buf[ans].sex, buf[ans].age);
       }
    }
    return 0;
}
