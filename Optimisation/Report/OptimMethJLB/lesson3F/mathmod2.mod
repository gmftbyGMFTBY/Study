# problem F2//Tbar
# second model 
# JLB at BIT 2017/04 

param n;
param p1{b in 1..n}; # processing times on M1
param p2{b in 1..n}; # processing times on M2
param d{b in 1..n}; # duedates
param HV; # not necessary here but we use the same data files

# Xab=1 <=> b is the ath job 
var X{a in 1..n, b in 1..n} binary ;
# finishing date of the a^th job on M1 and M2
var F1{a in 1..n} ; 
var F2{a in 1..n} ; 
# tardiness of the a^th job
var G{a in 1..n} >=0 ; 

minimize tbar: sum{a in 1..n} G[a];

s.t. matrow{a in 1..n}: sum{b in 1..n} X[a,b] = 1;
s.t. matcol{b in 1..n}: sum{a in 1..n} X[a,b] = 1;
s.t. f11: F1[1] = sum{b in 1..n} p1[b]*X[1,b];
s.t. f21: F2[1] = sum{b in 1..n} (p1[b]+p2[b])*X[1,b];
s.t. suc1{a in 2..n}: F1[a] >= F1[a-1] + sum{b in 1..n} p1[b]*X[a,b];
s.t. suc2{a in 2..n}: F2[a] >= F2[a-1] + sum{b in 1..n} p2[b]*X[a,b];
s.t. taskop{a in 2..n}: F2[a] >= F1[a] + sum{b in 1..n} p2[b]*X[a,b];
s.t. tardy{a in 1..n}: G[a] + sum{b in 1..n} d[b]*X[a,b] >= F2[a];

end; 
