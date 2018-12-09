#include <iostream>
#include <stdlib.h>
#include <queue>

/*
   priority_queue
   priority_queue<int> Q; default the max heap
   priority_queue<int, vector<int>, greater<int>> Q;  min heap
   Q.push(x)
   int a = Q.top()
   Q.pop()
 */

using namespace std;

priority_queue <int, vector<int>, greater<int>> Q;  // min heap

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {
        while (Q.empty() == false) Q.pop();
        for (int i = 1; i <= n; i ++) {
            int x;
            scanf("%d", &x);
            Q.push(x);
        }

        int ans = 0;
        while (Q.size() > 1) {
            int a = Q.top();
            Q.pop();
            int b = Q.top();
            Q.pop();

            ans += a + b;
            Q.push(a + b);
        }
        printf("%d\n", ans);
    }
    return 0;
}
