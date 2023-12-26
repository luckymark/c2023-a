#include <stdio.h>
#include <time.h>
#include "p.h"
int a[1001];
/*void prime(int step){
    for(int i=step;i<=1000;i+=step) a[i]=0;
    return;
}*/
int main() {
    clock_t start,end;
    start=clock();
    /*for (int i = 2; i <= 1000; i++) a[i] = 1;
    for (int i = 2; i <= 1000; i++) {
        if (a[i]) {
            printf("%d ", i);
            prime(i);
        }
    }*/
    for(int i=2;i<=1000;i++){
        if(prime(i)) printf("%d ",i);
    }
    end=clock();
    printf("\ntime=%lfs",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}