%module test
%{
#include <stdio.h>
extern int fac(int);
%}

extern int fac(int);
