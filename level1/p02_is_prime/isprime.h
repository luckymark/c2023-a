//
// Created by zjw131f1fc on 2023/9/26.
//
#include <stdio.h>
#include <math.h>
void isprime(int num)
{
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            printf("1非素数");
            return;
        }
    }
    printf("2素数");
}