GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_05.dat -o glp_10_05.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_05.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.200e+01  ratio =  4.200e+01
GM: min|aij| =  5.555e-01  max|aij| =  1.800e+00  ratio =  3.240e+00
EQ: min|aij| =  3.086e-01  max|aij| =  1.000e+00  ratio =  3.240e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.312e+00  ratio =  5.250e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   1.530000000e+03 inf =   1.600e+01 (1)
     22: obj =   4.333333333e+00 inf =   0.000e+00 (0)
*    23: obj =   0.000000000e+00 inf =   0.000e+00 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    23: mip =     not found yet >=              -inf        (1; 0)
+   181: >>>>>   2.330000000e+02 >=   1.000000000e+01  95.7% (34; 0)
+   400: >>>>>   1.970000000e+02 >=   1.600000000e+01  91.9% (56; 5)
+  1129: >>>>>   1.900000000e+02 >=   2.800000000e+01  85.3% (183; 20)
+  1393: >>>>>   1.650000000e+02 >=   3.452380952e+01  79.1% (217; 35)
+  3611: >>>>>   1.540000000e+02 >=   5.200000000e+01  66.2% (517; 121)
+  8317: >>>>>   1.520000000e+02 >=   7.000000000e+01  53.9% (1115; 330)
+ 14993: >>>>>   1.500000000e+02 >=   8.725000000e+01  41.8% (1789; 659)
+ 24966: >>>>>   1.460000000e+02 >=   1.080000000e+02  26.0% (1992; 1564)
+ 35390: mip =   1.460000000e+02 >=     tree is empty   0.0% (0; 7473)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   1.5 secs
Memory used: 2.3 Mb (2419610 bytes)
Writing MIP solution to 'glp_10_05.res'...
