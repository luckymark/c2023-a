#ifndef _LINKED_LIST_
#define _LINKED_LIST_
typedef struct _node{
    int value;
    struct _node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

void listAdd(List* pList,int value);
void listPrint(List *pList);
void listShow(List *pList,int target);
int listFind(List *pList,int target,int times);
void listReverse(List* pList);
#endif