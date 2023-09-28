#include <stdio.h>
#include "prime.h"
int main() {
    int num;
    printf("Enter a num:");
    scanf("%d",&num);
    if (is_prime(num)) {
        printf("It is a prime.");
    } else {
        printf("It is not a prime.");
    }
    return 0;
}