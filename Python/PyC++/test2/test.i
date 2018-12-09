%module test
%{
#include <iostream>
#include <cstdio>
using namespace std;

extern int fac(int);
extern void greet();
%}

extern int fac(int);
extern void greet();
