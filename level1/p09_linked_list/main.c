#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

struct Node {
    struct Node * next;
    int value;
};

struct Node* insert(struct Node* head, int index, int value){
    struct Node *new_node=malloc(sizeof (struct Node));
    new_node->next=NULL;
    new_node->value=value;
    if(index<0)index=INT_MAX;
    else if(index==0){new_node->next=head;return new_node;}
    struct Node* p=head;
    while(index>1&&p->next!=NULL) { p = p->next;index-- ;}
    new_node->next=(p->next);
    p->next=new_node;
    return head;
}

int search_value(struct Node* head, int value){
    struct Node* p=head;
    int cnt = 0;
    while(p!=NULL&&p->value!=value) { p = p->next;cnt++; }
    if(p==NULL)return -1;
    else return cnt;
}

void print_link(struct Node* head){
    struct Node* p=head;
    while(p!=NULL){
        printf("%d -> ", p->value);
        p=p->next;
    }
    printf("\b\b\b\b\x20\x20\x20\x20\r\n");
}

struct Node* delete_index(struct Node* head, int index){
    struct Node* p=head;
    if(index==0)return head->next;
    while(index>0&&p->next!=NULL)p=p->next;
    p->next=p->next->next;
    return head;
}

struct Node* delete_node(struct Node* head, struct Node* node){
    if(head==node){return head->next;}
    struct Node* p=head;
    while(p->next!=NULL||p->next!=node)p=p->next;
    if(p->next==NULL)return head;
    p->next=p->next->next;
    return head;
}

struct Node* delete_value(struct Node* head, int value){
    if (head->value==value)return head->next;
    struct Node* p=head;
    while (p->next!=NULL&&p->next->value!=value)p=p->next;
    if(p->next==NULL)return head;
    p->next=p->next->next;
    return head;
}

struct Node* reversed(struct Node* head){
    struct Node* cur=head, *new_head=NULL, *q;
    while(cur!=NULL){
        q = cur->next;
        cur->next=new_head;
        new_head=cur;
        cur=q;
    }
    return new_head;
}

int main() {
    struct Node head = {NULL,0};
    int val;
    do {scanf("%d", &val);insert(&head, 1, val);}
    while (val>=0);
    delete_value(&head, val);
    print_link(&head);
    struct Node* new_head = reversed(&head);
    print_link(new_head);
    int index = search_value(new_head, 5);
    printf("%d", index);
    return 0;
}