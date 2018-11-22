GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_29.dat -o glp_10_29.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_29.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  3.600e+01  ratio =  3.600e+01
GM: min|aij| =  7.071e-01  max|aij| =  1.414e+00  ratio =  2.000e+00
EQ: min|aij| =  5.000e-01  max|aij| =  1.000e+00  ratio =  2.000e+00
2N: min|aij| =  5.000e-01  max|aij| =  1.125e+00  ratio =  2.250e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -9.900000000e+02 inf =   7.788e+01 (10)
     26: obj =   1.340000000e+02 inf =   0.000e+00 (0)
*    37: obj =  -1.776356839e-15 inf =   1.110e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    37: mip =     not found yet >=              -inf        (1; 0)
+   339: >>>>>   2.890000000e+02 >=   1.100000000e+01  96.2% (69; 1)
+   440: >>>>>   1.930000000e+02 >=   1.400000000e+01  92.7% (86; 3)
+  2284: >>>>>   1.670000000e+02 >=   3.600000000e+01  78.4% (425; 37)
+  2871: >>>>>   1.650000000e+02 >=   3.600000000e+01  78.2% (496; 90)
+  3020: >>>>>   1.610000000e+02 >=   3.600000000e+01  77.6% (519; 102)
+ 24210: >>>>>   1.530000000e+02 >=   7.200000000e+01  52.9% (3418; 575)
+ 51948: >>>>>   1.510000000e+02 >=   9.400000000e+01  37.7% (5796; 2040)
+126155: mip =   1.510000000e+02 >=     tree is empty   0.0% (0; 23107)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   7.0 secs
Memory used: 6.6 Mb (6870577 bytes)
Writing MIP solution to 'glp_10_29.res'...
