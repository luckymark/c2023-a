#include "stdio.h"
#define MAX_SIZE 10000000

int Euler(int, int[]);//欧拉筛法
void Goldbach(int);

int main() {
    int n;
    scanf("%d", &n);
    Goldbach(n);
    return 0;
}

int Euler(int n, int prime[]){
    static char is_not_prime[MAX_SIZE] = {1, 1};
    int cnt = 0;
    for(int i=2;i<=n;i++){
        if (!is_not_prime[i]) { prime[cnt] = i;cnt++ ;}
        for(int j=0;j<cnt&&i*prime[j]<=n;++j){
            is_not_prime[i*prime[j]] = 1;
            if (i%prime[j]==0)break;
        }
    }
    return cnt;
}

void Goldbach(int n){
    static int prime[MAX_SIZE] = {};
    int pri_num = Euler(n, prime);
    static long plus[MAX_SIZE] = {};
    for (int i=1;i<pri_num&&prime[i]<n;i++){
        for (int j=i; j<pri_num&&prime[i]+prime[j]<=n;j++){
            plus[(prime[i]+prime[j])/2] = (i<<16)|(j%(1<<16));
        }
    }
    int k = 3;
    printf("4=2+2\n");
    while(plus[k]!=0){
        printf("%d=%d+%d\n", k*2, prime[plus[k]>>16], prime[plus[k]<<16>>16]);
        k++;
    }
    if (--k*2==n)printf("Goldbach said right!");
    else printf("Goldbach said wrong to the number %d.", k*2);
}