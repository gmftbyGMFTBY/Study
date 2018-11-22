GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_19.dat -o glp_10_19.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_19.dat...
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
GM: min|aij| =  6.547e-01  max|aij| =  1.528e+00  ratio =  2.333e+00
EQ: min|aij| =  4.286e-01  max|aij| =  1.000e+00  ratio =  2.333e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.219e+00  ratio =  4.875e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   1.755000000e+03 inf =   1.600e+01 (1)
     18: obj =   9.015306122e+01 inf =   0.000e+00 (0)
*    23: obj =  -5.329070518e-15 inf =   2.220e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    23: mip =     not found yet >=              -inf        (1; 0)
+   253: >>>>>   2.170000000e+02 >=   1.100000000e+01  94.9% (56; 1)
+   825: >>>>>   1.860000000e+02 >=   1.500000000e+01  91.9% (172; 8)
+ 10175: >>>>>   1.640000000e+02 >=   4.600000000e+01  72.0% (1646; 197)
+ 59618: >>>>>   1.630000000e+02 >=   9.140000000e+01  43.9% (6714; 2139)
+ 96340: >>>>>   1.600000000e+02 >=   1.140000000e+02  28.8% (8098; 4864)
+154644: >>>>>   1.590000000e+02 >=   1.568333333e+02   1.4% (861; 24171)
+156046: mip =   1.590000000e+02 >=     tree is empty   0.0% (0; 30143)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   9.5 secs
Memory used: 8.3 Mb (8725723 bytes)
Writing MIP solution to 'glp_10_19.res'...
