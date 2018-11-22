GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_09.dat -o glp_10_09.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_09.dat...
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
      0: obj =  -1.440000000e+03 inf =   9.800e+01 (10)
     22: obj =   1.221034483e+02 inf =   2.776e-16 (0)
*    33: obj =  -5.329070518e-15 inf =   8.327e-17 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    33: mip =     not found yet >=              -inf        (1; 0)
+   371: >>>>>   1.680000000e+02 >=   6.000000000e+00  96.4% (51; 1)
+   959: >>>>>   1.460000000e+02 >=   2.800000000e+01  80.8% (145; 12)
+  2842: >>>>>   1.400000000e+02 >=   4.687755102e+01  66.5% (391; 61)
+  2927: >>>>>   1.300000000e+02 >=   4.700000000e+01  63.8% (392; 90)
+  3636: >>>>>   1.240000000e+02 >=   5.200000000e+01  58.1% (439; 155)
+  5073: >>>>>   1.220000000e+02 >=   5.939386563e+01  51.3% (561; 230)
+ 25364: mip =   1.220000000e+02 >=     tree is empty   0.0% (0; 4897)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   1.0 secs
Memory used: 1.6 Mb (1670363 bytes)
Writing MIP solution to 'glp_10_09.res'...
