#include "stdio.h"
#include "time.h"
#include "prime.h"
#include "euler.h"

//char is_prime(int);
//void print_all_prime(int);
void print_prime(int*);

int main(){
    int n;
    clock_t start, end;
    scanf("%d", &n);
    printf("Normal prime function:\n");

    start=clock();
    int* lst = all_prime(n);
    end=clock();
    print_prime(lst);
    printf("\ntotal time:%fs", (double)(end-start)/CLOCKS_PER_SEC);

    printf("\n\nEuler prime function:\n");
    start=clock();
    lst = Euler_prime(n);
    end=clock();
    print_prime(lst);
    printf("\ntotal time:%fs", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}

void print_prime(int* primes){
    int i = 0;
    while(primes[i]>0)printf("%d, ", primes[i++]);
}


/*char is_prime(int n){
    int sq = (int) sqrt(n)+1;
    if(n==2)return 1;
    for(int i=2;i<=sq;i++)if(n%i==0)return 0;
    return 1;
}*/

/*void print_all_prime(int n){
    for(int i=2;i<=n;i++)if(is_prime(i))printf("%d, ", i);
}*/
