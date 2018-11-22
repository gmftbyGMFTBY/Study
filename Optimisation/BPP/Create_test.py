#!/usr/bin/python3
from random import *
import sys

t = sys.argv[1]

with open('test' + t , 'w') as f:
    n = input("Please input the size of the question : ")
    time = input("Please input the time of the iteration : ")
    ph = input("Please input the height of the BOX : ")
    pw = input("Please input the weight of the BOX : ")
    f.write(n +'\n' + time +'\n'+ ph+'\n' + pw + '\n' )
    xw = list(range(int(n)))
    xh = list(range(int(n)))
    while True :
        for i in range(int(n)):
            xw[i] = randint(1 , int(int(pw) * 0.4))
            xh[i] = randint(1 , int(int(ph) * 0.4))
        sum = 0
        for i in range(int(n)):
            sum += xw[i] * xh[i]
        sum = sum // int(n)
        if int(ph) * int(pw) / (3*int(n)) < sum < int(ph) * int(pw) *3 /int(n):
            break
    for i in range(int(n)):
        f.write(str(xh[i]) + ' ')
    f.write('\n')
    for i in range(int(n)):
        f.write(str(xw[i]) +' ')
    f.write('\n')

