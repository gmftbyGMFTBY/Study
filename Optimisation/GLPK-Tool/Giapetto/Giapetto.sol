Problem:    Giapetto
Rows:       5
Columns:    2
Non-zeros:  8
Status:     OPTIMAL
Objective:  z = 180 (MAXimum)

   No.   Row name   St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 z            B            180                             
     2 Fin_hours    NU           100                         100             1 
     3 Carp_houtrs  NU            80                          80             1 
     4 Dem[soldier] B             20                          40 
     5 Dem[train]   B             60                    6.02e+23 

   No. Column name  St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 x[soldier]   B             20             0               
     2 x[train]     B             60             0               

Karush-Kuhn-Tucker optimality conditions:

KKT.PE: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.PB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.DE: max.abs.err = 0.00e+00 on column 0
        max.rel.err = 0.00e+00 on column 0
        High quality

KKT.DB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

End of output
