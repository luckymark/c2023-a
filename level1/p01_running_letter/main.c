#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 40
int main() {
    int i,j,k;
    char str[N];
    printf("请输入一个字符串:");
    gets(str);
    for(i=1;i<50;i++)
    {
        for(j=0;j<i;j++)
        {
            printf(" ");
        }
        printf("%s",str);
        Sleep(100);
        system("cls");
    }
    for(i=50;i>1;i--)
    {
        for(k=0;k<i;k++)
        {
            printf(" ");
        }
        printf("%s",str);
        Sleep(100);
        system("cls");
    }
    return 0;
}
