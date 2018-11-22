#!/usr/bin/python3

import sys
import re

p = sys.argv[1]

url1 = '/home/lantian/File/Study Coding/Optimisation/GLPK-Tool/TSP-Hard/GLPK/new/PnD_'+str(p)+'/new_glp_'+str(p)+'_'
url2 = '/home/lantian/File/Study Coding/Optimisation/GLPK-Tool/TSP-Hard/GLPK/prepare/PnD_'+str(p)+'/glp_'+str(p)+'_'

pattern=re.compile('^Objective:  [a-zA-Z]+ = ([0-9]+)')
flag = True

for i in range(1,31):
    if i < 10:p = '0'+str(i)
    else:p = str(i)
    f1 = open(url1+p+'.res','r')
    f2 = open(url2+p+'.res','r')
    ans1 = f1.readlines()
    ans2 = f2.readlines()
    res1 = []
    res2 = []
    for i in ans1:
        w = pattern.match(i)
        if w:
            res1 = w.group(1)
            break
    for i in ans2:
        w = pattern.match(i)
        if w:
            res2 = w.group(1)
            break
    if res1 != res2:
        flag = False
        print('Error Instance:\n'+url2+p+'.res')
        break
    f1.close()
    f2.close()
if flag == True:
    print('Complete Correctly!')

