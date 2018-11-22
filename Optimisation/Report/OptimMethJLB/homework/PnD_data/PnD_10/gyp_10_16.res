GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_16.dat -o glp_10_16.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_16.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  7.200e+01  ratio =  7.200e+01
GM: min|aij| =  4.082e-01  max|aij| =  2.449e+00  ratio =  6.000e+00
EQ: min|aij| =  1.667e-01  max|aij| =  1.000e+00  ratio =  6.000e+00
2N: min|aij| =  1.250e-01  max|aij| =  1.000e+00  ratio =  8.000e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   1.260000000e+03 inf =   8.000e+00 (1)
     16: obj =   5.050000000e+02 inf =   0.000e+00 (0)
*    25: obj =   2.131628207e-14 inf =   0.000e+00 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    25: mip =     not found yet >=              -inf        (1; 0)
+   445: >>>>>   3.320000000e+02 >=   2.000000000e+00  99.4% (87; 3)
+  1145: >>>>>   3.090000000e+02 >=   1.100000000e+01  96.4% (219; 9)
+  1253: >>>>>   3.040000000e+02 >=   1.300000000e+01  95.7% (236; 13)
+  2522: >>>>>   2.700000000e+02 >=   2.700000000e+01  90.0% (433; 34)
+  3183: >>>>>   2.540000000e+02 >=   3.100000000e+01  87.8% (519; 67)
+  3957: >>>>>   2.420000000e+02 >=   3.600000000e+01  85.1% (612; 105)
+ 10522: >>>>>   2.350000000e+02 >=   6.400000000e+01  72.8% (1545; 277)
+ 29028: >>>>>   2.300000000e+02 >=   1.033423913e+02  55.1% (3705; 917)
+107849: mip =   2.300000000e+02 >=     tree is empty   0.0% (0; 21353)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   5.5 secs
Memory used: 6.0 Mb (6301025 bytes)
Writing MIP solution to 'glp_10_16.res'...
