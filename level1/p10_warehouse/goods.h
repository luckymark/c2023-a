//
// Created by ycm on 2023/9/26.
//
#include "string.h"
#include "stdlib.h"

#ifndef C2023_CHALLENGE_GOODS_H
#define C2023_CHALLENGE_GOODS_H

typedef struct Goods {
    char* type;
    char* name;
    double price;
    unsigned int amount;
    char * note;
} Goods;

#endif //C2023_CHALLENGE_GOODS_H


