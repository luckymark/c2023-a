//
// Created by ycm on 2023/9/26.
//
#include "string.h"
#include "stdlib.h"

#ifndef C2023_CHALLENGE_GOODS_H
#define C2023_CHALLENGE_GOODS_H
#define MAX_NAME_SIZE 128

typedef struct Goods {
    char* type;
    char* name;
    unsigned int amount;
    double price;
    char * note;
} Goods;

#endif //C2023_CHALLENGE_GOODS_H


