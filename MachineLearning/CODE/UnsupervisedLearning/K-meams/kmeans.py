#!/usr/bin/python3

from utils import *
from numpy import *

def kmeans(data , k , distance = distance , creatk = randk):
    m = shape(data)[0]
    cluster = mat(zeros((m , 2)))
    cent = creatk(data , k)
    clusterchange = True
    while clusterchange:
        clusterchange = False
        for i in range(m):
            minp = inf
            minindex = -1
            for j in range(k):
                dis = distance(cent[j,:] , data[i,:])
                if dis < minp :
                    minp = dis
                    minindex = j
            if cluster[i,0] != minindex :
                clusterchange = True
                cluster[i,:] = minindex , minp**2
        for i in range(k):
            p = data[nonzero(cluster[:,0].A == i)[0]]
            cent[i , :] = mean(p , axis = 0)
    return cent , cluster

if __name__ == "__main__":
    data = loadDataSet('./Ch10/testSet.txt')
    a ,b = kmeans(data , 4)
    print(a)
