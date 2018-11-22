#!/usr/bin/python
# Author : GMFTBY
# Time   : 2018.2.27

import sys
import numpy as np

def numpy_matrix(a, b):
    # a, b must be the numpy array
    return np.dot(a, b)

def pure_matrix(a, b, c):
    # a, b, c must be the numpy array
    c_row, c_col = a.shape[0], b.shape[1]
    for row in range(c_row):
        for col in range(c_col):
            s = 0
            for index in range(a.shape[1]):
                s += a[row][index] * b[index][col]
            c[row][col] = s

def read_file(path):
    # read file from the path
    with open(path, 'r') as f:
        a = []
        for row in f.readlines():
            n_row = list(map(int, row.split()))
            a.append(n_row)
    return np.array(a)

if __name__ == "__main__":
    # read the data
    a = read_file('../../data/matrix_a')
    b = read_file('../../data/matrix_b')
    c = read_file('../../data/matrix_c')
