#include <stdio.h>

int main() {
    int n = 0;
    int isPrime = 1;
    scanf("%d",&n);
    for(int i=2;i<n;i++){
        int x = n%i;
        if(x == 0){
            isPrime = 0;
        }
    }
    if(isPrime){
        printf("This number is a prime.");
    } else{
        printf("This number is not a prime.");
    }
    return 0;
}