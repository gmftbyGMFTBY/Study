GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_15.dat -o glp_10_15.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_15.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  5.000e+01  ratio =  5.000e+01
GM: min|aij| =  6.514e-01  max|aij| =  1.535e+00  ratio =  2.357e+00
EQ: min|aij| =  4.243e-01  max|aij| =  1.000e+00  ratio =  2.357e+00
2N: min|aij| =  2.500e-01  max|aij| =  1.531e+00  ratio =  6.125e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   4.050000000e+02 inf =   8.000e+00 (1)
     21: obj =   2.233428571e+02 inf =   2.220e-16 (0)
*    37: obj =   0.000000000e+00 inf =   0.000e+00 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    37: mip =     not found yet >=              -inf        (1; 0)
+   415: >>>>>   3.780000000e+02 >=   2.100000000e+01  94.4% (76; 2)
+   595: >>>>>   2.730000000e+02 >=   2.600000000e+01  90.5% (112; 5)
+   954: >>>>>   2.590000000e+02 >=   3.000000000e+01  88.4% (179; 9)
+  1121: >>>>>   2.510000000e+02 >=   3.100000000e+01  87.6% (208; 12)
+  1378: >>>>>   2.310000000e+02 >=   3.500000000e+01  84.8% (255; 15)
+  1975: >>>>>   2.150000000e+02 >=   3.500000000e+01  83.7% (367; 34)
+  3822: >>>>>   1.950000000e+02 >=   5.200000000e+01  73.3% (688; 75)
+ 20252: >>>>>   1.910000000e+02 >=   9.500000000e+01  50.3% (2943; 596)
+ 31038: >>>>>   1.840000000e+02 >=   1.080000000e+02  41.3% (4051; 1147)
+ 33412: >>>>>   1.820000000e+02 >=   1.109473442e+02  39.0% (3964; 1674)
+ 69337: >>>>>   1.810000000e+02 >=   1.444857143e+02  20.2% (4833; 4576)
+102314: mip =   1.810000000e+02 >=     tree is empty   0.0% (0; 19521)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   5.1 secs
Memory used: 5.5 Mb (5783837 bytes)
Writing MIP solution to 'glp_10_15.res'...
