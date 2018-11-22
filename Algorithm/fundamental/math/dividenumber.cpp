#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

/*
   Judge the number x :
        x = p1^e1 * p2^e2 * ... * pn^en
        which p1, p2, ..., pn is the prime number
        and sometimes we also need to know e1, e2, ..., en

   Algorithm:
       1. filter the prime
       2. search all the prime from 2 to 10^5 (which bound is 10^9, the reason of choosing 100^5 is that 
          every number x has only one prime which is bigger than sqrt(x), we just need to search all the
          prime lower than sqrt(x) the one meaning (is not 1) must be the prime and it is bigger than 
          sqrt(x))
       3. counting the number of the prime
 */

/*
    Question:
        给定 n , a 求最大的 k ,使 n !可以被 a^k 整除但不能被 a^(k+1) 整除。

        a  = p1^e1 * p2^e2 * ... * pn^en
        n! = pp1^ee1 * pp2^ee2 * ... & ppn^een

        find the k = min (ee1 / e1, ee2 / e2, ..., een / en)
 */

using namespace std;

bool mark[1010];
int prime[1010];
int primesize = 0;

// prime filter
void init () {
    for (int i = 0; i <= 1000; i++) mark[i] = false;
    primesize = 0;
    for (int i = 2; i <= 1000; i ++) {
        if (mark[i]) continue;
        
        prime[primesize ++] = i;    // save the prime
        
        for (int j = i * i; j <= 1000; j += i) mark[j] = true;
    }
}

int cnt[1010];      // cnt[i]  = prime[i]'s factor number in n!
int cnt2[1010];     // cnt2[i] = prime[i]'s factor number in a

int main () {
    int n, a;
    init ();

    // test the prime filter
    /*
       for (int i = 2; i < 20;i ++) 
        if (mark[i] == false)
            printf("%d\n", i);
    */

    while (scanf("%d%d", &n, &a) == 2) {
        for (int i = 0; i < primesize; i ++) cnt[i] = cnt2[i] = 0;
        
        // divide the n!
        for (int i = 0; i < primesize; i ++) {
            int t = n;
            while (t) {
                cnt[i] += t / prime[i];
                t = t / prime[i];
            }
        }

        int ans = 123123123;    // max number for using 
        // divide the a
        for (int i = 0; i < primesize; i ++) {
            while (a % prime[i] == 0) {
                cnt2[i] ++;
                a /= prime[i];
            }

            if (cnt2[i] == 0) continue;
            if (cnt[i] / cnt2[i] < ans) ans = cnt[i] / cnt2[i];
        }

        printf("%d\n", ans);
    }
    return 0;
}
