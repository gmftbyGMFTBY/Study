GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_06.dat -o glp_10_06.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_06.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  5.000e+01  ratio =  5.000e+01
GM: min|aij| =  4.472e-01  max|aij| =  2.236e+00  ratio =  5.000e+00
EQ: min|aij| =  2.000e-01  max|aij| =  1.000e+00  ratio =  5.000e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.562e+00  ratio =  6.250e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -7.650000000e+02 inf =   5.581e+01 (10)
     26: obj =   6.126298701e+01 inf =   3.608e-16 (0)
*    33: obj =   7.105427358e-15 inf =   2.776e-17 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    33: mip =     not found yet >=              -inf        (1; 0)
+   180: >>>>>   1.780000000e+02 >=   2.000000000e+00  98.9% (27; 0)
+ 10140: >>>>>   1.750000000e+02 >=   5.400000000e+01  69.1% (1591; 174)
+ 15711: >>>>>   1.720000000e+02 >=   6.448484848e+01  62.5% (2436; 353)
+ 33268: >>>>>   1.710000000e+02 >=   8.446808511e+01  50.6% (4525; 1067)
+ 64474: >>>>>   1.680000000e+02 >=   1.105000000e+02  34.2% (6704; 2816)
+126412: mip =   1.680000000e+02 >=     tree is empty   0.0% (0; 25889)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   7.0 secs
Memory used: 7.2 Mb (7600643 bytes)
Writing MIP solution to 'glp_10_06.res'...
