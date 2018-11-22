GLPSOL: GLPK LP/MIP Solver, v4.61
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
GLPK Integer Optimizer, v4.61
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
GLPK Simplex Optimizer, v4.61
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
+ 80858: mip =   1.200000000e+03 >=   7.850913318e+02  34.6% (7004; 1640)
+ 84175: >>>>>   1.190000000e+03 >=   7.880626536e+02  33.8% (7239; 1676)
+141369: mip =   1.190000000e+03 >=   8.030000000e+02  32.5% (11582; 2528)
+197806: mip =   1.190000000e+03 >=   8.170000000e+02  31.3% (15683; 3125)
+251979: mip =   1.190000000e+03 >=   8.274000000e+02  30.5% (19618; 3705)
+303843: mip =   1.190000000e+03 >=   8.350000000e+02  29.8% (22981; 4313)
+350702: mip =   1.190000000e+03 >=   8.420000000e+02  29.2% (26214; 4886)
+397028: mip =   1.190000000e+03 >=   8.480000000e+02  28.7% (29267; 5428)
+443697: mip =   1.190000000e+03 >=   8.524736162e+02  28.4% (32239; 5989)
+485703: mip =   1.190000000e+03 >=   8.591387888e+02  27.8% (34997; 6566)
+526551: mip =   1.190000000e+03 >=   8.650000000e+02  27.3% (37365; 7162)
+564884: mip =   1.190000000e+03 >=   8.700000000e+02  26.9% (39328; 7765)
Time used: 60.0 secs.  Memory used: 47.6 Mb.
+601966: mip =   1.190000000e+03 >=   8.750000000e+02  26.5% (41466; 8312)
+638339: mip =   1.190000000e+03 >=   8.799636189e+02  26.1% (43498; 8829)
+670944: mip =   1.190000000e+03 >=   8.837329411e+02  25.7% (45578; 9303)
+700027: mip =   1.190000000e+03 >=   8.870000000e+02  25.5% (47251; 9755)
+731388: mip =   1.190000000e+03 >=   8.900000000e+02  25.2% (48831; 10254)
+732703: >>>>>   1.122000000e+03 >=   8.901575186e+02  20.7% (48933; 10270)
+770223: mip =   1.122000000e+03 >=   8.940000000e+02  20.3% (36496; 33344)
+807289: mip =   1.122000000e+03 >=   8.973380282e+02  20.0% (37864; 34061)
+840319: mip =   1.122000000e+03 >=   9.014195860e+02  19.7% (39052; 34749)
+871861: mip =   1.122000000e+03 >=   9.054319451e+02  19.3% (40161; 35403)
+904229: mip =   1.122000000e+03 >=   9.087299166e+02  19.0% (41231; 36091)
+937107: mip =   1.122000000e+03 >=   9.114057733e+02  18.8% (42380; 36711)
+966960: mip =   1.122000000e+03 >=   9.150000000e+02  18.4% (43375; 37363)
Time used: 120.0 secs.  Memory used: 60.7 Mb.
+979363: mip =   1.122000000e+03 >=   9.164886886e+02  18.3% (43821; 37642)
TIME LIMIT EXCEEDED; SEARCH TERMINATED
Time used:   120.0 secs
Memory used: 60.7 Mb (63668319 bytes)
Writing MIP solution to 'gl2_15_01.res'...
