#include<stdio.h>
#include"isprime.h"
int isprime(int x);
int main(){
    int x;
    scanf("%d",&x);
    if (isprime(x)) {
        printf("是素数");
    }else{
        printf("不是素数");
    }
    return 0;
}
