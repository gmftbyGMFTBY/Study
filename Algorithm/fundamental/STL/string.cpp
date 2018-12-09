#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>   // not the <string.h>

/*
    string s:
        * cin >> s;
        * char str[] = "test";
          s = str;
        * s += 'c';
          s += "ao";
          string b = "lantian";
          s += b;
        * s == b
          s <= b
        * cout << s;
          printf("%s\n", s.c_str());
        * s.size()
        * s.erase(begin, length)
        * s.find(substring, startpos);
            when not find, return string:npos
        * s.insert(2, substring);
 */

using namespace std;

int main () {
    string s;
    cin >> s;
    s += 'c';
    s += "ao";
    string b = "lantian";
    s += b;
    cout << s;
    s.erase(0, 3);
    string k = "an";
    printf("\n%d\n", s.find(k, 0));
    s.insert(0, k);
    printf("\n%s\n", s.c_str());

    char str[100];
    while (true) {
        cin.getline(str, sizeof(str));
        puts(str);
    }
    return 0;
}
