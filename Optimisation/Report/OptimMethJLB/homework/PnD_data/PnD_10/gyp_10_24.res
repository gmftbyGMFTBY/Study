GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_24.dat -o glp_10_24.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_24.dat...
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
GM: min|aij| =  6.718e-01  max|aij| =  1.489e+00  ratio =  2.216e+00
EQ: min|aij| =  4.513e-01  max|aij| =  1.000e+00  ratio =  2.216e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.406e+00  ratio =  5.625e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -4.950000000e+02 inf =   3.894e+01 (10)
     28: obj =   1.214150943e+02 inf =   9.437e-16 (0)
*    34: obj =   1.776356839e-15 inf =   2.220e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    34: mip =     not found yet >=              -inf        (1; 0)
+   455: >>>>>   3.860000000e+02 >=   4.600000000e+01  88.1% (107; 2)
+   719: >>>>>   3.470000000e+02 >=   5.100000000e+01  85.3% (177; 4)
+   999: >>>>>   2.700000000e+02 >=   6.006666667e+01  77.8% (232; 11)
+  1068: >>>>>   2.640000000e+02 >=   6.064285714e+01  77.0% (237; 23)
+  2626: >>>>>   2.100000000e+02 >=   7.714285714e+01  63.3% (542; 50)
+  8371: >>>>>   2.060000000e+02 >=   1.110000000e+02  46.1% (1358; 348)
+  9690: >>>>>   2.020000000e+02 >=   1.170000000e+02  42.1% (1494; 453)
+ 22111: >>>>>   2.000000000e+02 >=   1.469090909e+02  26.5% (2493; 1138)
+ 43961: >>>>>   1.980000000e+02 >=   1.860000000e+02   6.1% (1402; 4360)
+ 48491: mip =   1.980000000e+02 >=     tree is empty   0.0% (0; 9583)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   2.2 secs
Memory used: 2.9 Mb (3036239 bytes)
Writing MIP solution to 'glp_10_24.res'...
