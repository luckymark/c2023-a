#include <stdio.h>
#include <math.h>
#include <time.h>
int main() {
    int begin,end,i,j;
    begin = clock();
    for(i = 2;i <= 1000;i++) {
        for (j = 2; j < sqrt(i); j++) {
            if(i % j == 0) {
                break;
            }
        }
        if (j > sqrt(i)) {
            printf("%d ",i);
        }
    }
    end = clock();
    printf("\nRunning Time: %dms",end - begin);
    return 0;
}