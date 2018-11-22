#!/usr/bin/python3

from numpy import *

def loadDataSet(filename):
    data = []
    f = open(filename)
    for line in f.readlines():
        cur = line.strip().split('\t')
        now = list(map(float , cur))
        data.append(now)
    f.close()
    return mat(data)

def distance(x , y):
    return sqrt(sum(power(x - y , 2)))

def randk(data , k):
    n = shape(data)[1]
    cent = mat(zeros((k,n)))
    for i in range(n):
        minp = min(data[:,i])
        rangep = float(max(data[: , i]) - minp)
        cent[: , i] = minp + rangep * random.rand(k , 1)
    return cent

if __name__ == "__main__":
    data = loadDataSet('./Ch10/testSet.txt')
    print(randk(data , 2))
