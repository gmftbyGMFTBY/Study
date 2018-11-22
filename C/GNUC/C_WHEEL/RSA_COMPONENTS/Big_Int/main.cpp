#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "./Biginteger.h"
#include <string>
#include <time.h>

using namespace std;

int main()
{
    cout << "Welcome to use the RSA Algorithm Experiment Programm - By Lantian" << endl;
    cout << "Please to choose the Base of the Biginteger(1 - 9: presents:10 - 1e9) - Recommend the 5(1e5)" << endl;
    int base;
    cin >> base;
    cout << "Please choose two Primes' digits:" << endl;
    int length_digit1 ,length_digit2;
    cout << "1: "; cin >> length_digit1;
    cout << "2: "; cin >> length_digit2;
    cout << "Begin to run ..." << endl;
    /*
    clock_t beginp = clock();
    Biginteger ansp = Random_Prime(30,5);
    cout << ansp;
    clock_t endp = clock();
    cout << "Time: "<< (endp-beginp)/CLOCKS_PER_SEC <<endl;
    */
    //Following text's base is 5,you can set it from 1 - 9 Anyway.
    Biginteger publickey(0,base);
    Biginteger privatekey(0,base);
    Biginteger module(0,base);
    Create_Key(length_digit1,length_digit2,base,module,publickey,privatekey);

    cout << publickey << privatekey << module;
    string a;
    cout << "Try to input the text!" << endl;
    cin >> a;
    Biginteger text(a,base);

    clock_t begin = clock();
    Biginteger ans = Encoding(text,publickey,module);
    cout << "The answer of the Encoding!" << endl;
    cout << ans;
    cout << "Try to decoding!" << endl;
    ans = Decoding(ans,privatekey,module);
    cout << "The answer of the Decoding!" << endl;
    cout << ans;
    cout << "Are the result is the same as the input ?" << endl;
    clock_t end = clock();
    cout << "The Encoding and the Decoding finished in " << (end - begin)/CLOCKS_PER_SEC << 's' << endl;
    if(text == ans) cout << "Yes , The RSA Algorithm is Done Successfully!" << endl;
    else cout << "No , There are some wrongs with the programm." << endl;
    /*
    string a,b;
    cin >> a >> b;
    Biginteger i(a,5);
    Biginteger j(b,5);
    i = i % j;
    cout << i;*/
    return 0;
}
