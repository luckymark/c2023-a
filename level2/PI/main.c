//输出圆周率前20000位数字
#include <stdio.h>
#include <time.h>
#define num 10000
long a = num,b = 0,c = num,d,e,f[num+1],g;

int main() {
    struct timespec start, end;

    // 记录开始时间
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    while (b != c) {
        f[b++] = a/5;
    }
    while (c > num/2) {
        d =0;
        g = c *2;
        b = c;
        while (1) {
            d += f[b] * a;
            g--;
            f[b] = d % g;
            d /= g;
            g--;
            b--;
            if (b <= 0) {
                break;
            }
            d *= b;
        }
        c --;
        printf ("%.4ld", e + d / a );
        e = d % a;
    }

    // 记录结束时间
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    // 计算运行时间
    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("\nRuntime: %f s\n", elapsed);

    return 0;
}
