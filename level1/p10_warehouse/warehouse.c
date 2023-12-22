#include "warehouse.h"
void Display_list(FILE* warehouse)
{
    int ch;
    while(1)
    {
        ch=fgetc(warehouse);
        if(ch==EOF)
            break;
        putchar(ch);
    }
}
int read(FILE* warehouse,int num)
{
    int ch,i=0;
    while(1)
    {
        ch = fgetc(warehouse);
        if (ch == EOF)
            break;
        if(ch=='#')
            i++;
        if (i == num)
        {
            char str[4];
            ch = fgetc(warehouse);
            str[0]=ch;
            ch = fgetc(warehouse);
            str[1]=ch;
            ch = fgetc(warehouse);
            str[2]=ch;
            return atoi(str);
        }
    }
}
void update(FILE* warehouse,int num,int n)
{
    int ch,i=0;
    while(1)
    {
        ch = fgetc(warehouse);
        if (ch == EOF)
            break;
        if(ch=='#')
            i++;
        if (i == num)
        {
            long int flag=ftell(warehouse);
            char str[4];
            itoa(n, str, 10);
            fseek(warehouse,flag,0);
            fputc(' ',warehouse);
            fputc(' ',warehouse);
            fputc(' ',warehouse);
            fseek(warehouse,flag,0);
            fputs(str, warehouse);
            return;
        }
    }
}
void menu()
{
    printf("Please choose:\n");
    printf("1.Inventory list\n2.Put into\n3.Take out\n");
    printf("4.Exit\n");

}