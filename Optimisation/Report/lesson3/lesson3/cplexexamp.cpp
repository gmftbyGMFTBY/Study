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
#include <sstream>

#include "instance.h"
#include <ilcplex/ilocplex.h>

#define EQUAL_TO_1( ilocplex, var ) ((ilocplex).getValue((var)) > 0.5)   // kai
#define EQUAL_TO_0( ilocplex, var ) ((ilocplex).getValue((var)) < 0.5)   // kai
#define EQUAL_TO( ilocplex, var, val ) (((ilocplex).getValue((var)) - (val)) < 0.5) && (-((ilocplex).getValue((var)) + (val)) < 0.5)   // kai

#define DATADIR "/Users/jean-louisbouquard/Enseignement/BIT_teaching/optimization/opti_pgm/F2data/F2_40/"
#define ROOT "f2d_40_"

ILOSTLBEGIN

int main(int argc, const char * argv[]) {
    // variables
    Cinstance * pinst ;
    char filin[150],nb[5],filout[150];
    int nb;
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
    strcpy(filout,DATADIR); // instead of ficout
    strcat(filout, ROOT);
    strcat(filout,argv[1]);
    strcat(filout,".res");
    ofstream resfile(filout, ios::out | ios::app); // instead of fichier
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

        // initializations: m,n, ...
        m = pinst->getm();
        n = pinst->getn();
        // dynamic allocations: s(n),c(m*n),t(n),delta(m*n), s1(w) ...
        s = new int[n];
        s1 = new int[w];
        // computation of an initial solution (edd)
        edd(pinst,s);

        //  coef c,t,f, delta
        compute_ctf(pinst, s, 0, c, t, &f);
        fichier << ";" << f;
 
        totimp=0;
        nbpass=0;
    
        // time start
        start = clock();

        // CPLEX
        // creation of the environment
        env = IloEnv();
        // creation of the model
        model = IloModel(env);
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
            for (j=0; j<w; j++) {
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
        for (j=0; j<w; j++) {
            myExpr1 += pinst->p(0,s[j])*X[j];
        }
        myExpr1 -= C[0];
        IloRange cont3 = IloRange(env, 0, myExpr1, 0);
        myExpr1.end();
        model.add(cont3);
        cont3.setName("contF00");
    
        // constraints on machine 0
        IloRangeArray cont4(env,n-1); 
        for (k=1; k<n; k++) {
            IloExpr myExpr(env);
            myExpr += C[k-1];
            for (j=0; j<n; j++) {
                myExpr += pinst->p(0,s[j])*X[k*n+j];
            }
            myExpr -= C[k];
            cont4[k-1] = IloRange(env, 0, myExpr, 0);
            myExpr.end();
        }
        model.add(cont4);
        cont4.setNames("contM0");

        // constraints on machine 1
        IloRangeArray cont7(env,n-1); 
        for (k=1; k<n; k++) {
            IloExpr myExpr(env);
            myExpr += C[n+k-1];
            for (j=0; j<n; j++) {
                myExpr += pinst->p(1,s[j])*X[k*n+j];
            }
            myExpr -= C[n+k];
            cont7[k-1] = IloRange(env, -IloInfinity, myExpr, 0);
            myExpr.end();            
        }
        model.add(cont7);
        cont7.setNames("contM1");

        // constraints machine 0 to 1
        IloRangeArray cont18(env,n); 
        for (k=0; k<n; k++) {
            IloExpr myExpr(env);
            myExpr += C[k];
            for (j=0; j<n; j++) {
                myExpr += pinst->p(1,s[j])*X[k*w+j];
            }
            myExpr -= C[n+k];
            cont18[k] = IloRange(env, -IloInfinity, myExpr, 0);
            myExpr.end();  
        }
        model.add(cont18);
        cont18.setNames("contM01");

        // constraints Tardiness
        IloRangeArray cont13(env,w); 
        for (k=0; k<n; k++) {
            IloExpr myExpr(env);
            myExpr += T[k];
            for (j=0; j<n; j++) {
                myExpr += pinst->d(s[j])*X[k*n+j];
            }
            myExpr -= C[n+k];
            cont13[k] = IloRange(env, 0, myExpr, IloInfinity);
            myExpr.end();
        }
        model.add(cont13);
        cont13.setNames("contTar");

        // constraint on the obj func
        IloExpr somT(env); // on ne la supprimera qu'à la fin
        for (k=0; k<n; k++) {
            somT += T[k];
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
        strcpy(filin,"model.lp");
        cplex.exportModel ( filin );

        // retrieving the result
        if ( cplex.solve() == IloTrue ) {
        // feasible solution (if time is limited) or optimal (otherwise)
            for (k=0; k<n; k++) 
                for (j=0; j<n; j++) 
                    if (EQUAL_TO_1(cplex, X[k*n+j])) 
                        s1[k] = s[j];
            //for (k=0; k<w; k++) 
            //    s[k] = s1[k];
            
        cplex.end();
        } 
        somT.end();
        //while(nbpass<3); // fin de la boucle sur les passages (niveau 2)
        finish = clock();
        cout << ( finish - start ) / (double) CLOCKS_PER_SEC << " ";
        // Publishing results
        cout  << " Sum Tk = " << f << endl;
        filout  << f << ";" ;
        //for (k=0;k<n;k++)
        //    fichier << s[k] << " ";
        filout  << ( finish - start ) / (double) CLOCKS_PER_SEC << endl;
        // on ferme !
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
    filout.close();    
    return 0;
}

