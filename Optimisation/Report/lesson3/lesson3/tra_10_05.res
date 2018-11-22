GLPSOL: GLPK LP/MIP Solver, v4.60
Parameter(s) specified in the command line:
 -m mathmod1.mod -d glp_10_05.dat -o glp_10_05.res
Reading model section from mathmod1.mod...
28 lines were read
Reading data section from glp_10_05.dat...
7 lines were read
Generating tbar...
Generating exclu1...
Generating exclu2...
Generating taskop...
Generating tardy...
Model has been successfully generated
GLPK Integer Optimizer, v4.60
111 rows, 75 columns, 320 non-zeros
45 integer variables, all of which are binary
Preprocessing...
109 rows, 74 columns, 308 non-zeros
45 integer variables, all of which are binary
Scaling...
 A: min|aij| =  1.000e+00  max|aij| =  2.000e+03  ratio =  2.000e+03
GM: min|aij| =  1.000e+00  max|aij| =  1.000e+00  ratio =  1.000e+00
EQ: min|aij| =  1.000e+00  max|aij| =  1.000e+00  ratio =  1.000e+00
2N: min|aij| =  9.766e-01  max|aij| =  1.000e+00  ratio =  1.024e+00
Constructing initial basis...
Size of triangular part is 109
Solving LP relaxation...
GLPK Simplex Optimizer, v4.60
109 rows, 74 columns, 308 non-zeros
      0: obj =   1.400000000e+01 inf =   4.666e+03 (81)
     84: obj =   1.810000000e+02 inf =   0.000e+00 (0)
*   101: obj =   1.400000000e+01 inf =   0.000e+00 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+   101: mip =     not found yet >=              -inf        (1; 0)
+  1985: >>>>>   1.185000000e+03 >=   1.810000000e+02  84.7% (222; 14)
+  2551: >>>>>   9.750000000e+02 >=   2.060000000e+02  78.9% (267; 56)
+  2674: >>>>>   8.770000000e+02 >=   2.060000000e+02  76.5% (250; 112)
+  3355: >>>>>   8.550000000e+02 >=   2.060000000e+02  75.9% (305; 156)
+  4721: >>>>>   8.410000000e+02 >=   2.260000000e+02  73.1% (451; 206)
+  4935: >>>>>   8.030000000e+02 >=   2.270000000e+02  71.7% (466; 235)
+  7750: >>>>>   8.000000000e+02 >=   2.470000000e+02  69.1% (724; 348)
+ 17105: >>>>>   7.670000000e+02 >=   2.890000000e+02  62.3% (1676; 685)
+ 28995: >>>>>   7.350000000e+02 >=   3.150000000e+02  57.1% (2716; 1319)
+ 65672: >>>>>   7.170000000e+02 >=   3.920000000e+02  45.3% (5656; 3588)
+ 99174: >>>>>   6.940000000e+02 >=   4.350000000e+02  37.3% (8010; 6183)
+133320: >>>>>   6.550000000e+02 >=   4.720000000e+02  27.9% (9746; 10141)
+180876: mip =   6.550000000e+02 >=   5.370000000e+02  18.0% (9218; 22714)
+212013: mip =   6.550000000e+02 >=   5.880000000e+02  10.2% (7066; 36236)
+217658: >>>>>   6.510000000e+02 >=   6.050000000e+02   7.1% (5516; 41904)
+217672: >>>>>   6.490000000e+02 >=   6.050000000e+02   6.8% (5109; 43110)
+222847: mip =   6.490000000e+02 >=     tree is empty   0.0% (0; 68099)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   18.6 secs
Memory used: 28.4 Mb (29773857 bytes)
Writing MIP solution to 'glp_10_05.res'...
