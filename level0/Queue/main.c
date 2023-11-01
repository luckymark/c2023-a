//
// Created by ycm on 2023/10/17.
//
#include <assert.h>
#include "queue.h"
#include "LifoQueue.h"


int main(){
    ArrQueue * queue=arrInitQueue(4);
    assert(arrIsEmpty(queue));
    arrAppend(queue, 1);
    arrAppend(queue, 2);
    arrAppend(queue, 3);

    assert(arrIsFull(queue));

    int x=arrPop(queue);
    assert(arrPop(queue)==2);
    assert(arrPop(queue)==3);
    assert(arrIsEmpty(queue));
    arrDestroy(queue);
// test for LifoQueue
    Stack* st = initStack(5);
    assert(isEmptyStack(st));
    pushStack(st, 1);
    pushStack(st, 2);
    pushStack(st, 3);
    pushStack(st, 4);
    pushStack(st, 5);

    assert (isFullStack(st));
    popStack(st);
    assert(popStack(st)==4);
    assert(popStack(st)==3);
    popStack(st);
    pushStack(st, 2);
    pushStack(st, 3);
    pushStack(st, 4);
    pushStack(st, 5);
    assert(isFullStack(st));
    assert(!pushStack(st,6));
    for(int i=5;i>0;i--)popStack(st);
    assert(isEmptyStack(st));
    destroyStack(st);
}