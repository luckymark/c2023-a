#ifndef GOBANG_ZOBRIST_H
#define GOBANG_ZOBRIST_H
#include "defination.h"
void randomFill(unsigned long long (*b)[15][2]);
void changeHash(unsigned long long *hashKey,unsigned long long (*hashMap)[15][2],Point *step,enum piece side);
#endif //GOBANG_ZOBRIST_H