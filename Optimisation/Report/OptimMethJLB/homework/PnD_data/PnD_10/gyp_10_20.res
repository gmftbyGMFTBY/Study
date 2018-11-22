GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_20.dat -o glp_10_20.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_20.dat...
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
GM: min|aij| =  6.212e-01  max|aij| =  1.610e+00  ratio =  2.591e+00
EQ: min|aij| =  3.859e-01  max|aij| =  1.000e+00  ratio =  2.591e+00
2N: min|aij| =  4.375e-01  max|aij| =  1.469e+00  ratio =  3.357e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   3.150000000e+02 inf =   8.000e+00 (1)
     23: obj =   9.400000000e+01 inf =   5.551e-16 (0)
*    31: obj =   0.000000000e+00 inf =   6.661e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    31: mip =     not found yet >=              -inf        (1; 0)
+   266: >>>>>   4.060000000e+02 >=   1.300000000e+01  96.8% (48; 0)
+   734: >>>>>   2.130000000e+02 >=   3.000000000e+01  85.9% (154; 5)
+  1447: >>>>>   1.990000000e+02 >=   3.700000000e+01  81.4% (275; 40)
+  5326: >>>>>   1.950000000e+02 >=   6.100000000e+01  68.7% (927; 125)
+  7964: >>>>>   1.870000000e+02 >=   7.145454545e+01  61.8% (1384; 193)
+  9382: >>>>>   1.850000000e+02 >=   7.500000000e+01  59.5% (1580; 320)
+  9856: >>>>>   1.750000000e+02 >=   7.640000000e+01  56.3% (1621; 368)
+ 48347: >>>>>   1.710000000e+02 >=   1.250000000e+02  26.9% (4674; 2344)
+ 74224: >>>>>   1.690000000e+02 >=   1.500000000e+02  11.2% (3026; 6475)
+ 85912: mip =   1.690000000e+02 >=     tree is empty   0.0% (0; 16763)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   4.3 secs
Memory used: 4.8 Mb (5070785 bytes)
Writing MIP solution to 'glp_10_20.res'...
