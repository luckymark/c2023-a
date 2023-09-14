#include <stdio.h>
#include <time.h>

int isPrime(int n);

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

int isPrime(int n){
    int isPrime = 1;
    for(int i=2;i<n;i++){
        int x = n%i;
        if(x == 0){
            isPrime = 0;
            break;
        }
    }
    return isPrime;
}