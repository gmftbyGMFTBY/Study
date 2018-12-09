#include <stdio.h>
#include <stdlib.h>

/*
   Output a trapezoid with h height
       ****
     ******
   ********  
 **********
 */

int main () {
    int h;
    while (scanf("%d", &h) != EOF) {
        for (int i = 1; i <= h; i++ ) {
            // print empty
            for (int j = 1; j <= 2 * (h - i); j++) {
                printf(" ");
            }

            // print *
            for (int j = 1; j <= h + 2 * (i - 1); j++) {
                printf("*");
            }

            printf("\n");
        }
    }
    return 0;
}
