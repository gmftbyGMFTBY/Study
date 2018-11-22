GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_02.dat -o glp_10_02.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_02.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.400e+01  ratio =  4.400e+01
GM: min|aij| =  5.806e-01  max|aij| =  1.722e+00  ratio =  2.966e+00
EQ: min|aij| =  3.371e-01  max|aij| =  1.000e+00  ratio =  2.966e+00
2N: min|aij| =  3.125e-01  max|aij| =  1.375e+00  ratio =  4.400e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -1.530000000e+03 inf =   1.116e+02 (10)
     25: obj =   1.730344828e+02 inf =   1.110e-16 (0)
*    37: obj =   1.287858709e-14 inf =   1.110e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    37: mip =     not found yet >=              -inf        (1; 0)
+   139: >>>>>   1.790000000e+02 >=   1.332267630e-14 100.0% (34; 0)
+  1868: >>>>>   1.540000000e+02 >=   1.200000000e+01  92.2% (392; 32)
+ 29156: >>>>>   1.510000000e+02 >=   6.200000000e+01  58.9% (4389; 760)
+114811: mip =   1.510000000e+02 >=   1.041568627e+02  31.0% (10013; 5781)
+173334: mip =   1.510000000e+02 >=   1.360000000e+02   9.9% (4793; 18010)
+188260: mip =   1.510000000e+02 >=     tree is empty   0.0% (0; 36435)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   12.6 secs
Memory used: 10.4 Mb (10892779 bytes)
Writing MIP solution to 'glp_10_02.res'...
