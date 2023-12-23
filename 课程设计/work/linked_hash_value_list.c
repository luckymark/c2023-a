#include <stdio.h>
#include <stdlib.h>
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

void listAppend(List* pList, Hash_value hash_value) {
    Node *p = (Node *) malloc(sizeof(Node));
    p->hash_value = hash_value;
    p->before = pList->tail;
    p->next = NULL;
    pList->tail = p;

    Node *last = NULL;
    if( pList->head ){
        p->before->next = p;
    } else{
        pList->head = p;
    }
}

Hash_value* listSearchHash(List *pList,unsigned int hash){
    Hash_value *result = NULL;
    Node *p = pList->head;
    while (p){
        if(p->hash_value.hash == hash){
            result =  &(p->hash_value);
        }
        p = p->next;
    }
    return result;
}

bool isHashExist(List *pList,unsigned int hash){
    Node *p = pList->head;
    while (p){
        if(p->hash_value.hash == hash){
            return true;
        }
        p = p->next;
    }
    return false;
}

void listDeleteNode(List *pList , Node* pNode){
    Node *p = pList->head;
    while (p){
        if(p == pNode){
            p->before->next = p->next;
            free(p);
            break;
        }
        p = p->next;
    }
}

void listDeleteAll(List *pList){
    Node *p = pList->head;
    Node *temp = NULL;
    while (p){
        temp = p->next;
        free(p);
        p = temp;
    }
}

bool isListEmpty(List *pList){
    return pList->head == NULL;
}