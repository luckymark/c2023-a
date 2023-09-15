#include "stdio.h"
#include "math.h"
#define boolean short

boolean is_prime(int);

int main() {
    int n;
    scanf("%d",&n);
    if (is_prime(n))printf("true");
    else printf("false");
    return 0;
}

boolean is_prime(int n){
    if (n==2)return 1;
    int sqr = (int) sqrt(n)+1;
    for(int i=2;i<=sqr;i++)if(n%i==0)return 0;
    return 1;
}