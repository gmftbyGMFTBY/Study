#!/usr/bin/python3.6

LMAX = 30;
RMAX = 30;
CMAX = 30;
import random

for i in range(2):
    mymap = [[random.randint(0,1) for i in range(30)] for i in range(30)]
    for li , i in enumerate(mymap):
        for lj , j in enumerate(i):
            if j == 0 : mymap[li][lj] = '.'
            else : mymap[li][lj] = '#'

    for i in mymap:
        for j in i:
            print(j , end='')
        print()
    print()
