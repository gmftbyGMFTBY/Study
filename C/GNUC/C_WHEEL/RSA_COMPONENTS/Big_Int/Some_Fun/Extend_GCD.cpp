#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
//#include "Biginteger.h"

using namespace std;

int Extend_GCD(int a,int b,int& x,int& y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    cout <<"a: "<<a <<endl<<"b:"<<b<<endl;
    int t = Extend_GCD(b,a % b,x,y);
    int g = x;
    x = y;
    y = g - (a / b) * y;
    cout <<"x: " <<x <<endl<<"y:"<< y<<endl;
    return g;
}

int main()
{
    int x,y;
    int k = Extend_GCD(3,19,x,y);
    cout << x <<endl<< y <<endl;
    cout << k <<endl;
    return 0;
}
