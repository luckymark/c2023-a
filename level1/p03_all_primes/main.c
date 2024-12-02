#include <stdio.h>
#include <time.h>
#include "isPrime.h"

int main() {
    clock_t start_t,end_t;
    double total_t;
    start_t = clock();

    for (int i = 2;i<=1000;i++){
        if(isPrime(i)){
            printf("%d\n",i);
        }
    }

    end_t = clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    printf("The total running time: %lfs",total_t);
    return 0;
}