//
// Created by ycm on 2023/9/29.
//
#ifndef C2023_CHALLENGE_LINKLIST_H
#define C2023_CHALLENGE_LINKLIST_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "assert.h"

typedef struct LinkNode {
    struct LinkNode *next;
    void* value;
}LinkNode;

typedef struct LinkList {
    struct LinkNode *head;
    struct LinkNode *tail;
    unsigned int size;
}LinkList;

LinkList *createLinkList(void);
LinkList *reversedLinkList(LinkList*);
void* searchLinkList(LinkList*, unsigned int);
LinkList *appendLinkList(LinkList*, unsigned int, void*);
bool removeLinkList(LinkList*, unsigned int);
bool destroyLinkList(LinkList*);
void** toList(LinkList*);

#endif //C2023_CHALLENGE_LINKLIST_H
