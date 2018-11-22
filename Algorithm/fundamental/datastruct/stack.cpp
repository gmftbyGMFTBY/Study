#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

/*
   Add the STL in C++ for coding
   stack<int> S;
   S.push(i);
   int x = S.top();
   S.pop();
   S.empty();
 */

stack<int> S;
char str[200];
char ans[200];

int main () {
    while (scanf("%s", str) != EOF) {
        int i;
        for (i = 0; str[i] != 0; i ++) {
            if (str[i] == '(') {
                S.push(i);
                ans[i] = ' ';
            }
            else if (str[i] == ')') {
                if (S.empty() == 0) {
                    S.pop();
                    ans[i] = ' ';
                }
                else ans[i] = '?';
            }
            else ans[i] = ' ';
        }

        while (!S.empty()) {
            ans[S.top()] = '$';
            S.pop();
        }

        ans[i] = 0;
        puts(str);
        puts(ans);
    }
    return 0;
}
