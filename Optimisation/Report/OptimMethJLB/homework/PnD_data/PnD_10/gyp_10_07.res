GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_07.dat -o glp_10_07.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_07.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.600e+01  ratio =  4.600e+01
GM: min|aij| =  8.151e-01  max|aij| =  1.227e+00  ratio =  1.505e+00
EQ: min|aij| =  6.700e-01  max|aij| =  1.000e+00  ratio =  1.493e+00
2N: min|aij| =  6.562e-01  max|aij| =  1.438e+00  ratio =  2.190e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   1.350000000e+03 inf =   1.600e+01 (1)
     20: obj =   1.156618182e+02 inf =   0.000e+00 (0)
*    25: obj =  -3.552713679e-15 inf =   1.110e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    25: mip =     not found yet >=              -inf        (1; 0)
+   876: >>>>>   4.180000000e+02 >=   2.200000000e+01  94.7% (221; 9)
+  1213: >>>>>   2.130000000e+02 >=   4.300000000e+01  79.8% (304; 12)
+  1703: >>>>>   2.110000000e+02 >=   4.600000000e+01  78.2% (394; 47)
+  1993: >>>>>   1.950000000e+02 >=   4.700000000e+01  75.9% (457; 59)
+  3041: >>>>>   1.890000000e+02 >=   6.223913043e+01  67.1% (637; 100)
+  8252: >>>>>   1.810000000e+02 >=   8.500000000e+01  53.0% (1519; 246)
+ 16278: >>>>>   1.770000000e+02 >=   9.717391304e+01  45.1% (2603; 643)
+ 88512: mip =   1.770000000e+02 >=     tree is empty   0.0% (0; 16381)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   4.6 secs
Memory used: 4.8 Mb (4983579 bytes)
Writing MIP solution to 'glp_10_07.res'...
