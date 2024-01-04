#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct store
{
    char name[999];
    int num;
}store;

int Count = 0;
store list[999];

void show()
{
    int i;
    printf("************************************\n");
    printf("id\t\t数量\n");
    for(i=0;i<Count;i++)
    {
        printf("%s\t\t%d\n",list[i].name,list[i].num);
    }
}

void add()
{
    store new_store;
    printf("id:");
    scanf("%s",new_store.name);
    printf("数量:");
    scanf("%d",&new_store.num);
    list[Count] = new_store;
    Count++;
}

void delete()
{
    int i,j;
    int f = 0;
    char id[999];
    printf("id:");
    scanf("%s",id);
    for (i=0;i<Count;i++)
    {
        if (strcmp(list[i].name , id) == 0)
        {
            printf("已删除id为%s的货物%d项\n",list[i].name,list[i].num);
            for (j=i;j<Count-1;j++)
            {
                list[j] = list[j+1];
            }
            f = 1;
            Count--;
            break;
        }
    }
    if(f == 0)
    {
        printf("未找到该货物\n");
    }
}

int main(){
    FILE* fp;
    int f = 0;
    int choice;
    fp = fopen("Inventory.dat", "r");
    if (fp != NULL) {
        fread(&Count, sizeof(int), 1, fp);
        fread(list, sizeof(store), Count, fp);
        fclose(fp);
    }
    while(f == 0)
    {
        printf("************************************\n");
        printf("输入你的操作\n1.展示货物\n2.进货\n3.出货\n4.退出\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                show();
                break;
            case 2:
                add();
                break;
            case 3:
                delete();
                break;
            case 4:
                f = 1;
        }
    }
    fp = fopen("Inventory.dat","w");
    fwrite(&Count , sizeof(int) , 1 , fp);
    fwrite(list , sizeof(store) , Count , fp);
    fclose(fp);
    system("pause");
    return 0;
}