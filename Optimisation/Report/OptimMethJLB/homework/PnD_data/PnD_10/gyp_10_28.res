GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_28.dat -o glp_10_28.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_28.dat...
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
GM: min|aij| =  7.291e-01  max|aij| =  1.372e+00  ratio =  1.881e+00
EQ: min|aij| =  5.316e-01  max|aij| =  1.000e+00  ratio =  1.881e+00
2N: min|aij| =  4.062e-01  max|aij| =  1.031e+00  ratio =  2.538e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   1.890000000e+03 inf =   1.600e+01 (1)
     23: obj =   2.230000000e+02 inf =   0.000e+00 (0)
*    48: obj =   3.197442311e-14 inf =   4.441e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    48: mip =     not found yet >=              -inf        (1; 0)
+   217: >>>>>   3.750000000e+02 >=   1.700000000e+01  95.5% (47; 0)
+   358: >>>>>   2.570000000e+02 >=   1.700000000e+01  93.4% (77; 3)
+  1835: >>>>>   2.450000000e+02 >=   3.500000000e+01  85.7% (401; 23)
+  2238: >>>>>   2.380000000e+02 >=   3.700000000e+01  84.5% (471; 33)
+  2843: >>>>>   2.300000000e+02 >=   4.200000000e+01  81.7% (587; 43)
+  7300: >>>>>   2.180000000e+02 >=   5.200000000e+01  76.1% (1443; 124)
+ 12227: >>>>>   2.110000000e+02 >=   6.700000000e+01  68.2% (2310; 252)
+ 13397: >>>>>   2.090000000e+02 >=   6.800000000e+01  67.5% (2498; 344)
+ 14714: >>>>>   1.810000000e+02 >=   7.000000000e+01  61.3% (2664; 397)
+ 64748: >>>>>   1.750000000e+02 >=   1.110000000e+02  36.6% (7915; 2839)
+135964: mip =   1.750000000e+02 >=   1.500000000e+02  14.3% (6064; 11934)
+163874: mip =   1.750000000e+02 >=     tree is empty   0.0% (0; 31845)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   10.4 secs
Memory used: 8.7 Mb (9174231 bytes)
Writing MIP solution to 'glp_10_28.res'...
