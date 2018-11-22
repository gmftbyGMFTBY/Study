GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_14.dat -o glp_10_14.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_14.dat...
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
GM: min|aij| =  3.928e-01  max|aij| =  2.546e+00  ratio =  6.481e+00
EQ: min|aij| =  1.543e-01  max|aij| =  1.000e+00  ratio =  6.481e+00
2N: min|aij| =  1.250e-01  max|aij| =  1.312e+00  ratio =  1.050e+01
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -1.035000000e+03 inf =   7.269e+01 (10)
     22: obj =   2.628569820e+02 inf =   5.551e-17 (0)
*    34: obj =  -8.881784197e-16 inf =   0.000e+00 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    34: mip =     not found yet >=              -inf        (1; 0)
+   310: >>>>>   2.390000000e+02 >=   1.000000000e+01  95.8% (48; 1)
+   745: >>>>>   1.690000000e+02 >=   1.200000000e+01  92.9% (126; 5)
+  1841: >>>>>   1.470000000e+02 >=   1.600000000e+01  89.1% (299; 16)
+  5867: >>>>>   1.410000000e+02 >=   2.300000000e+01  83.7% (954; 99)
+  9157: >>>>>   1.210000000e+02 >=   2.800000000e+01  76.9% (1468; 197)
+ 13652: >>>>>   1.090000000e+02 >=   3.441509434e+01  68.4% (2014; 512)
+101856: mip =   1.090000000e+02 >=   8.100000000e+01  25.7% (7303; 6521)
+151978: mip =   1.090000000e+02 >=     tree is empty   0.0% (0; 29785)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   9.4 secs
Memory used: 8.0 Mb (8420333 bytes)
Writing MIP solution to 'glp_10_14.res'...
