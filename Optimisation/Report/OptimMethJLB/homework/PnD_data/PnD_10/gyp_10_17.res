GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_17.dat -o glp_10_17.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_17.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.000e+01  ratio =  4.000e+01
GM: min|aij| =  4.729e-01  max|aij| =  2.115e+00  ratio =  4.472e+00
EQ: min|aij| =  2.236e-01  max|aij| =  1.000e+00  ratio =  4.472e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.312e+00  ratio =  5.250e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -1.530000000e+03 inf =   1.036e+02 (10)
     25: obj =   2.130000000e+02 inf =   3.331e-16 (0)
*    35: obj =  -1.421085472e-14 inf =   1.110e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    35: mip =     not found yet >=              -inf        (1; 0)
+   411: >>>>>   3.060000000e+02 >=   2.309263891e-14 100.0% (86; 1)
+   710: >>>>>   2.170000000e+02 >=   1.500000000e+01  93.1% (133; 7)
+  1227: >>>>>   1.880000000e+02 >=   1.600000000e+01  91.5% (226; 11)
+  2390: >>>>>   1.810000000e+02 >=   2.300000000e+01  87.3% (406; 32)
+  2626: >>>>>   1.480000000e+02 >=   2.800000000e+01  81.1% (435; 43)
+ 10474: >>>>>   1.420000000e+02 >=   5.000000000e+01  64.8% (1544; 259)
+ 29596: >>>>>   1.380000000e+02 >=   6.900000000e+01  50.0% (3792; 828)
+ 51614: >>>>>   1.360000000e+02 >=   8.500000000e+01  37.5% (5516; 1943)
+119243: >>>>>   1.340000000e+02 >=   1.260000000e+02   6.0% (2694; 12639)
+121489: >>>>>   1.330000000e+02 >=   1.284285714e+02   3.4% (1465; 16110)
+124484: mip =   1.330000000e+02 >=     tree is empty   0.0% (0; 23603)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   6.8 secs
Memory used: 6.8 Mb (7151649 bytes)
Writing MIP solution to 'glp_10_17.res'...
