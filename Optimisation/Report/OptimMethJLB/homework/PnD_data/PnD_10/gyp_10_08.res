GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_08.dat -o glp_10_08.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_08.dat...
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
GM: min|aij| =  3.840e-01  max|aij| =  2.604e+00  ratio =  6.782e+00
EQ: min|aij| =  1.474e-01  max|aij| =  1.000e+00  ratio =  6.782e+00
2N: min|aij| =  1.250e-01  max|aij| =  1.438e+00  ratio =  1.150e+01
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -8.550000000e+02 inf =   6.144e+01 (10)
     31: obj =   1.423714286e+02 inf =   5.551e-17 (0)
*    45: obj =   0.000000000e+00 inf =   8.327e-17 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    45: mip =     not found yet >=              -inf        (1; 0)
+   332: >>>>>   2.460000000e+02 >=   7.000000000e+00  97.2% (62; 1)
+   596: >>>>>   1.890000000e+02 >=   8.000000000e+00  95.8% (122; 7)
+  2395: >>>>>   1.770000000e+02 >=   2.000000000e+01  88.7% (422; 46)
+  4272: >>>>>   1.750000000e+02 >=   2.900000000e+01  83.4% (735; 94)
+  4836: >>>>>   1.690000000e+02 >=   3.400000000e+01  79.9% (828; 112)
+  5919: >>>>>   1.670000000e+02 >=   3.600000000e+01  78.4% (1006; 161)
+  7219: >>>>>   1.600000000e+02 >=   3.900000000e+01  75.6% (1189; 214)
+ 11653: >>>>>   1.520000000e+02 >=   5.200000000e+01  65.8% (1770; 410)
+ 17319: >>>>>   1.500000000e+02 >=   6.100000000e+01  59.3% (2316; 779)
+ 20190: >>>>>   1.450000000e+02 >=   6.510256410e+01  55.1% (2551; 994)
+ 40720: >>>>>   1.440000000e+02 >=   9.400000000e+01  34.7% (3625; 2424)
+ 76620: mip =   1.440000000e+02 >=     tree is empty   0.0% (0; 15315)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   3.6 secs
Memory used: 4.2 Mb (4417371 bytes)
Writing MIP solution to 'glp_10_08.res'...
