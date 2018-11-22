#include <iostream>
#include <cstdio>

using namespace std;

int fac(int x)
{
    if(x <= 1) return 1;
    else return x * fac(x - 1);
}

void greet()
{
    cout << "Hello World!" << endl;
}

int main()
{
    return 0;
}
