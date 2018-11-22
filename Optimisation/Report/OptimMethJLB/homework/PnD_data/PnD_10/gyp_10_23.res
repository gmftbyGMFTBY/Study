GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_23.dat -o glp_10_23.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_23.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.900e+01  ratio =  4.900e+01
GM: min|aij| =  5.915e-01  max|aij| =  1.690e+00  ratio =  2.858e+00
EQ: min|aij| =  3.499e-01  max|aij| =  1.000e+00  ratio =  2.858e+00
2N: min|aij| =  3.750e-01  max|aij| =  1.531e+00  ratio =  4.083e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -3.150000000e+02 inf =   2.769e+01 (10)
     26: obj =   2.300000000e+01 inf =   7.048e-16 (0)
*    30: obj =   0.000000000e+00 inf =   3.331e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    30: mip =     not found yet >=              -inf        (1; 0)
+   226: >>>>>   3.960000000e+02 >=   7.000000000e+00  98.2% (38; 0)
+   359: >>>>>   3.810000000e+02 >=   8.000000000e+00  97.9% (64; 1)
+   459: >>>>>   2.970000000e+02 >=   8.000000000e+00  97.3% (84; 2)
+   534: >>>>>   2.920000000e+02 >=   1.100000000e+01  96.2% (96; 6)
+   742: >>>>>   2.330000000e+02 >=   1.100000000e+01  95.3% (145; 8)
+  1372: >>>>>   2.270000000e+02 >=   1.300000000e+01  94.3% (255; 28)
+  1528: >>>>>   1.960000000e+02 >=   1.500000000e+01  92.3% (289; 30)
+  4036: >>>>>   1.790000000e+02 >=   1.900000000e+01  89.4% (732; 74)
+  6603: >>>>>   1.760000000e+02 >=   2.400000000e+01  86.4% (1178; 137)
+ 13659: >>>>>   1.330000000e+02 >=   3.300000000e+01  75.2% (2367; 298)
+ 74439: >>>>>   1.310000000e+02 >=   7.700000000e+01  41.2% (7810; 3764)
+135094: mip =   1.310000000e+02 >=   1.150000000e+02  12.2% (4584; 15373)
+144998: mip =   1.310000000e+02 >=     tree is empty   0.0% (0; 32329)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   10.0 secs
Memory used: 9.0 Mb (9398653 bytes)
Writing MIP solution to 'glp_10_23.res'...
