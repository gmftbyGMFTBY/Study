# problem F2//Tbar
# first model
# JLB at BIT 2017/04 

param n;
param p1{b in 1..n}; # processing times on M1
param p2{b in 1..n}; # processing times on M2
param d{b in 1..n}; # duedates
param HV; # an upper bound of the makespan

# Zab=0 <=> job a is scheduled before b 
var Z{a in 1..n-1, b in 2..n : a<b} binary ;
# completion time of the job a on M1 and M2
var C1{a in 1..n} >= p1[a] ; 
var C2{a in 1..n} ; 
# tardiness of the job a
var T{a in 1..n} >=0 ; 

minimize tbar: sum{a in 1..n} T[a];

s.t. exclu1{a in 1..n-1, b in 2..n : a<b}:
   p1[b] <= C1[b]-C1[a]+HV*Z[a,b] <= HV-p1[a] ;
s.t. exclu2{a in 1..n-1, b in 2..n : a<b}: 
   p2[b] <= C2[b]-C2[a]+HV*Z[a,b] <= HV-p2[a] ;
s.t. taskop{a in 1..n}: C2[a] >= C1[a] + p2[a] ;
s.t. tardy{a in 1..n}: T[a] + d[a] >= C2[a] ;

end; 
