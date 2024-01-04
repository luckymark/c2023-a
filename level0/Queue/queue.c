//
// Created by ycm on 2023/10/17.
//

#include "queue.h"

ArrQueue* arrInitQueue(unsigned size){
    ArrQueue* q = (ArrQueue *)malloc(sizeof(ArrQueue));
    q->arr = q->head = q->tail = (int*) malloc((size+1)*sizeof(int));
    q->size = size;
    return q;
}

bool arrAppend(ArrQueue* q, int val){
    if(arrIsFull(q))return false;
    *(q->tail++) = val;
    q->tail = q->arr+(q->tail-q->arr)%(q->size+1);
    return true;
}

int arrPop(ArrQueue* q){
    if(arrIsEmpty(q))return -1;
    int val = *(q->head++);
    q->head = q->arr+(q->head-q->arr)%(q->size+1);
    return val;
}

bool arrIsEmpty(ArrQueue* q){
    return q->head==q->tail;
}

bool arrIsFull(ArrQueue* q){
    //return (q->arr+(q->tail-q->arr+1)%(q->size+1))==q->head;
    return (q->head-q->tail+q->size)==1;
}

void arrDestroy(ArrQueue* q){
    free(q->arr);
    free(q);
}

/*

LinkQueue* linkInitQueue(unsigned size){
    LinkQueue* q = (LinkQueue *)malloc(sizeof(LinkQueue));
    q->head = q->tail = NULL;
    q->size = size;
    return q;
}

bool linkAppend(LinkQueue* q, void* val){
    if(linkIsFull(q))return false;
    QNode* node = (QNode *)malloc(sizeof(QNode));
    node->val = val;
    node->next = NULL;
    return true;
}
*/
