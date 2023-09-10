#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

#if defined(WIN32)
    #define TIMEB _timeb
    #define ftime _ftime
#else
    #define TIMEB timeb
#endif

int main() {
    time_t st_s, ed_s, elapse;
    struct TIMEB st_ms,ed_ms;
    ftime(&st_ms);
    time(&st_s);

    int table[1003] = {};
    for (int i = 2; i <= 1000; ++i) {
        if (table[i] == 0) {
            printf("%d ", i);
            for (int j = i; j <= 1000; j += i) {
                table[j] = 1;
            }
        }
    }

    ftime(&ed_ms);
    time(&ed_s);

    elapse = (ed_s * 1000 + ed_ms.millitm) - (st_s * 1000 + st_ms.millitm);
    printf("\nelapsed time: %lldms\n", elapse);
    return 0;
}