#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
typedef struct
{
    int S,M,L,XL;
}size;
typedef struct
{
    size Size;
}Goods;
Goods Shirt={{0,0,0,0}};
Goods Coat={{0,0,0,0}};
Goods Sweater={{0,0,0,0}};
void Print_data(FILE *fp);
void Show_List(FILE *fp);
void Save_variables(FILE *var);
void Put_in_Storage();
void Deliver_from_storage();
int main()
{
    while (1)
    {
        FILE *fp=fopen("Storage List.txt","r+");
        FILE *var=fopen("Amount.txt","r+");
        fscanf(var,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
               &Shirt.Size.S,&Shirt.Size.M,&Shirt.Size.L,&Shirt.Size.XL,
               &Coat.Size.S,&Coat.Size.M,&Coat.Size.L,&Coat.Size.XL,
               &Sweater.Size.S,&Sweater.Size.M,&Sweater.Size.L,&Sweater.Size.XL);
        printf("What do you want to do?\n");
        printf("1.Show the store list.\n");
        printf("2.Put in storage.\n");
        printf("3.Deliver from storage.\n");
        printf("4.Exit.\n");
        switch (getch())
        {
            case '1':
            {
                Show_List(fp);
                break;
            }
            case '2':
            {
                Put_in_Storage();
                Print_data(fp);
                FILE *var=fopen("Amount.txt","w");
                Save_variables(var);
                break;
            }
            case '3':
            {
                Deliver_from_storage();
                Print_data(fp);
                FILE *var=fopen("Amount.txt","w");
                Save_variables(var);
                break;
            }
            case '4':
            {
                exit(0);
                break;
            }
            default:
                break;
        }
        getch();
        system("cls");
    }
}
void Show_List(FILE *fp)
{
    system("cls");
    int ch;
    while((ch=getc(fp))!=EOF)
    {
        putchar(ch);
    }
    printf("\nPress Enter to go back.\n");
}
void Print_data(FILE *fp)
{
    fprintf(fp,"Shirt:\n"
               "{\n"
               "S:%d\n"
               "M:%d\n"
               "L:%d\n"
               "XL:%d\n"
               "}\n"
               "\n"
               "Coat:\n"
               "{\n"
               "S:%d\n"
               "M:%d\n"
               "L:%d\n"
               "XL:%d\n"
               "}\n"
               "\n"
               "Sweater:\n"
               "{\n"
               "S:%d\n"
               "M:%d\n"
               "L:%d\n"
               "XL:%d\n"
               "}\n",
               Shirt.Size.S,Shirt.Size.M,Shirt.Size.L,Shirt.Size.XL,
               Coat.Size.S,Coat.Size.M,Coat.Size.L,Coat.Size.XL,
               Sweater.Size.S,Sweater.Size.M,Sweater.Size.L,Sweater.Size.XL);
    fclose(fp);
}
void Save_variables(FILE *var)
{
    fprintf(var,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
            Shirt.Size.S,Shirt.Size.M,Shirt.Size.L,Shirt.Size.XL,
            Coat.Size.S,Coat.Size.M,Coat.Size.L,Coat.Size.XL,
            Sweater.Size.S,Sweater.Size.M,Sweater.Size.L,Sweater.Size.XL);
    fclose(var);
}
void Put_in_Storage()
{
    system("cls");
    printf("Choose the category.\n");
    printf("1.Shirt\n");
    printf("2.Coat\n");
    printf("3.Sweater\n");
    switch (getch())
    {
        case '1':
        {
            system("cls");
            printf("Choose the size.\n");
            printf("1.S\n");
            printf("2.M\n");
            printf("3.L\n");
            printf("4.XL\n");
            switch (getch())
            {
                case '1':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Shirt.Size.S+=i;
                    break;
                }
                case '2':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Shirt.Size.M+=i;
                    break;
                }
                case '3':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Shirt.Size.L+=i;
                    break;
                }
                case '4':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Shirt.Size.XL+=i;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case '2':
        {
            system("cls");
            printf("Choose the size.\n");
            printf("1.S\n");
            printf("2.M\n");
            printf("3.L\n");
            printf("4.XL\n");
            switch (getch())
            {
                case '1':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Coat.Size.S+=i;
                    break;
                }
                case '2':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Coat.Size.M+=i;
                    break;
                }
                case '3':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Coat.Size.L+=i;
                    break;
                }
                case '4':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Coat.Size.XL+=i;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case '3':
        {
            system("cls");
            printf("Choose the size.\n");
            printf("1.S\n");
            printf("2.M\n");
            printf("3.L\n");
            printf("4.XL\n");
            switch (getch())
            {
                case '1':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Sweater.Size.S+=i;
                    break;
                }
                case '2':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Sweater.Size.M+=i;
                    break;
                }
                case '3':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Sweater.Size.L+=i;
                    break;
                }
                case '4':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Sweater.Size.XL+=i;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    system("cls");
    printf("Done!\n");
    printf("Press Enter to go back.\n");
}
void Deliver_from_storage()
{
    system("cls");
    printf("Choose the category.\n");
    printf("1.Shirt\n");
    printf("2.Coat\n");
    printf("3.Sweater\n");
    switch (getch())
    {
        case '1':
        {
            system("cls");
            printf("Choose the size.\n");
            printf("1.S\n");
            printf("2.M\n");
            printf("3.L\n");
            printf("4.XL\n");
            switch (getch())
            {
                case '1':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Shirt.Size.S-=i;
                    break;
                }
                case '2':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Shirt.Size.M-=i;
                    break;
                }
                case '3':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Shirt.Size.L-=i;
                    break;
                }
                case '4':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Shirt.Size.XL-=i;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case '2':
        {
            system("cls");
            printf("Choose the size.\n");
            printf("1.S\n");
            printf("2.M\n");
            printf("3.L\n");
            printf("4.XL\n");
            switch (getch())
            {
                case '1':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Coat.Size.S-=i;
                    break;
                }
                case '2':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Coat.Size.M-=i;
                    break;
                }
                case '3':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Coat.Size.L-=i;
                    break;
                }
                case '4':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Coat.Size.XL-=i;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case '3':
        {
            system("cls");
            printf("Choose the size.\n");
            printf("1.S\n");
            printf("2.M\n");
            printf("3.L\n");
            printf("4.XL\n");
            switch (getch())
            {
                case '1':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Sweater.Size.S-=i;
                    break;
                }
                case '2':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Sweater.Size.M-=i;
                    break;
                }
                case '3':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Sweater.Size.L-=i;
                    break;
                }
                case '4':
                {
                    system("cls");
                    printf("Enter the number.\n");
                    int i;
                    scanf("%d",&i);
                    Sweater.Size.XL-=i;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    system("cls");
    printf("Done!\n");
    printf("Press Enter to go back.\n");
}
