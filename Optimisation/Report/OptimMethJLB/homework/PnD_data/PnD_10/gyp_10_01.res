GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_01.dat -o glp_10_01.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_01.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  5.400e+01  ratio =  5.400e+01
GM: min|aij| =  5.516e-01  max|aij| =  1.813e+00  ratio =  3.286e+00
EQ: min|aij| =  3.043e-01  max|aij| =  1.000e+00  ratio =  3.286e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.562e+00  ratio =  6.250e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   4.950000000e+02 inf =   8.000e+00 (1)
     23: obj =   6.600000000e+01 inf =   0.000e+00 (0)
*    32: obj =   7.105427358e-15 inf =   4.441e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    32: mip =     not found yet >=              -inf        (1; 0)
+   551: >>>>>   2.790000000e+02 >=   2.700000000e+01  90.3% (95; 3)
+   674: >>>>>   2.630000000e+02 >=   2.700000000e+01  89.7% (123; 4)
+   830: >>>>>   2.520000000e+02 >=   3.100000000e+01  87.7% (149; 7)
+  1216: >>>>>   2.480000000e+02 >=   3.200000000e+01  87.1% (218; 13)
+  1703: >>>>>   1.880000000e+02 >=   3.500000000e+01  81.4% (303; 23)
+ 10890: >>>>>   1.840000000e+02 >=   7.488190077e+01  59.3% (1569; 306)
+ 11431: >>>>>   1.810000000e+02 >=   7.632258065e+01  57.8% (1589; 383)
+ 25278: >>>>>   1.770000000e+02 >=   1.050000000e+02  40.7% (2987; 1042)
+ 27154: >>>>>   1.750000000e+02 >=   1.077272727e+02  38.4% (3002; 1342)
+ 35174: >>>>>   1.700000000e+02 >=   1.207627119e+02  29.0% (3304; 2066)
+ 62319: >>>>>   1.680000000e+02 >=   1.680000000e+02 < 0.1% (291; 11224)
+ 62319: mip =   1.680000000e+02 >=     tree is empty   0.0% (0; 13315)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   2.9 secs
Memory used: 3.5 Mb (3704407 bytes)
Writing MIP solution to 'glp_10_01.res'...
