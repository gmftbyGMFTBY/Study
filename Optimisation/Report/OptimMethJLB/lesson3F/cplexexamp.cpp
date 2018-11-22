//
//  cplexexamp.cpp
//  
//  JLB at BIT on 2017/05
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>

#include "instance.h"
#include <ilcplex/ilocplex.h>

#define EQUAL_TO_1( ilocplex, var ) ((ilocplex).getValue((var)) > 0.5)   // kai
#define EQUAL_TO_0( ilocplex, var ) ((ilocplex).getValue((var)) < 0.5)   // kai
#define EQUAL_TO( ilocplex, var, val ) (((ilocplex).getValue((var)) - (val)) < 0.5) && (-((ilocplex).getValue((var)) + (val)) < 0.5)   // kai

#define DATADIR "/Users/jean-louisbouquard/Enseignement/BIT_teaching/optimization/opti_pgm/F2data/F2_10/"
#define ROOT "f2d_10_"

ILOSTLBEGIN

int main(int argc, const char * argv[]) {
    // variables
    Cinstance * pinst ;
    char filin[150],filout[150];
    int h,i,j,k,m,n,*s,f,*s1,somt;
    int step, ific, iinit, ifinal;
	clock_t start, finish;
	string tmp, tmph;
	stringstream ss;
	
	if (argc<2) {
	    cout << "usage: cplexexamp nb" << endl;
	    return 0;
	    }		
    // the data file
    strcpy(filout,DATADIR); 
    strcat(filout, ROOT);
    strcat(filout,argv[1]);
    strcat(filout,".res");
    ofstream resfile(filout, ios::out | ios::app); 
    ///////////////////////////
    IloEnv env;
    try {
        IloModel model(env); // Cplex model
    
        // data file
        strcpy(filin,DATADIR);
        strcat(filin, ROOT);
        strcat(filin, argv[1]);
        strcat(filin,".dat");
        // reading the file
        pinst = create_instance(filin);
        // write_instance(pinst);
        
        // initializations: m,n, ...
        m = pinst->getm();
        n = pinst->getn();
        // dynamic allocations: s(n), s1(n) 
        s = new int[n];
        s1 = new int[n];
        // computation of an initial solution (edd)
        edd(pinst,s);
        //cout << "edd = ";
        //for (j=0; j<n; j++) 
        //    cout << s[j] << " ";          
        //cout << endl;
        
        // time start
        start = clock();

        // CPLEX
        // creation of the environment
        env = IloEnv();
        // creation of the model
        model = IloModel(env);
        
        strcpy(filin, ROOT);    // naming the problem
        strcat(filin, argv[1]); // not quite necessary
        model.setName(filin);   // but convenient for the model
        //  variables:
        //  X[k,j]: n^2 binary variables 
        IloNumVarArray X( env, n*n, 0.0, 1.0, ILOINT );
        //  F[i,k] : n*m float positive variables
        IloNumVarArray F( env, n*m, 0.0, IloInfinity, ILOFLOAT );
        //  G[k] : n float positive variables
        IloNumVarArray G( env, n, 0.0, IloInfinity, ILOFLOAT );
        //  Z objective function
        IloNumVar Z( env, 0.0, IloInfinity, ILOFLOAT ); 
        X.setNames("X");
        F.setNames("F");
        G.setNames("G");
        Z.setName("Z");
        //cout << "Var declared" << endl;

        // constraints on the rows
        IloRangeArray cont1(env);
        for (j=0; j<n; j++) {
            IloExpr myExpr(env); 
            for (k=0; k<n; k++) {
                myExpr += X[k*n+j];
            }
            cont1.add(IloRange(env, 1, myExpr, 1));
            myExpr.end();
        }
        model.add(cont1);
        cont1.setNames("contRow");

        // constraints on the columns
        IloRangeArray cont2(env); 
        for (k=0; k<n; k++) {
            IloExpr myExpr(env); 
            for (j=0; j<n; j++) {
                myExpr += X[k*n+j];
            }
            cont2.add(IloRange(env, 1, myExpr, 1));
            myExpr.end();
        }
        model.add(cont2);
        cont2.setNames("contCol");
    
        // constraint (unique) F00
        // IloRange cont3;
        IloExpr myExpr1(env);
        for (j=0; j<n; j++) {
            myExpr1 += pinst->p(0,s[j])*X[j];
        }
        myExpr1 -= F[0];
        IloRange cont3 = IloRange(env, 0, myExpr1, 0);
        myExpr1.end();
        model.add(cont3);
        cont3.setName("contF00");
    
        // constraints on machine 0
        IloRangeArray cont4(env,n-1); 
        for (k=1; k<n; k++) {
            IloExpr myExpr(env);
            myExpr += F[k-1];
            for (j=0; j<n; j++) {
                myExpr += pinst->p(0,s[j])*X[k*n+j];
            }
            myExpr -= F[k];
            cont4[k-1] = IloRange(env, 0, myExpr, 0);
            myExpr.end();
        }
        model.add(cont4);
        cont4.setNames("contM0");

        // constraints on machine 1
        IloRangeArray cont7(env,n-1); 
        for (k=1; k<n; k++) {
            IloExpr myExpr(env);
            myExpr += F[n+k-1];
            for (j=0; j<n; j++) {
                myExpr += pinst->p(1,s[j])*X[k*n+j];
            }
            myExpr -= F[n+k];
            cont7[k-1] = IloRange(env, -IloInfinity, myExpr, 0);
            myExpr.end();            
        }
        model.add(cont7);
        cont7.setNames("contM1");

        // constraints machine 0 to 1
        IloRangeArray cont18(env,n); 
        for (k=0; k<n; k++) {
            IloExpr myExpr(env);
            myExpr += F[k];
            for (j=0; j<n; j++) {
                myExpr += pinst->p(1,s[j])*X[k*n+j];
            }
            myExpr -= F[n+k];
            cont18[k] = IloRange(env, -IloInfinity, myExpr, 0);
            myExpr.end();  
        }
        model.add(cont18);
        cont18.setNames("contM01");

        // constraints Tardiness
        IloRangeArray cont13(env,n); 
        for (k=0; k<n; k++) {
            IloExpr myExpr(env);
            myExpr += G[k];
            for (j=0; j<n; j++) {
                myExpr += pinst->d(s[j])*X[k*n+j];
            }
            myExpr -= F[n+k];
            cont13[k] = IloRange(env, 0, myExpr, IloInfinity);
            myExpr.end();
        }
        model.add(cont13);
        cont13.setNames("contTar");

        // constraint on the obj func
        IloExpr somT(env); // on ne la supprimera qu'à la fin
        for (k=0; k<n; k++) {
            somT += G[k];
        }
        somT -= Z;
        IloRange cont15 = IloRange(env, 0, somT, 0);
        model.add(cont15);
        cont15.setName("contTbar");

        model.add(IloMinimize(env, Z));
        // resolution
        // creation of the object cplex
        IloCplex cplex( model );
        cplex.setOut(env.getNullStream());
        cplex.setWarning(env.getNullStream());
        // exportation of the model in the file .lp
        strcpy(filin,DATADIR); 
        strcat(filin, ROOT);
        strcat(filin,argv[1]);
        strcat(filin,".lp");
        cplex.exportModel ( filin );

        // retrieving the result
        if ( cplex.solve() == IloTrue ) {
        // feasible solution (if time is limited) or optimal (otherwise)
            //cout << "T = ";
            for (k=0; k<n; k++) {
                for (j=0; j<n; j++) 
                    if (EQUAL_TO_1(cplex, X[k*n+j])) 
                        s1[k] = s[j];
                //cout << round(cplex.getValue(G[k])) << " ";
            }
            //cout << endl;
            //for (k=0; k<n; k++) 
            //    s[k] = s1[k];
            f = round(cplex.getValue(Z));
            cplex.end();
        } 
        somT.end();
        //while(nbpass<3); // fin de la boucle sur les passages (niveau 2)
        finish = clock();
        cout << ( finish - start ) / (double) CLOCKS_PER_SEC << " ";
        // Publishing results
        cout  << " Sum Tk = " << f << endl;
        resfile  << f << "; [" ;
        for (k=0;k<n;k++)
            resfile << s1[k] << " ";

        resfile  << "] " << ( finish - start ) / (double) CLOCKS_PER_SEC << endl;
        // close the model and the env
        model.end();
        env.end();
        
        delete [] s1;
        delete [] s;
        pinst->libere();
    }
    catch (IloException& e) {
        cerr << "Concert exception caught: " << e << endl;
    }
    catch (...) { 
        cout << "default exception"; 
    }    
    resfile.close();    
    return 0;
}

