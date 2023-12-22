#include "warehouse.h"
int main()
{
    while(1)
    {
        int input;
        menu();
        scanf("%d", &input);
        if(input==1)
        {
            FILE* warehouse=fopen("C:\\c2023-a\\level1\\p10_warehouse\\warehouse.txt","r");
            if(warehouse!=NULL)
            {
                Display_list(warehouse);
                printf("\n\n");
            }
            else
                printf("The file can't be opened");
            fclose(warehouse);
        }
        else if(input==2)
        {
            int num,a;
            FILE* warehouse=fopen("C:\\c2023-a\\level1\\p10_warehouse\\warehouse.txt","r");
            printf("Please choose the num of drink:\n");
            scanf("%d",&num);
            while(num>8||num<1)
            {
                printf("\nERROR\n");
                printf("Please re-input\n");
                scanf("%d",&num);
            }
            printf("How many drinks do you want to put into?\n");
            scanf("%d",&a);
            int n=read(warehouse,num);
            n=n+a;
            fclose(warehouse);
            warehouse=fopen("C:\\c2023-a\\level1\\p10_warehouse\\warehouse.txt","r+");
            update(warehouse,num,n);
            fclose(warehouse);
            printf("\n");
        }
        else if(input==3)
        {
            int num,a;
            FILE* warehouse=fopen("C:\\c2023-a\\level1\\p10_warehouse\\warehouse.txt","r");
            printf("Please choose the num of drink:\n");
            scanf("%d",&num);
            while(num>8||num<1)
            {
                printf("\nERROR\n");
                printf("Please re-input\n");
                scanf("%d",&num);
            }
            printf("How many drinks do you want to take out?\n");
            scanf("%d",&a);
            int n=read(warehouse,num);
            n=n-a;
            fclose(warehouse);
            warehouse=fopen("C:\\c2023-a\\level1\\p10_warehouse\\warehouse.txt","r+");
            update(warehouse,num,n);
            fclose(warehouse);
            printf("\n");
        }
        else if(input==4)
        {
            break;
        }
        else
        {
            printf("\nERROR\nPlease re-input\n\n");
        }
    }
    return 0;
}