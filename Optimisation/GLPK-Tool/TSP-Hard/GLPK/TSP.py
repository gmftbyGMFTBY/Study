from pulp import *
import sys
import re
import os
from itertools import *

url = '/home/lantian/File/Study Coding/Optimisation/GLPK-Tool/TSP-Hard/GLPK'
number = sys.argv[1]  # Catch the size of the n.

def solve(n , w , h):
    global number
    p = LpProblem('The TSP Problem in ' + number + 'data.',LpMinimize)
    x = LpVariable.matrix('0b',(range(0,n+1),range(0,n+1)),cat='Binary')
    l = LpVariable.matrix('l',(range(0,n+1)),cat='Integer')
    # Objective
    p += sum([l[i] for i in range(1,n+1)]) , 'The minimize of the problem'
    # Constraints begin!
    p += l[1] == 0 , 'l[1] must >= 0'
    p += l[n] == 0 , 'l[n] must >= 0'
    for i in range(1,n+1):
        p += sum(x[i][j] for j in range(1,n+1)) == 1,'x_row' + str(i)
    for i in range(1,n+1):
        p += sum(x[j][i] for j in range(1,n+1)) == 1,'x_col' + str(i)
    for i in range(2,n):
        p += l[i] == l[i-1] + sum([x[j][i]*w[j-1] for j in range(1,n+1)]) , 'l[k]>='+str(i)
    for i in range(2,n):
        p += l[i] >= 0 , 'l[' + str(i) + '] >= 0'
    # Constraints end!
    #print(p)
    p.writeLP(url+'/new/PnD_'+number+'/pnd_'+number+'_'+h+'.que',writeSOS=1,mip=1)
    p.solve()
    return p,x

def write(i,j,k):
    global number
    #target = url + '/new/PnD_' + number + '/pnd_' + number + '_' + k + '.res'
    #os.system('touch ' + target)
    w = open(url+'/new/PnD_'+number+'/pnd_'+number+'_'+k+'.res','w')
    w.write("Status: " + LpStatus[i.status] + '\n')
    w.write('Solution: ' + str(value(i.objective)) + '\n')
    w.close()
    print('Write in the file successfully!')

for i in range(1,31):
    if i < 10:i = '0'+str(i)
    else:i = str(i)
    with open(url+'/prepare/PnD_'+number+'/pnd_'+number+'_'+i+'.dat','r') as f:
        f.readline()
        n = int(sys.argv[1])   # The size of the n
        data = list(map(lambda x:int(x) , f.readline().strip('\n').split()))
        k,j = solve(n,data,i) # solve and do not write in the file , p is the data of the problem
        write(k,j,i)    # Write in the file
        print('Instance ' + i + ' has been created!')

print('All the Work on Instances ' + number + ' is done!')

