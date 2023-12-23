#include <time.h>
#include "defination.h"
#include "MT199937.h"
void randomFill(unsigned long long (*b)[15][2]){
    mt19937_init((unsigned)time(NULL));
    for(int i = 0; i < 15; i++){
        for ( int j = 0; j < 15; j++){
            b[i][j][0] = ((unsigned long long)mt19937_generate()<<32)|mt19937_generate();
            b[i][j][1] = ((unsigned long long)mt19937_generate()<<32)|mt19937_generate();
        }
    }
}

void changeHash(unsigned long long *hashKey,unsigned long long (*hashMap)[15][2],Point *step,enum piece side){
    *hashKey ^= hashMap[step->y][step->x][side == Black?0:1];
}