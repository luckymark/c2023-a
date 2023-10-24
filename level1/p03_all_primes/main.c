#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

#if defined(WIN32)
#define TIMEB _timeb
#define ftime _ftime
#else
#define TIMEB timeb
#endif

#include "../p02_is_prime/Prime.h"

enum {
    PRIME_MAX_NUM = 1000
};

int main() {
    time_t st_s, ed_s, elapse;
    struct TIMEB st_ms, ed_ms;
    ftime(&st_ms);
    time(&st_s);

    int notPrime[PRIME_MAX_NUM + 3] = {};
    int prime[PRIME_MAX_NUM + 3] = {};
    int cnt = 0;

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
        printf("%d ", prime[i]);
    }

    ftime(&ed_ms);
    time(&ed_s);

    //extract test
    printf(isPrime(100) ? "yes" : "no");

    elapse = (ed_s * 1000 + ed_ms.millitm) - (st_s * 1000 + st_ms.millitm);
    printf("\nelapsed time: %lldms\n", elapse);
    return 0;
}