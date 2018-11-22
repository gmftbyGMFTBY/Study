GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_26.dat -o glp_10_26.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_26.dat...
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
GM: min|aij| =  5.886e-01  max|aij| =  1.699e+00  ratio =  2.887e+00
EQ: min|aij| =  3.464e-01  max|aij| =  1.000e+00  ratio =  2.887e+00
2N: min|aij| =  3.750e-01  max|aij| =  1.562e+00  ratio =  4.167e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -1.260000000e+03 inf =   8.675e+01 (10)
     25: obj =   1.519386401e+02 inf =   1.110e-15 (0)
*    35: obj =   8.881784197e-16 inf =   4.996e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    35: mip =     not found yet >=              -inf        (1; 0)
+   218: >>>>>   3.700000000e+02 >=   1.700000000e+01  95.4% (41; 0)
+   391: >>>>>   3.090000000e+02 >=   1.700000000e+01  94.5% (73; 5)
+   487: >>>>>   2.910000000e+02 >=   1.700000000e+01  94.2% (92; 16)
+   939: >>>>>   1.950000000e+02 >=   1.900000000e+01  90.3% (187; 24)
+  3824: >>>>>   1.930000000e+02 >=   4.100000000e+01  78.8% (695; 101)
+ 31571: >>>>>   1.900000000e+02 >=   8.800000000e+01  53.7% (4501; 925)
+ 41275: >>>>>   1.890000000e+02 >=   9.800000000e+01  48.1% (5510; 1422)
+ 45299: >>>>>   1.740000000e+02 >=   1.010000000e+02  42.0% (5862; 1673)
+120883: mip =   1.740000000e+02 >=   1.600000000e+02   8.0% (2968; 14406)
+130053: mip =   1.740000000e+02 >=     tree is empty   0.0% (0; 26543)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   7.8 secs
Memory used: 7.0 Mb (7360133 bytes)
Writing MIP solution to 'glp_10_26.res'...
