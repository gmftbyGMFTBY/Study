GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_27.dat -o glp_10_27.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_27.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.500e+01  ratio =  4.500e+01
GM: min|aij| =  5.081e-01  max|aij| =  1.968e+00  ratio =  3.873e+00
EQ: min|aij| =  2.582e-01  max|aij| =  1.000e+00  ratio =  3.873e+00
2N: min|aij| =  1.875e-01  max|aij| =  1.406e+00  ratio =  7.500e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -4.950000000e+02 inf =   3.894e+01 (10)
     26: obj =   7.620689655e+00 inf =   5.551e-17 (0)
*    27: obj =   8.881784197e-16 inf =   0.000e+00 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    27: mip =     not found yet >=              -inf        (1; 0)
+   231: >>>>>   1.780000000e+02 >=   2.000000000e+01  88.8% (42; 0)
+  1402: >>>>>   1.730000000e+02 >=   3.800000000e+01  78.0% (237; 14)
+  1567: >>>>>   1.640000000e+02 >=   3.800000000e+01  76.8% (249; 21)
+ 16838: >>>>>   1.620000000e+02 >=   7.800000000e+01  51.9% (2417; 394)
+ 19021: >>>>>   1.540000000e+02 >=   8.100000000e+01  47.4% (2619; 527)
+ 19411: >>>>>   1.470000000e+02 >=   8.166666667e+01  44.4% (2479; 869)
+ 80485: mip =   1.470000000e+02 >=     tree is empty   0.0% (0; 15603)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   4.2 secs
Memory used: 4.6 Mb (4838259 bytes)
Writing MIP solution to 'glp_10_27.res'...
