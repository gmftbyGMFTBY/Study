#include <stdio.h>
#include <stdlib.h>

/*
   the date counter
 */

#define YEAR(x) x % 100 != 0 && x % 4 == 0 || x % 400 == 0 ? 1 : 0

int dayofmonth[13][2] = {
    0, 0,
    31, 31,
    28, 29,
    31, 31,
    30, 30,
    31, 31,
    30, 30,
    31, 31,
    31, 31,
    30, 30,
    31, 31,
    30, 30,
    31, 31
};

// class for date
struct date {
    int day;
    int month;
    int year;
    // calculate the next day
    void nextday () {
        day ++;
        if (day > dayofmonth[month][YEAR(year)]) {
            day = 1;
            month ++;
            if (month > 12) {
                month = 1;
                year ++;
            }
        }
    }
};

// this big memory can not set into the main function
// must put it in the stack heap to avoid the segmentfault
int buf[5001][13][32];

int abs(int x) {
    return x < 0 ? -x : x;
}

int main () {
    date tmp;
    int cnt = 0;
    tmp.day = 1;
    tmp.month = 1;
    tmp.year = 0;

    // predefine
    while (tmp.year != 5000) {
        buf[tmp.year][tmp.month][tmp.day] = cnt;
        tmp.nextday();
        cnt ++;
    }

    int d1, m1, y1;
    int d2, m2, y2;
    while (scanf("%4d%2d%2d", &y1, &m1, &d1) != EOF) {
        scanf("%4d%2d%2d", &y2, &m2, &d2);
        printf("%d\n", abs(buf[y2][m2][d2] - buf[y1][m1][d1]) + 1);
    }
    return 0;
}
