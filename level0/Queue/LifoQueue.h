//
// Created by ycm on 2023/10/17.
//

#ifndef C2023_CHALLENGE_LIFOQUEUE_H
#define C2023_CHALLENGE_LIFOQUEUE_H
#include "stdlib.h"
#include "stdbool.h"

typedef struct Stack{
    int* bottom;
    int* pointer;
    unsigned size;
} Stack;

Stack* initStack(unsigned );
bool pushStack(Stack*, int);
int popStack(Stack*);
void destroyStack(Stack*);
bool isEmptyStack(Stack*);
bool isFullStack(Stack*);

#endif //C2023_CHALLENGE_LIFOQUEUE_H
