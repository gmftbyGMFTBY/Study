#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

/*
   find all the primes number in the bound which we decide
 */

using namespace std;

// judge prime number
bool naive_prime_judge (int x) {
    if (x <= 1) return false;
    int bound = (int)sqrt(x) + 1;   // do not write the bound in the `for` statement, which is time-consuming
    for (int i = 2; i <= bound; i ++) {
        if (x % i == 0) return false;
    }
    return true;
}

/* prime filter
   If one number is not a prime, it must have the factor which is the prime

   Input: n
   Ouput: all the prime number between 2 and n
 */

bool mark[10000];   // mark the prime number to the true
int primesize = 0;

int init () {
    // init the mark
    for (int i = 0; i < 10000; i++) mark[i] = false;
    primesize = 0;

    for (int i = 2; i <= 10000; i ++) {
        if (mark[i] == true) continue;   // jump the prime
        
        // find the prime i
        primesize += 1;

        // mark numbers to prime
        for (int j = i * i; j < 10000; j += i) mark[j] = true;
    }

    return primesize;
}


int main () {
    int x;
    int size = init();

    printf("Get %d prime number between 2 to 10000\n", size);
    // test
    for (int i = 2; i <= 20; i ++) {
        if (mark[i] == false) printf("%d\n", i);
    }

    while (scanf("%d", &x) != EOF) {
        puts(naive_prime_judge(x) ? "YES" : "NO");
    }
    return 0;
}
