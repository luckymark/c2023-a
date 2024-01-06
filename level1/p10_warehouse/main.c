#include <stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
struct Box{
    int data;
    char model[30];
};
struct NodeList{
    struct Box box;
    struct NodeList *next;
};
typedef  struct NodeList* Node;
void initList(Node node){
    node->next=NULL;
}
_Bool insertList(Node head){
    printf("入库位置：");
    int index;
    scanf("%d",&index);
    if(index<1) return 0;
    while(--index){
        head=head->next;
        if(head==NULL) return 0;
    }
    Node node = malloc(sizeof (struct NodeList));
    if(node==NULL) return 0;
    printf("数量 型号：\n");
    scanf("%d %s",&node->box.data,node->box.model);
    node->next=head->next;
    head->next=node;
    return 1;
}

_Bool deleteList(Node head){
    int index;
    printf("出库位置：");
    scanf("%d",&index);
    if(index<0) return 0;
    while(--index){
        head=head->next;
        if(head==NULL) return 0;
    }
    if(head==NULL) return 0;
    Node tmp=head->next;
    head->next=head->next->next;
    free(tmp);
    printf("出库成功\n");
    if(index<0) return 0;
    return 1;
}
void printList(Node head){
    while(head){
        printf(" 数量：%d 型号：%s\n",head->box.data,head->box.model);
        head=head->next;
    }
}
void warehouse(){
    for(int i=0;i<20;i++)
    printf("*");
    printf("\n");
    printf("*     1库存列表     *");
    printf("\n");
    for(int i=0;i<20;i++)
        printf("*");
    printf("\n");
    printf("*       2入库      *");
    printf("\n");
    for(int i=0;i<20;i++)
        printf("*");
    printf("\n");
    printf("*       3出库      *");
    printf("\n");
    for(int i=0;i<20;i++)
        printf("*");
    printf("\n");
    printf("*     4退出程序     *\n");
}
void welcome(Node head){
    char c=getch();
    switch (c)
    {
        case'1':
            printList(head);break;
        case'2':
            insertList(head);break;
        case'3':
            deleteList(head);break;
        case'4':
            Sleep(300);
            printf("欢迎再次使用！");
            exit(0);
        default:
            printf("请重新输入");
            break;
    }
}
int main(){
    FILE *f=fopen("D:\\c2023-a\\level1\\p10_warehouse\\data.txt","r");
    if(f==NULL){
        printf("File not found!\n");
        return 0;
    }
    struct NodeList *head=NULL;
    struct NodeList *tail=NULL;
    while(!feof(f)){
        struct NodeList *node=(struct NodeList *)malloc(sizeof(struct NodeList));
        int s1=fscanf(f,"%d",&node->box.data);
        int s2=fscanf(f,"%s",node->box.model);
        if(s1!=1||s2!=1){
            break;
        }
        node->next=NULL;
        if(head==NULL){
            head=node;
            tail=node;
        }else{
            tail->next=node;
            tail=node;
        }
    }
    fclose(f);
    warehouse();
    while(1){
        printf("请选择你的功能：\n");
        welcome(head);
        f= fopen("D:\\c2023-a\\level1\\p10_warehouse\\data.txt","w");
        struct NodeList *p=head;
        while(p!=NULL){
            fprintf(f,"%d %s\n",p->box.data,p->box.model);
            p=p->next;
        }
        fclose(f);
    }

    return 0;

}
