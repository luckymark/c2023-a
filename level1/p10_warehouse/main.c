#include<stdio.h>
#include<stdlib.h>
#include"good.h"
int main()
{
    Good head;
    head.last = head.next = NULL;
    Good* mg = NULL;
    head.last = head.next = NULL;
    Good* now = &head;
    while(1)
    {
        printf("1:显示存货列表\n2:入库\n3:出库\n4:退出程序\n");
        char input = getchar();
        switch(input)
        {
            case '1':

                showlist(head);
                break;
            case '2':
                now->next = (Good*)malloc(sizeof(Good));
                now->next->last = now;
                now = now->next;
                push(now);
                break;
            case '3':
                mg = pop(&head);
                if(mg != NULL && mg->next == NULL)
                {
                    now = mg->last;
                }
                free(mg);
                break;
            case '4':
                return 0;
                break;
        }
        system("cls");
    }
    return 0;
}