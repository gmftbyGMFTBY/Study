#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   Transfer the date into the week
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

struct date {
    int day;
    int month;
    int year;
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

int buf[3001][13][32];

char monthname[13][20] = {
    "",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

char weekname[7][20] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

int main () {
    // c++ do not need struct keyword
    date tmp;
    int cnt = 0;
    tmp.day = 1;
    tmp.month = 1;
    tmp.year = 0;
    while (tmp.year != 3000) {
        buf[tmp.year][tmp.month][tmp.day] = cnt;
        tmp.nextday();
        cnt ++;
    }

    int d, m, y;
    char s[20];

    while (scanf("%d %s %d", &d, s, &y) != EOF) {
        for (m = 1; m <= 12; m ++) {
            if (strcmp(s, monthname[m]) == 0) {
                break;
            }
        }

        // m save the month index, 2012.7.16 Monday
        int days = buf[y][m][d] - buf[2012][7][16];
        days += 1;

        // days maybe the negative
        printf("%s\n", weekname[(days % 7 + 7) % 7]);
    }
    return 0; 
}
