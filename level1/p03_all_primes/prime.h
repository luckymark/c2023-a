//
// Created by ycm on 2023/9/26.
//
#include "stdlib.h"
#ifndef C2023_CHALLENGE_PRIME_H
#define C2023_CHALLENGE_PRIME_H

#endif //C2023_CHALLENGE_PRIME_H
#include "math.h"
/*double sqrt(double x){
    double y = x;
    while(y*y<x){
        y = (y+x/y)*0.5;
    }
    return y;
}*/


char is_prime(int n){
    int sq = (int) sqrt(n)+1;
    if(n==2)return 1;
    for(int i=2;i<=sq;i++)if(n%i==0)return 0;
    return 1;
}

int* all_prime(int n){
    int* prime = malloc(n*sizeof(int));
    int cnt = 0;
    for(int i=2;i<=n;i++)if(is_prime(i))prime[cnt++] = i;
    int* ans = malloc((cnt+1)*sizeof(int));
    for(int i=0;i<cnt;i++)ans[i] = prime[i];
    ans[cnt] = 0;
    free(prime);
    return ans;
}
