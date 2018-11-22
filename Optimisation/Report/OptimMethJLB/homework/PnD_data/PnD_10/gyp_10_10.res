GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_10.dat -o glp_10_10.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_10.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  5.200e+01  ratio =  5.200e+01
GM: min|aij| =  7.071e-01  max|aij| =  1.414e+00  ratio =  2.000e+00
EQ: min|aij| =  5.000e-01  max|aij| =  1.000e+00  ratio =  2.000e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.406e+00  ratio =  5.625e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -2.340000000e+03 inf =   1.622e+02 (10)
     24: obj =   7.150000000e+02 inf =   8.882e-16 (0)
*    43: obj =  -1.776356839e-15 inf =   3.331e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    43: mip =     not found yet >=              -inf        (1; 0)
+   189: >>>>>   3.070000000e+02 >=   2.600000000e+01  91.5% (32; 0)
+  1726: >>>>>   2.900000000e+02 >=   5.200000000e+01  82.1% (398; 24)
+  1815: >>>>>   2.790000000e+02 >=   5.200000000e+01  81.4% (415; 27)
+  2246: >>>>>   2.360000000e+02 >=   5.400000000e+01  77.1% (513; 42)
+  3126: >>>>>   1.940000000e+02 >=   6.400000000e+01  67.0% (653; 114)
+  6419: >>>>>   1.830000000e+02 >=   8.000000000e+01  56.3% (1167; 291)
+ 38057: >>>>>   1.810000000e+02 >=   1.280000000e+02  29.3% (4434; 1816)
+ 85131: mip =   1.810000000e+02 >=     tree is empty   0.0% (0; 17535)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   4.4 secs
Memory used: 4.9 Mb (5103489 bytes)
Writing MIP solution to 'glp_10_10.res'...
