#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
typedef struct Good Good;
struct Good{
    char name[30];
    char model[50];
    int num;
    Good* last;
    Good* next;
};
typedef struct Good Good;
int number = 0;
Good* pop(Good* good)
{
    Good* mgood = good;
    //Good* head = good;
    while(mgood->next != NULL)
    {
        mgood = mgood->next;

        printf("名字：%s   型号：%s   数量：%d\n",mgood->name,mgood->model,mgood->num);
    }
    printf("输入要出库的货物名称");
    char nam[30];
    memset(nam,0,sizeof(nam));
    scanf("%s",&nam);
    //good = *head;

    while(good->next != NULL)
    {
        good = good->next;
        //printf("good.name:%s \nnam:%s\n good.name==nam:%d\n",good.name,nam,good.name==nam);
        if(strcmp(good->name,nam) == 0)
        {
            if(good->last != NULL)
                good->last->next = good->next;
            if(good->next != NULL)
                good->next->last = good->last;
            //free(&good);
            printf("已出库");
            system("pause");
            system("cls");
            return good;
        }
    }
    printf("未找到！");
    system("pause");
    system("cls");
    return NULL;
}
void push(Good* good)
{
    printf("输入名字，型号，数量，换行分割\n");
    memset(good->name,0,sizeof(good->name));
    scanf("%s\n%s\n%d",&good->name,&good->model,&good->num);
    good->next = NULL;
    printf("入库成功");
    system("pause");
    system("cls");
}
void showlist(Good good)
{
    Good* mgood = &good;
    while(mgood->next != NULL)
    {
        mgood = mgood->next;
        printf("名字：%s   型号：%s   数量：%d\n",mgood->name,mgood->model,mgood->num);
    }
    system("pause");
    system("cls");
}
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