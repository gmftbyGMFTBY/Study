GLPSOL: GLPK LP/MIP Solver, v4.60
Parameter(s) specified in the command line:
 -m mathmod2.mod -d glp_15_01.dat -o gl2_15_01.res --tmlim 120
Reading model section from mathmod2.mod...
30 lines were read
Reading data section from glp_15_01.dat...
6 lines were read
Generating tbar...
Generating matrow...
Generating matcol...
Generating f11...
Generating f21...
Generating suc1...
Generating suc2...
Generating taskop...
Generating tardy...
Model has been successfully generated
GLPK Integer Optimizer, v4.60
90 rows, 270 columns, 1466 non-zeros
225 integer variables, all of which are binary
Preprocessing...
89 rows, 270 columns, 1451 non-zeros
225 integer variables, all of which are binary
Scaling...
 A: min|aij| =  1.000e+00  max|aij| =  8.700e+02  ratio =  8.700e+02
GM: min|aij| =  2.808e-01  max|aij| =  3.561e+00  ratio =  1.268e+01
EQ: min|aij| =  7.885e-02  max|aij| =  1.000e+00  ratio =  1.268e+01
2N: min|aij| =  4.688e-02  max|aij| =  1.195e+00  ratio =  2.550e+01
Constructing initial basis...
Size of triangular part is 88
Solving LP relaxation...
GLPK Simplex Optimizer, v4.60
89 rows, 270 columns, 1451 non-zeros
      0: obj =   0.000000000e+00 inf =   2.345e+02 (41)
    114: obj =   1.732164855e+03 inf =   5.969e-14 (0)
*   197: obj =   5.202199780e+02 inf =   4.441e-15 (0) 1
OPTIMAL LP SOLUTION FOUND
Integer optimization begins...
+   197: mip =     not found yet >=              -inf        (1; 0)
+   531: >>>>>   1.886000000e+03 >=   5.642829389e+02  70.1% (46; 0)
+  1905: >>>>>   1.679000000e+03 >=   5.758081605e+02  65.7% (254; 9)
+  2064: >>>>>   1.411000000e+03 >=   5.771368799e+02  59.1% (251; 61)
+  2208: >>>>>   1.396000000e+03 >=   5.887274419e+02  57.8% (230; 120)
+ 11207: >>>>>   1.343000000e+03 >=   6.563384224e+02  51.1% (1172; 163)
+ 16225: >>>>>   1.237000000e+03 >=   6.817386195e+02  44.9% (1633; 351)
+ 25160: >>>>>   1.200000000e+03 >=   7.236102227e+02  39.7% (2253; 848)
+ 80609: mip =   1.200000000e+03 >=   7.848018135e+02  34.6% (6979; 1638)
+ 84175: >>>>>   1.190000000e+03 >=   7.880626536e+02  33.8% (7239; 1676)
+141014: mip =   1.190000000e+03 >=   8.030000000e+02  32.5% (11570; 2523)
+196478: mip =   1.190000000e+03 >=   8.170000000e+02  31.3% (15613; 3111)
+252197: mip =   1.190000000e+03 >=   8.274000747e+02  30.5% (19643; 3706)
+305631: mip =   1.190000000e+03 >=   8.350000000e+02  29.8% (23074; 4340)
+355005: mip =   1.190000000e+03 >=   8.420000000e+02  29.2% (26490; 4933)
+399951: mip =   1.190000000e+03 >=   8.480000000e+02  28.7% (29454; 5456)
+444053: mip =   1.190000000e+03 >=   8.526507547e+02  28.3% (32264; 5994)
+484680: mip =   1.190000000e+03 >=   8.590000000e+02  27.8% (34940; 6555)
+525817: mip =   1.190000000e+03 >=   8.650000000e+02  27.3% (37328; 7151)
+563577: mip =   1.190000000e+03 >=   8.700000000e+02  26.9% (39253; 7750)
Time used: 60.0 secs.  Memory used: 47.4 Mb.
+600293: mip =   1.190000000e+03 >=   8.750000000e+02  26.5% (41379; 8282)
+636031: mip =   1.190000000e+03 >=   8.790339938e+02  26.1% (43396; 8791)
+669602: mip =   1.190000000e+03 >=   8.831818182e+02  25.8% (45497; 9280)
+701051: mip =   1.190000000e+03 >=   8.870000000e+02  25.5% (47302; 9770)
+732448: mip =   1.190000000e+03 >=   8.900542882e+02  25.2% (48909; 10265)
+732703: >>>>>   1.122000000e+03 >=   8.901575186e+02  20.7% (48933; 10270)
+767105: mip =   1.122000000e+03 >=   8.936698558e+02  20.4% (36358; 33287)
+800635: mip =   1.122000000e+03 >=   8.967623300e+02  20.1% (37575; 33932)
+831891: mip =   1.122000000e+03 >=   9.010000000e+02  19.7% (38755; 34606)
+864947: mip =   1.122000000e+03 >=   9.047668734e+02  19.4% (39914; 35277)
+895969: mip =   1.122000000e+03 >=   9.080000000e+02  19.1% (40943; 35940)
+927391: mip =   1.122000000e+03 >=   9.110000000e+02  18.8% (42041; 36564)
+956387: mip =   1.122000000e+03 >=   9.136291821e+02  18.6% (42980; 37143)
+969064: mip =   1.122000000e+03 >=   9.151888124e+02  18.4% (43483; 37397)
TIME LIMIT EXCEEDED; SEARCH TERMINATED
Time used:   120.0 secs
Memory used: 60.2 Mb (63156211 bytes)
Writing MIP solution to 'gl2_15_01.res'...
