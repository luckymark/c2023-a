#include<stdio.h>
#include<stdlib.h>
struct ListNode{
    int element;
    struct ListNode*next;
};
typedef  struct ListNode* Node;
void initList(Node node){
    node->next=NULL;
}
_Bool insertList(Node head,int element,int index){
    if(index<1) return 0;
    while(--index){
        head=head->next;
        if(head==NULL) return 0;
    }
    Node node = malloc(sizeof (struct ListNode));
    if(node==NULL) return 0;
    node->element=element;
    node->next=head->next;
    head->next=node;
    return 1;
}

_Bool deleteList(Node head,int index){
    if(index<1) return 0;
    while(--index){
        head=head->next;
        if(head==NULL) return 0;
    }
    if(head->next==NULL) return 0;
    Node tmp=head->next;
    head->next=head->next->next;
    free(tmp);
    return 1;
}
 void printList(Node head){
    while(head->next){
        head=head->next;
        printf(" %d",head->element);
    }
    printf("\n");
}
int findList(Node head,int element){
head=head->next;
int i=1;
while(head){
    if(head->element==element) return i;
    head=head->next;
    i++;
}
    return -1;
}
int findList2(Node head,int element){
    head=head->next;
    int i=1;
    int count=0;
    while(head){
        if(head->element==element){
            if(count==1){
                return i;
            }else count++;
        }
        head=head->next;
        i++;
    }
    return -1;
}
struct ListNode exchangeList(Node head,int sizeList){
    struct ListNode head2;
    initList(&head2);
   for(int i= sizeList;i>0;i--){
           head=head->next;
       insertList(&head2,head->element,1);
   }
    return head2;
}
int main(){
    struct ListNode head;
    initList(&head);
    for(int i=1;i<7;i++) {
        insertList(&head, i, 1);
    }
    deleteList(&head,2);
    printList(&head);
    insertList(&head,5,1);
    printList(&head);
    printf("%d\n", findList(&head,5));
    printf("%d\n", findList2(&head,5));
    printList(&head);
    struct ListNode head2=exchangeList(&head,6);
    printList(&head2);
    printf("%d\n", findList(&head2,5));
    return 0;
}
