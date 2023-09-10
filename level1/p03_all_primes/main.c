#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

#if defined(WIN32)
#define TIMEB _timeb
#define ftime _ftime
#else
#define TIMEB timeb
#endif

enum {
    MAX_NUM = 1000
};

int main() {
    time_t st_s, ed_s, elapse;
    struct TIMEB st_ms, ed_ms;
    ftime(&st_ms);
    time(&st_s);

    int notPrime[MAX_NUM + 3] = {};
    int prime[MAX_NUM + 3] = {};
    int cnt = 0;

    for (int i = 2; i < MAX_NUM; ++i) {
        if (!notPrime[i]) {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * prime[j] < MAX_NUM; ++j) {
            notPrime[i * prime[j]] = 1;
            if (!(i % prime[j]))break;
        }
    }
    for (int i = 0; i < cnt; ++i) {
        printf("%d ", prime[i]);
    }

    ftime(&ed_ms);
    time(&ed_s);

    elapse = (ed_s * 1000 + ed_ms.millitm) - (st_s * 1000 + st_ms.millitm);
    printf("\nelapsed time: %lldms\n", elapse);
    return 0;
}