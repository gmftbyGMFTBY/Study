# The Mod Solve the problem which is more like the TSP problem
# But which has more constrains

/* Set */
#set place 'Place which the milkman should go $every$ $only once$';

/* Param */
param n;   # The number of the place
param w {i in 1..n};   # The cost of the place

/* var */
var l {i in 0..n} >=0;# 'l[i] means after the place how many milk milkman last' The most important variable
var x {i in 1..n,j in 1..n} binary;

/* Objective function */
minimize ans: sum{i in 0..n} l[i];

/* Constraints */
s.t. x_row{i in 1..n} : sum{j in 1..n} x[i,j] = 1;
s.t. x_col{j in 1..n} : sum{i in 1..n} x[i,j] = 1;
s.t. l_fisrt : l[0] = 0;
s.t. l_end : l[n] = 0;
s.t. l_cons {i in 1..(n-1)} : l[i] = l[i-1] + sum{j in 1..n} x[j,i]*w[j];
s.t. l_neg {i in 2..(n-1)} : l[i] >= 0;

end;
