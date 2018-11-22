GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_12.dat -o glp_10_12.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_12.dat...
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
      0: obj =  -3.600000000e+02 inf =   3.050e+01 (10)
     30: obj =   3.146368039e+01 inf =   3.886e-16 (0)
*    35: obj =   5.928590951e-14 inf =   2.741e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    35: mip =     not found yet >=              -inf        (1; 0)
+   224: >>>>>   3.930000000e+02 >=   8.000000000e+00  98.0% (37; 0)
+   351: >>>>>   3.260000000e+02 >=   8.000000000e+00  97.5% (61; 5)
+  1022: >>>>>   2.120000000e+02 >=   9.000000000e+00  95.8% (201; 12)
+  1268: >>>>>   1.620000000e+02 >=   9.000000000e+00  94.4% (230; 38)
+  3749: >>>>>   1.610000000e+02 >=   1.700000000e+01  89.4% (660; 99)
+ 16988: >>>>>   1.500000000e+02 >=   3.600000000e+01  76.0% (2776; 463)
+ 32465: >>>>>   1.490000000e+02 >=   5.400000000e+01  63.8% (4518; 1351)
+ 61698: >>>>>   1.470000000e+02 >=   7.600000000e+01  48.3% (6845; 2934)
+132767: mip =   1.470000000e+02 >=   1.260000000e+02  14.3% (4446; 14295)
+146898: mip =   1.470000000e+02 >=     tree is empty   0.0% (0; 30473)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   9.2 secs
Memory used: 8.1 Mb (8507435 bytes)
Writing MIP solution to 'glp_10_12.res'...
