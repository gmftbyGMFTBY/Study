GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_03.dat -o glp_10_03.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_03.dat...
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
GM: min|aij| =  4.495e-01  max|aij| =  2.225e+00  ratio =  4.950e+00
EQ: min|aij| =  2.020e-01  max|aij| =  1.000e+00  ratio =  4.950e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.531e+00  ratio =  6.125e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   1.980000000e+03 inf =   1.600e+01 (1)
     23: obj =   9.000000000e+01 inf =   2.776e-17 (0)
*    35: obj =   3.552713679e-15 inf =   1.110e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    35: mip =     not found yet >=              -inf        (1; 0)
+   310: >>>>>   2.640000000e+02 >=   2.000000000e+00  99.2% (50; 0)
+  1477: >>>>>   2.490000000e+02 >=   9.000000000e+00  96.4% (267; 10)
+  1840: >>>>>   2.290000000e+02 >=   1.200000000e+01  94.8% (326; 15)
+  2232: >>>>>   1.700000000e+02 >=   1.400000000e+01  91.8% (389; 28)
+  2443: >>>>>   1.560000000e+02 >=   1.400000000e+01  91.0% (406; 70)
+  3766: >>>>>   1.400000000e+02 >=   2.900000000e+01  79.3% (583; 116)
+ 27303: >>>>>   1.380000000e+02 >=   6.700000000e+01  51.4% (3269; 867)
+104757: mip =   1.380000000e+02 >=     tree is empty   0.0% (0; 19151)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   5.5 secs
Memory used: 5.5 Mb (5811349 bytes)
Writing MIP solution to 'glp_10_03.res'...
