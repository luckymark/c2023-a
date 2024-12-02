#ifndef _LINKED_HASH_VALUE_LIST_
#define _LINKED_HASH_VALUE_LIST_
#include <stdbool.h>
#include "defination.h"
typedef struct _node{
    struct _node *before;
    Hash_value hash_value;
    struct _node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

void listAppend(List* pList, Hash_value hash_value);
Hash_value* listSearchHash(List *pList,unsigned int hash);
bool isHashExist(List *pList,unsigned int hash);
void listDeleteNode(List *pList , Node* pNode);
void listDeleteAll(List *pList);
bool isListEmpty(List *pList);

#endif