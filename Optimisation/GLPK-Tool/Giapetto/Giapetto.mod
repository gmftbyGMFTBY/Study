#Giapetto;s problem
#This module to find the optimal solution for maximizing Giapetto's profit

set TOY 'Toys class in the store can produce';
set lala:=TOY union TOY;
set k:=TOY intersection TOY;
set p:=TOY discard TOY;

/* Parameters */
param Finishing_hours {i in TOY};
param Carpentry_hours {i in TOY};
param Demand_toys {i in TOY};
param Profit_toys {i in TOY};

/* Decision variables */
var x {i in TOY} >=0;

/* Objective function */
maximize z: sum{i in TOY} Profit_toys[i]*x[i];

/* Constraints */
subject to Fin_hours : sum{i in TOY} Finishing_hours[i]*x[i] <= 100;
subject to Carp_houtrs : sum{i in TOY} Carpentry_hours[i]*x[i] <= 80;
subject to Dem {i in TOY} : x[i] <= Demand_toys[i];   /* Multiple constraints */

data;
/* data section */

set TOY := soldier train;

param Finishing_hours:=
soldier 2
train 1;

param Carpentry_hours:=
soldier 1
train 1;

param Demand_toys:=
soldier 40
train 6.02E+23;

param Profit_toys:=
soldier 3
train 2;

end;
