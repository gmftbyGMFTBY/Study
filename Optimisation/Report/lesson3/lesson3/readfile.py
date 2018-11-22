#!/usr/local/bin/python3
# -*- coding: UTF-8 -*-

# Optimization Methods 
# 2017/04/22 JLB at BIT

# an auxiliary function

def read_file(namefile):
    """Reads a file and returns its content
    Input: name of the file to read
    Output: the 3 lists that are in the file."""
    fic = open(namefile,'rt')
    s = fic.readline()
    n = int(s)
    s = fic.readline()
    l = s.split(' ')
    lp1 = [int(x) for x in l]
    s = fic.readline()
    l = s.split(' ')
    lp2 = [int(x) for x in l]
    s = fic.readline()
    l = s.split(' ')
    ld = [int(x) for x in l]
    fic.close()
    return (lp1,lp2,ld)

