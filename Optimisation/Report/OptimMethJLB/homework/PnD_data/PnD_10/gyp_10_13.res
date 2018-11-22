GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_13.dat -o glp_10_13.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_13.dat...
4 lines were read
Generating lbar...
Generating matrow...
Generating matcol...
Generating load1...
Generating load...
Model has been successfully generated
GLPK Integer Optimizer, v4.61
30 rows, 109 columns, 316 non-zeros
100 integer variables, all of which are binary
Preprocessing...
29 rows, 108 columns, 306 non-zeros
100 integer variables, all of which are binary
Scaling...
 A: min|aij| =  1.000e+00  max|aij| =  5.600e+01  ratio =  5.600e+01
GM: min|aij| =  6.148e-01  max|aij| =  1.627e+00  ratio =  2.646e+00
EQ: min|aij| =  3.780e-01  max|aij| =  1.000e+00  ratio =  2.646e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.562e+00  ratio =  6.250e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   9.000000000e+02 inf =   8.000e+00 (1)
     19: obj =   2.173250000e+02 inf =   0.000e+00 (0)
*    31: obj =   1.332267630e-15 inf =   2.220e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    31: mip =     not found yet >=              -inf        (1; 0)
+   192: >>>>>   2.080000000e+02 >=   1.500000000e+01  92.8% (37; 0)
+   686: >>>>>   1.810000000e+02 >=   2.300000000e+01  87.3% (122; 11)
+ 22891: >>>>>   1.800000000e+02 >=   8.200000000e+01  54.4% (3310; 596)
+ 33751: >>>>>   1.720000000e+02 >=   9.361591221e+01  45.6% (4358; 1084)
+ 34811: >>>>>   1.690000000e+02 >=   9.500000000e+01  43.8% (4143; 1606)
+ 54626: >>>>>   1.650000000e+02 >=   1.160000000e+02  29.7% (4826; 3085)
+ 97608: mip =   1.650000000e+02 >=     tree is empty   0.0% (0; 18461)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   4.7 secs
Memory used: 5.1 Mb (5328679 bytes)
Writing MIP solution to 'glp_10_13.res'...
