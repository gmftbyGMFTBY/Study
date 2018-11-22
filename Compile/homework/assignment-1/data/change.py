#!/usr/bin/python3

with open('matrix_c', 'r') as f:
    ff = open('c', 'w')
    for line in f.readlines():
        n = line.split()
        w = '['
        n = w + ','.join(n) + '],'
        ff.write(n)
