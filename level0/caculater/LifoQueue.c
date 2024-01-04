//
// Created by ycm on 2023/10/17.
//

#include "LifoQueue.h"

Stack* initStack(unsigned size) {
    Stack* st = (Stack*)malloc(sizeof(Stack));
    st->size = size;
    st->bottom = st->pointer = (int*)malloc(size * sizeof(int));
    return st;
}

bool pushStack(Stack* st, int val) {
    if(isFullStack(st))return false;
    *(st->pointer++) = val;
    return true;
}

int popStack(Stack* st) {
    return isEmptyStack(st)?-1:*(--st->pointer);
}

void destroyStack(Stack* st) {
    free(st->bottom);
    free(st);
}

bool isEmptyStack(Stack* st) {
    return st->pointer==st->bottom;
}
bool isFullStack(Stack* st) {
    return st->pointer== st->bottom + st->size;
}
