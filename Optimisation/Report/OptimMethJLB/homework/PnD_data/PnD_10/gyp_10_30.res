GLPSOL: GLPK LP/MIP Solver, v4.61
Parameter(s) specified in the command line:
 -m picdel.mod -d glp_10_30.dat -o glp_10_30.res
Reading model section from picdel.mod...
20 lines were read
Reading data section from glp_10_30.dat...
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
 A: min|aij| =  1.000e+00  max|aij| =  4.300e+01  ratio =  4.300e+01
GM: min|aij| =  5.839e-01  max|aij| =  1.712e+00  ratio =  2.933e+00
EQ: min|aij| =  3.410e-01  max|aij| =  1.000e+00  ratio =  2.933e+00
2N: min|aij| =  3.125e-01  max|aij| =  1.344e+00  ratio =  4.300e+00
Constructing initial basis...
Size of triangular part is 28
Solving LP relaxation...
GLPK Simplex Optimizer, v4.61
29 rows, 108 columns, 306 non-zeros
      0: obj =   5.400000000e+02 inf =   8.000e+00 (1)
     25: obj =   1.695572139e+02 inf =   5.551e-17 (0)
*    34: obj =   5.329070518e-15 inf =   5.551e-17 (0)
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+    34: mip =     not found yet >=              -inf        (1; 0)
+   210: >>>>>   2.450000000e+02 >=   1.200000000e+01  95.1% (44; 0)
+   776: >>>>>   2.170000000e+02 >=   2.000000000e+01  90.8% (175; 6)
+   892: >>>>>   1.650000000e+02 >=   2.200000000e+01  86.7% (201; 14)
+ 24284: >>>>>   1.640000000e+02 >=   7.500000000e+01  54.3% (3619; 627)
+ 55880: >>>>>   1.590000000e+02 >=   1.024137931e+02  35.6% (6480; 2073)
+123957: mip =   1.590000000e+02 >=     tree is empty   0.0% (0; 24721)
INTEGER OPTIMAL SOLUTION FOUND
Time used:   7.3 secs
Memory used: 7.0 Mb (7367145 bytes)
Writing MIP solution to 'glp_10_30.res'...
