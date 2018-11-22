GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_25.dat -o glp_10_25.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_25.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.000e+01  ratio =  4.000e+01
GM: min|aij| =  6.687e-01  max|aij| =  1.495e+00  ratio =  2.236e+00
EQ: min|aij| =  4.472e-01  max|aij| =  1.000e+00  ratio =  2.236e+00
2N: min|aij| =  5.000e-01  max|aij| =  1.562e+00  ratio =  3.125e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   1.080000000e+03 inf =   1.600e+01 (1)
     23: obj =   8.800000000e+01 inf =   0.000e+00 (0)
*    37: obj =   0.000000000e+00 inf =   2.220e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    37: mip =     not found yet >=              -inf        (1; 0)
+   413: >>>>>   1.890000000e+02 >=   1.100000000e+01  94.2% (75; 2)
+  1005: >>>>>   1.810000000e+02 >=   1.200000000e+01  93.4% (192; 8)
+  1313: >>>>>   1.790000000e+02 >=   1.200000000e+01  93.3% (267; 12)
+  2527: >>>>>   1.650000000e+02 >=   2.000000000e+01  87.9% (490; 28)
+  3488: >>>>>   1.590000000e+02 >=   2.300000000e+01  85.5% (634; 67)
+  4558: >>>>>   1.450000000e+02 >=   2.500000000e+01  82.8% (792; 100)
+ 20163: >>>>>   1.430000000e+02 >=   5.700000000e+01  60.1% (3031; 552)
+ 28423: >>>>>   1.360000000e+02 >=   6.400000000e+01  52.9% (4035; 880)
+ 36931: >>>>>   1.330000000e+02 >=   7.100000000e+01  46.6% (4663; 1560)
+ 39522: >>>>>   1.310000000e+02 >=   7.289473684e+01  44.4% (4697; 1956)
+121834: mip =   1.310000000e+02 >=   1.290000000e+02   1.5% (449; 20910)
+122937: mip =   1.310000000e+02 >=     tree is empty   0.0% (0; 24361)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   6.9 secs
Memory used: 6.6 Mb (6886047 bytes)
Writing MIP solution to 'glp_10_25.res'...
