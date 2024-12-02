#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    struct _node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

void listAdd(List* pList,int value) {
    Node *p = (Node *) malloc(sizeof(Node));
    p->value = value;
    p->next = NULL;
    pList->tail = p;

    Node *last = NULL;
    if( pList->head ){
        last =  pList->head;
        while(last->next){
            last = last->next;
        }
        last->next = p;
    } else{
        pList->head = p;
    }
}

void listPrint(List *pList){
    for(Node *p = pList->head;p;p = p->next){
        printf("%d ",p->value);
    }
    printf("\n");
}

int listFind(List *pList,int target,int times){
    int count = 0;
    int serial = 0;
    for (Node *p = pList->head;p;p = p->next){
        serial ++;
        if(p->value == target){
            count++;
            if(count == times){
                break;
            }
        }
    }
    return count == times?serial:-1;
}
void listShow(List *pList,int target){
    int serial = 0;
    int count = 0;
    printf("The serial numbers of the founded \"%d\":",target);
    for(Node *p = pList->head; p; p = p->next){
        serial++;
        if(p->value == target){
            printf("%d ",serial);
            count ++;
        }
    }
    if(count == 0){
        printf("Not Found.");
    }
    printf("\n");
}

void listReverse(List* pList){

    Node *p1 = NULL;
    Node *p2 = NULL;
    Node *p3 = NULL;

    if(pList->head) {
        p3 = pList->head;
        int length = 1;
        while (p3->next && length < 3) {
            length++;
            p1 = p2;
            p2 = p3;
            p3 = p3->next;
        }
        if (p2 == NULL) {
            return;
        } else if (p1 == NULL){
            p3->next = p2;
            p2->next = NULL;
        } else {
            p1->next = NULL;
            p2->next = p1;
            while(p3->next){
                p1 = p2;
                p2 = p3;
                p3 = p3->next;
                p2 ->next = p1;
            }
            p3->next = p2;
        }
        Node *temp = pList->head;
        pList->head  = pList->tail;
        pList->tail = temp;
    }else{
        return;
    }
}