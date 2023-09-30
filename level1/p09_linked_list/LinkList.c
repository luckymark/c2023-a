//
// Created by ycm on 2023/9/29.
//

#include "LinkList.h"

LinkList *createLinkList(){
    LinkList * list = malloc(sizeof(LinkList));
    list->head=list->tail=NULL;
    list->size=0;
    return list;
}
LinkList *reversedLinkList(LinkList* list){
    if(list->size<=1)return list;
    LinkNode *p, *q;
    list->tail = list->head;
    q = list->head;
    list->head = NULL;
    while(q!=NULL){
        p = q->next;
        q->next = list->head;
        list->head = q;
        q = p;
    }
    return list;
}
void* searchLinkList(LinkList* list, unsigned int index){
    if(list->size<=index)return NULL;
    LinkNode *p = list->head;
    for(;index>0;index--)p=p->next;
    return p->value;
}
LinkList *appendLinkList(LinkList* list, unsigned int index, void* value){
    LinkNode *new_node = malloc(sizeof(LinkNode)), *p = list->head;
    assert (new_node!=NULL);
    new_node->next = NULL;
    new_node->value = value;
    list->size++;
    if(list->size==1) { list->head = list->tail = new_node; return list; }
    else if(index>list->size) { list->tail->next = new_node; list->tail=new_node;return list;}
    for(;index>1;index--)p=p->next;
    new_node->next = p->next;
    p->next = new_node;
    if(p==list->tail)list->tail=new_node;
    return list;
}
bool removeLinkList(LinkList* list, unsigned int index){
    if(list->size<=index)return false;
    list->size--;
    LinkNode *p = list->head, *q;

    if(!index){list->head=list->head->next;free(p);return true;}

    for(;index>1;index--)p = p->next;
    q = p->next->next;
    if(p->next==list->tail)list->tail = p;
    free(p->next);
    p->next = q;
    return true;
}
bool destroyLinkList(LinkList* list){
    LinkNode *p=list->head;
    while(p!=NULL){p = list->head->next;
    free(list->head);
    list->head = p;}
    free(list);
    return true;
}
void** toList(LinkList* list){
    if(!list->size)return NULL;
    void** values = malloc(sizeof(list->head->value)*list->size);
    LinkNode *p = list->head;
    for(int i=0;i<list->size;i++){
        values[i] = (p->value);
        p = p->next;
    }
    return values;
}