#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

typedef struct node Node;

Node* opposite(Node* head,int n,char list[])
{
    int i;
    Node* head_oppo =(Node*)malloc(sizeof(Node));
    Node *r,*s;
    r = head_oppo;
    for (i=0;i<n;i++)
    {
        s = malloc(sizeof(Node));
        s -> data = list[n - i - 1];
        r -> next = s;
        r = s;
    }
    r -> next = NULL;
    return head_oppo;
}

Node* createlist(int n)
{
    int i;
    int num;
    Node *q,*p;
    Node* head =(Node*)malloc(sizeof(Node));
    p = head;
    for(i=0;i<n;i++)
    {
        printf("输入节点%d内容:",i+1);
        scanf("%d",&num);
        q = malloc(sizeof(Node));
        q -> data = num;
        p -> next = q;
        p = q;
    }
    q -> next = NULL;
    return head;
};

void print(Node* head)
{
    int i=0;
    Node *pMove = head -> next;
    if (pMove == NULL)
    {
        printf("该链表为空\n");
    }
    else
    {
        while (pMove != NULL) {
            printf("节点%d为:%d\n", i + 1, pMove->data);
            i++;
            pMove = pMove->next;
        }
    }
}

void Find(Node* head,int find)
{
    int i=0,j=1;
    Node *pMove = head -> next;
    if (pMove == NULL)
    {
        printf("查找为空\n");
    }
    else
    {
        while (pMove != NULL) {
            if (pMove -> data == find)
            {
                printf("第%d个%d的序号为%d\n",j,find,i + 1);
                j++;
            }
            i++;
            pMove = pMove->next;
        }
        if (j == 1)
        {
            printf("查找为空\n");
        }
    }
}



int main(){
    int n;    //节点个数
    int find;
    printf("输入节点个数:");
    scanf("%d",&n);
    Node* head = createlist(n);
    int i=0;
    char list[n];
    Node *pMove = head -> next;
    while (pMove != NULL)
    {
        list[i] = pMove->data;
        i++;
        pMove = pMove->next;
    }
    print(head);
    printf("输入需要查找的内容:");
    scanf("%d",&find);
    Node* head_oppo = opposite(head,n,list);
    printf("颠倒后:\n");
    print(head_oppo);
    Find(head_oppo,find);
    system("pause");
    return 0;
}