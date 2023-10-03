//
// Created by ycm on 2023/9/26.
//

#include <stdlib.h>

#ifndef C2023_CHALLENGE_EULER_H
#define C2023_CHALLENGE_EULER_H

#endif //C2023_CHALLENGE_EULER_H

int* Euler_prime(int n/*, int prime[]*/){
    char* is_not_prime = malloc((n+2)*sizeof(char));
    int* prime = malloc((n+2)*sizeof(int));
    is_not_prime[0] = 1;is_not_prime[1] = 1;
    for(int i=2;i<n+2;i++)is_not_prime[i] = 0;

    int cnt = 0;
    for(int i=2;i<=n;i++){
        if (!is_not_prime[i]) { prime[cnt] = i;cnt++ ;}
        for(int j=0;j<cnt&&i*prime[j]<=n;++j){
            is_not_prime[i*prime[j]] = 1;
            if (i%prime[j]==0)break;
        }
    }
    int* ans = malloc((cnt+1)*sizeof(int));
    for(int i=0;i<cnt;i++)ans[i]=prime[i];
    ans[cnt] = 0;
    free(prime);free(is_not_prime);
    return ans;
}