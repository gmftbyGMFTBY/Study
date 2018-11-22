GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_11.dat -o glp_10_11.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_11.dat...
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
GM: min|aij| =  5.742e-01  max|aij| =  1.742e+00  ratio =  3.033e+00
EQ: min|aij| =  3.297e-01  max|aij| =  1.000e+00  ratio =  3.033e+00
2N: min|aij| =  3.125e-01  max|aij| =  1.438e+00  ratio =  4.600e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =  -1.620000000e+03 inf =   1.172e+02 (10)
     25: obj =   2.622513369e+02 inf =   2.220e-16 (0)
*    38: obj =   0.000000000e+00 inf =   2.220e-16 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    38: mip =     not found yet >=              -inf        (1; 0)
+   592: >>>>>   4.380000000e+02 >=   1.500000000e+01  96.6% (107; 5)
+   836: >>>>>   3.640000000e+02 >=   1.500000000e+01  95.9% (157; 8)
+  1199: >>>>>   2.020000000e+02 >=   2.500000000e+01  87.6% (233; 11)
+  2496: >>>>>   1.890000000e+02 >=   3.300000000e+01  82.5% (477; 66)
+  7346: >>>>>   1.840000000e+02 >=   5.000000000e+01  72.8% (1323; 194)
+ 13530: >>>>>   1.810000000e+02 >=   6.300000000e+01  65.2% (2201; 376)
+ 14432: >>>>>   1.750000000e+02 >=   6.400000000e+01  63.4% (2316; 433)
+ 93963: >>>>>   1.740000000e+02 >=   1.170000000e+02  32.8% (9960; 4408)
+144221: >>>>>   1.730000000e+02 >=   1.410000000e+02  18.5% (8966; 10587)
+149357: >>>>>   1.700000000e+02 >=   1.435000000e+02  15.6% (8267; 12018)
+183747: mip =   1.700000000e+02 >=     tree is empty   0.0% (0; 38057)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   12.1 secs
Memory used: 10.7 Mb (11221767 bytes)
Writing MIP solution to 'glp_10_11.res'...
