#include <stdio.h>
#include <stdlib.h>
typedef struct ListNode ListNode;
struct ListNode
{
    int value;
    ListNode* next;

};
void bianli(ListNode* mylist)
{
    while(mylist != NULL)
    {
        printf("%d \n", mylist->value);
        mylist = mylist->next;
    }
    //printf("%d \n", mylist);
}
int main()
{
    ListNode* now = NULL;
    ListNode* first = NULL;
    printf("number:\n");
    int num;
    scanf("%d", &num);
    printf("value:\n");
    for(int i = 0; i < num; i++)
    {
        if(now == NULL)
        {
            now = (ListNode*)malloc(sizeof(ListNode));
            scanf("%d",&now->value);
            now->next = NULL;
            first = now;
        }
        else
        {
            now->next = (ListNode*)malloc(sizeof(ListNode));
            now = now->next;
            scanf("%d",&now->value);
            now->next = NULL;
        }
    }
    printf("1:遍历链表\n");
    bianli(first);
    printf("2:反序\n");
    ListNode *list1,*list2,*list3;
    list1 = NULL;
    list2 = first;
    if(first->next == NULL)
    {
        goto finish;
    }
    now = first;
    list3 = first->next;
    while(list3 != NULL)
    {
        list2->next = list1;
        list1 = list2;
        list2 = list3;
        list3 = list3->next;
    }
    list2->next = list1;
    first = list2;
    finish:
    bianli(first);
    printf("3:查找5\n");
    ListNode* mylist = first;
    int isfind = 0;
    int idx = 1;
    while(mylist != NULL)
    {
        if(mylist->value == 5)
        {
            printf("%d \n", idx);
            isfind ++;
        }
        mylist = mylist->next;
        idx++;
    }
    if(isfind == 0)
    {
        printf("-1\n-1");
    }
    if(isfind == 1)
    {
        printf("-1");
    }
    return 0;
}