GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_04.dat -o glp_10_04.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_04.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.300e+01  ratio =  4.300e+01
GM: min|aij| =  4.644e-01  max|aij| =  2.153e+00  ratio =  4.637e+00
EQ: min|aij| =  2.157e-01  max|aij| =  1.000e+00  ratio =  4.637e+00
2N: min|aij| =  1.250e-01  max|aij| =  1.125e+00  ratio =  9.000e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -5.850000000e+02 inf =   8.112e+01 (10)
     26: obj =   1.411397320e+02 inf =   7.772e-16 (0)
*    38: obj =   3.552713679e-15 inf =   3.331e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    38: mip =     not found yet >=              -inf        (1; 0)
+   323: >>>>>   1.580000000e+02 >=   4.000000000e+00  97.5% (46; 0)
+  1027: >>>>>   1.400000000e+02 >=   1.800000000e+01  87.1% (142; 9)
+  3571: >>>>>   1.360000000e+02 >=   4.100000000e+01  69.9% (392; 60)
+ 14658: >>>>>   1.350000000e+02 >=   8.000000000e+01  40.7% (1437; 440)
+ 23224: >>>>>   1.310000000e+02 >=   9.500000000e+01  27.5% (1826; 1017)
+ 39020: mip =   1.310000000e+02 >=     tree is empty   0.0% (0; 7035)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   1.5 secs
Memory used: 2.1 Mb (2232159 bytes)
Writing MIP solution to 'glp_10_04.res'...
