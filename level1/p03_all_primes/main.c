#include "stdio.h"
#include "time.h"
#include "math.h"

char is_prime(int);
void print_all_prime(int);

int main(){
    int n;
    clock_t start, end;
    scanf("%d", &n);
    start=clock();
    print_all_prime(n);
    end=clock();
    printf("\ntotal time:%fs", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}

char is_prime(int n){
    int sq = (int) sqrt(n)+1;
    for(int i=2;i<=sq;i++)if(n%i==0)return 0;
    return 1;
}

void print_all_prime(int n){
    for(int i=2;i<=n;i++)if(is_prime(i))printf("%d, ", i);
}
