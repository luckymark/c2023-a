//
// Created by ycm on 2023/10/17.
//

#include "stdlib.h"
#include "stdbool.h"

#ifndef C2023_CHALLENGE_QUEUE_H
#define C2023_CHALLENGE_QUEUE_H

typedef struct QNode{
    struct QNode *next;
    void* val;
}QNode;

typedef struct Queue{
    struct QNode* head;
    struct QNode* tail;
    unsigned size;
}LinkQueue;

LinkQueue* linkInitQueue(unsigned size);
bool linkAppend(LinkQueue* q, void* val);
void* linkPop(LinkQueue* q);
bool linkIsEmpty(LinkQueue* q);
bool linkIsFull(LinkQueue* q);
void linkDestroy(LinkQueue* q);

typedef struct ArrQueue{
    int* arr;
    int* head;
    int* tail;
    unsigned size;
}ArrQueue;

ArrQueue* arrInitQueue(unsigned size);
bool arrAppend(ArrQueue* q, int val);
int arrPop(ArrQueue* q);
bool arrIsEmpty(ArrQueue* q);
bool arrIsFull(ArrQueue* q);
void arrDestroy(ArrQueue* q);


#endif //C2023_CHALLENGE_QUEUE_H
