//
// Created by Cyril on 2023/9/26.
//

#include "prime.h"
#include <stdbool.h>

bool isPrime(int input) {
    for (int i = 2; i * i <= input; ++i)
        if (input % i == 0) return false;
    return true;
}