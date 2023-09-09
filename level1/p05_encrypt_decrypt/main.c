#include<stdio.h>
#include<string.h>
char a[5000],b[5000];
void encrypt(char* ma, char* mb)
{
    int num = strlen(ma);
    for(int i = 0; i < num; i++)
    {
        mb[i] = ma[i] + 10;
    }
}
void decrypt(char* ma, char* mb)
{
    int num = strlen(ma);
    for(int i = 0; i < num; i++)
    {
        mb[i] = ma[i] - 10;
    }
}
int main()
{
    scanf("%s",a);
    encrypt(a,b);
    printf("%s\n",b);
    decrypt(b,a);
    printf("%s\n",a);
    return 0;
}
