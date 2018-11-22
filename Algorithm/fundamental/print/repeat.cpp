#include <stdio.h>
#include <stdlib.h>

/*
   5 @ W
    5: SIZE (0~80)
    @: INSIZE CHAR
    W: OUTSIZE CHAR
 */

char buf[81][81];

int main () {
    int size;
    char in, out;
    while (scanf("%d %c %c", &size, &in, &out) == 3) {
        // color == 0: outsize is out
        // color == 1: outsize is in
        int color = (size / 2 + 1) % 2;
        for (int con = 1; con <= (size / 2) + 1; con ++) {
            for (int i = con; i <= size - (con - 1); i++) {
                for (int j = con; j <= size - (con - 1); j ++) {
                    buf[i][j] = color ? in : out;
                }
            }
            color = color ? 0 : 1;
        }

        // print
        for (int i = 1; i <= size; i ++) {
            for (int j = 1; j <= size; j ++) {
                if ((i == 1 && j == 1) || (i == 1 && j == size)||
                    (i == size && j == 1) || (i == size && j == size)) printf(" ");
                else printf("%c", buf[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
