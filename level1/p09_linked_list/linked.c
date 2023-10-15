#include "linked.h"
void Creat_list(Node* pHead,int n)
{
    pHead->num=1;
    pHead->next=NULL;
    printf("Please input the NO.1 data\n");
    scanf("%d",&(pHead->data));
    Node* pEnd,* pNew;
    pEnd=pHead;
    for(int i = 0;i<n-1;i++)
    {
        pNew = (Node *) malloc(sizeof(Node));
        pNew->num=i+2;
        printf("Please input the NO.%d data\n",i+2);
        scanf("%d",&(pNew->data));
        pNew->next=NULL;
        pEnd->next=pNew;
        pEnd=pNew;
    }
}
Node* List(Node* pHead,int n)
{
    Node* pTemp=pHead;
    for(int i = 0;i<n-1;i++)
    {
        pTemp = pTemp->next;
    }
    return pTemp;
}
void Print_list(Node* pHead,int n)
{
    printf("The list has %d Nodes\n", n);
    for(int i = 1;i<=n;i++)
    {
        printf("%d %d\n",List(pHead,i)->num,List(pHead,i)->data);
    }
}
void Anti_list(Node* pHead,int n)
{
    for(int i=1;i<=n/2;i++)
    {
        int temp1=List(pHead,i)->data;
        List(pHead,i)->data=List(pHead,n+1-i)->data;
        List(pHead,n+1-i)->data=temp1;
    }
}
int Find_5(Node* pHead,int start,int n)
{
    int i;
    for(i = start+1;i<=n;i++)
    {
        if(List(pHead,i)->data==5)
            return i;
    }
    if(i==n+1)
        return -1;
}

