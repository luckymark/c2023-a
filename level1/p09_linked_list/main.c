#include "linked.h"
int main()
{
    Node *pHead=(Node*)malloc(sizeof(Node));
    int len=8;
    Creat_list(pHead,len);
    //Print_list(pHead,len);
    Anti_list(pHead,len);
    //Print_list(pHead,len);
    int temp=Find_5(pHead,0,len);
    printf("%d\n",temp);
    while(temp!=-1)
    {
        temp=Find_5(pHead,temp,len);
        printf("%d\n",temp);
    }
    return 0;
}