GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_22.dat -o glp_10_22.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_22.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.700e+01  ratio =  4.700e+01
GM: min|aij| =  5.977e-01  max|aij| =  1.673e+00  ratio =  2.799e+00
EQ: min|aij| =  3.573e-01  max|aij| =  1.000e+00  ratio =  2.799e+00
2N: min|aij| =  3.750e-01  max|aij| =  1.469e+00  ratio =  3.917e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   4.050000000e+02 inf =   8.000e+00 (1)
     21: obj =   1.660000000e+02 inf =   1.110e-16 (0)
*    30: obj =   0.000000000e+00 inf =   2.220e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    30: mip =     not found yet >=              -inf        (1; 0)
+   260: >>>>>   2.200000000e+02 >=   6.000000000e+00  97.3% (51; 1)
+  1632: >>>>>   2.110000000e+02 >=   1.700000000e+01  91.9% (320; 21)
+  2425: >>>>>   2.070000000e+02 >=   2.100000000e+01  89.9% (467; 40)
+  4584: >>>>>   1.890000000e+02 >=   3.346808511e+01  82.3% (897; 78)
+  6768: >>>>>   1.880000000e+02 >=   4.400000000e+01  76.6% (1279; 181)
+  6839: >>>>>   1.640000000e+02 >=   4.400000000e+01  73.2% (1295; 188)
+ 12937: >>>>>   1.540000000e+02 >=   5.540740741e+01  64.0% (2213; 463)
+ 94874: mip =   1.540000000e+02 >=   1.190000000e+02  22.7% (7093; 6506)
+136881: mip =   1.540000000e+02 >=     tree is empty   0.0% (0; 28421)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   9.0 secs
Memory used: 7.8 Mb (8131727 bytes)
Writing MIP solution to 'glp_10_22.res'...
