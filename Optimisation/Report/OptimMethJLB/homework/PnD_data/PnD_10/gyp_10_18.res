GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_18.dat -o glp_10_18.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_18.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.500e+01  ratio =  4.500e+01
GM: min|aij| =  4.591e-01  max|aij| =  2.178e+00  ratio =  4.743e+00
EQ: min|aij| =  2.108e-01  max|aij| =  1.000e+00  ratio =  4.743e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.406e+00  ratio =  5.625e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   7.650000000e+02 inf =   8.000e+00 (1)
     20: obj =   3.816666667e+01 inf =   5.551e-17 (0)
*    25: obj =   0.000000000e+00 inf =   5.551e-17 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    25: mip =     not found yet >=              -inf        (1; 0)
+   172: >>>>>   2.300000000e+02 >=   0.000000000e+00 100.0% (19; 0)
+   648: >>>>>   2.080000000e+02 >=   7.000000000e+00  96.6% (107; 3)
+   797: >>>>>   1.860000000e+02 >=   1.000000000e+01  94.6% (133; 5)
+   904: >>>>>   1.710000000e+02 >=   1.000000000e+01  94.2% (143; 11)
+   988: >>>>>   1.570000000e+02 >=   1.200000000e+01  92.4% (155; 18)
+  1279: >>>>>   1.500000000e+02 >=   1.600000000e+01  89.3% (192; 27)
+  1453: >>>>>   1.300000000e+02 >=   1.700000000e+01  86.9% (226; 34)
+  3754: >>>>>   1.220000000e+02 >=   2.500000000e+01  79.5% (552; 101)
+ 12856: >>>>>   1.200000000e+02 >=   4.200000000e+01  65.0% (1664; 326)
+ 15236: >>>>>   1.150000000e+02 >=   4.500000000e+01  60.9% (1885; 438)
+ 76092: mip =   1.150000000e+02 >=     tree is empty   0.0% (0; 14385)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   3.6 secs
Memory used: 4.0 Mb (4177827 bytes)
Writing MIP solution to 'glp_10_18.res'...
