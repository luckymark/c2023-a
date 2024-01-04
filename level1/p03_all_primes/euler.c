#include "stdio.h"
#include "time.h"
#define MAX_SIZE 10000000

void Euler(int, int[]);//欧拉筛法

int mmain() {
    int n;
    scanf("%d", &n);
    static int out[MAX_SIZE] = {};
    clock_t s, e;
    s=clock();
    Euler(n, out);
    e=clock();
    for(int i=0;out[i]!=0;i++)printf("%d, ", out[i]);
    printf("\ntotal time: %fs", (double) (e-s)/CLOCKS_PER_SEC);
    return 0;
}

void Euler(int n, int prime[]){
    static char is_not_prime[MAX_SIZE] = {1, 1,};
    int cnt = 0;
    for(int i=2;i<=n;i++){
        if (!is_not_prime[i]) { prime[cnt] = i;cnt++ ;}
        for(int j=0;j<cnt&&i*prime[j]<=n;++j){
            is_not_prime[i*prime[j]] = 1;
            if (i%prime[j]==0)break;
        }
    }
}