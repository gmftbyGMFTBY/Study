#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "./Biginteger.cpp"   //I only use the function I need
#include "./Extend_GCD.cpp"

using namespace std;

/*
   This Function return a list of the Biginteger number , And the size of the list is only 3.
   0 - Euler - n:Public Module number.
   1 - Public - key:Public Key in Biginteger Class.
   2 - Private - Key:Private Key in Biginteger Class.
   */
Biginteger* Create_Key(int digit,int base)
{
    Biginteger* ans = new Biginteger[3];
    Biginteger p = Random_Prime(digit,base);
    Biginteger q = Random_Prime(digit,base);
    
    cout <<"#######"<<endl;
    cout << p;
    cout << q;
    cout <<"#######"<<endl;
    Biginteger one(1,base);
    Biginteger n = p * q;
    Biginteger Euler = (p - one) * (q - one);

    ans[0] = Euler;

    ans[1] = Biginteger(65537,base);

    Biginteger x(0,base);
    Biginteger y(0,base);
    Extend_GCD(ans[1] , Euler , x , y);
    ans[3] = x;

    return ans;
}

int main()
{
    Biginteger* k = Create_Key(4,5);
    cout << "Euler" << k[0];
    cout << "PK:"<< k[1];
    cout << "PRIK:" <<k[2];
    return 0;
}
