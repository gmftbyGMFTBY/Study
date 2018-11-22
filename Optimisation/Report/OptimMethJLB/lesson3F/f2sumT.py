#!/usr/local/bin/python3
# -*- coding: UTF-8 -*-

# Optimization Methods 
# 2017/05/03 JLB at BIT

# Resolution of the F2//Tbar problem

# import
import pulp as pl
from readfile import *

def solvef2(pb):
    """Compute the optimal solution of the pb
    using glpk through pulp
    Input: pb: list of (p1,p2,d) an instance of the pb
    Output: not the permutation s of [0..len(ld)-1] but only its tbar."""
    (p1,p2,d) = pb
    n = len(p1)
    ranks = range(0,n)
    jobs = range(0,n) # yes they are equal. Only to make it more clear
    
    prob = pl.LpProblem("f2//Tbar", pl.LpMinimize)
    # declaration of the x[k,j]
    x = pl.LpVariable.matrix("X", (ranks, jobs), 0, 1, pl.LpBinary)
    # variables F1, F2, G = completion times on machine 1 and 2 and tardiness
    f1 = pl.LpVariable.matrix("F1", ranks, 0, None, pl.LpInteger)
    f2 = pl.LpVariable.matrix("F2", ranks, 0, None, pl.LpInteger)
    g = pl.LpVariable.matrix("G", ranks, 0, None, pl.LpInteger)
    
    # objective function
    prob += pl.lpSum(g[k] for k in ranks), 'Tbar'
    
    # Constraints: sum of the rows = 1
    for k in ranks:
        prob += pl.lpSum(x[k][j] for j in jobs) == 1, "row_" + str(k)
    # Constraints: sum of the cols = 1
    for j in jobs:
        prob += pl.lpSum(x[k][j] for k in ranks) == 1, "col_" + str(j)
    # Constraints: f10 and f20
    prob += pl.lpSum(p1[j]*x[0][j] for j in jobs) == f1[0], "f10"
    prob += pl.lpSum((p1[j]+p2[j])*x[0][j] for j in jobs) == f2[0], "f20"
    # Constraints: operations on M1 and on M2
    for k in range(1,n):
        prob += f1[k-1] + pl.lpSum(p1[j]*x[k][j] for j in jobs) <= f1[k], "m1_"+str(k)
        prob += f2[k-1] + pl.lpSum(p2[j]*x[k][j] for j in jobs) <= f2[k], "m2_"+str(k)
    # Constraints: succession from M1 to M2
        prob += f1[k] + pl.lpSum(p2[j]*x[k][j] for j in jobs) <= f2[k], "m12_"+str(k)
    # Constraints: tardinesses
    for k in ranks:
        prob += g[k] + pl.lpSum(d[j]*x[k][j] for j in jobs) >= f2[k], "tar_"+str(k)

    # Creation of the lp model 
    prob.writeLP('f2pb.lp', writeSOS=1, mip=1)
    
    # Solve the pb
    prob.solve(pl.GLPK(msg=0)) # or msg=1 if you want it verbose

    # Print the status of the solved LP
    print("MIP resolution: ", pl.LpStatus[prob.status])
    # the objective function
    tbar = pl.value(prob.objective)
    # Retrieving the permutation
    s = []
    for k in ranks:
        for j in jobs:
            if (x[k][j].varValue == 1):
                s.append(j)
    return (s,tbar)
################################################   
       
pb = read_file('f2d_10_05.dat')
#print(pb)
(s,tbar) = solvef2(pb)
print('The Tbar is ',tbar,' with the permutation ',s)




