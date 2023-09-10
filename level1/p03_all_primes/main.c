#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

#if defined(WIN32)
    #define TIMEB _timeb
    #define ftime _ftime
#else
    #define TIMEB timeb
#endif

enum {MAX_NUM = 1000};

int main() {
    time_t st_s, ed_s, elapse;
    struct TIMEB st_ms,ed_ms;
    ftime(&st_ms);
    time(&st_s);

    int table[MAX_NUM+3] = {};
    printf("2 3 ");
    for (int i = 6; i <= MAX_NUM; i += 6) {
        if (table[i-1] == 0) {
            printf("%d ", i-1);
            for (int j = i-1; j <= MAX_NUM; j += i-1) {
                table[j] = 1;
            }
        }
        if (table[i+1] == 0) {
            printf("%d ", i+1);
            for (int j = i+1; j <= MAX_NUM; j += i+1) {
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