GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_21.dat -o glp_10_21.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_21.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  5.300e+01  ratio =  5.300e+01
GM: min|aij| =  6.898e-01  max|aij| =  1.450e+00  ratio =  2.102e+00
EQ: min|aij| =  4.758e-01  max|aij| =  1.000e+00  ratio =  2.102e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.375e+00  ratio =  5.500e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   8.550000000e+02 inf =   1.600e+01 (1)
     20: obj =   9.932544218e+01 inf =   6.661e-16 (0)
*    24: obj =   1.776356839e-15 inf =   2.220e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    24: mip =     not found yet >=              -inf        (1; 0)
+   212: >>>>>   3.290000000e+02 >=   7.105427358e-15 100.0% (32; 1)
+   283: >>>>>   2.270000000e+02 >=   1.300000000e+01  94.3% (42; 6)
+ 10645: >>>>>   2.250000000e+02 >=   1.080000000e+02  52.0% (1682; 291)
+ 10815: >>>>>   2.040000000e+02 >=   1.080793651e+02  47.0% (1683; 330)
+ 57187: mip =   2.040000000e+02 >=     tree is empty   0.0% (0; 10893)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   2.5 secs
Memory used: 3.1 Mb (3291793 bytes)
Writing MIP solution to 'glp_10_21.res'...
