#include <stdio.h>


//Every even natural number greater than 2 is the sum of two prime numbers.

enum {
    PRIME_MAX_NUM = 1000,
    G_NUM = 100
};

struct coord {
    int x, y;
};

int main() {
    int notPrime[PRIME_MAX_NUM + 3] = {};
    int prime[PRIME_MAX_NUM + 3] = {};
    int cnt = 0;
    struct coord table[PRIME_MAX_NUM] = {};

    for (int i = 2; i < PRIME_MAX_NUM; ++i) {
        if (!notPrime[i]) {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * prime[j] < PRIME_MAX_NUM; ++j) {
            notPrime[i * prime[j]] = 1;
            if (!(i % prime[j]))break;
        }
    }

    for (int i = 0; i < cnt; ++i) {
        for (int j = 0; j <= i; ++j) {
            table[prime[i] + prime[j]].x = prime[i];
            table[prime[i] + prime[j]].y = prime[j];
        }
    }

    for (int i = 4; i <= G_NUM; i += 2) {
        printf("%d=%d+%d\n", i, table[i].x, table[i].y);
    }
}