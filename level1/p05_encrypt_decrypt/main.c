#include <stdio.h>
#include <string.h>
void encrypt();
void decrypt();
int main()
{
    printf("Input 1 to Encrypt or input 2 to decrypt.\n");
    int x;
    scanf("%d",&x);
    if (x==1)
        encrypt();
    else
        decrypt();
    return 0;
}
void encrypt()
{
    char origin[30];
    printf("Enter the original contents.\n");
    scanf("%s",origin);
    for(int i=0;i<=strlen(origin)-1;i++)
    {
        origin[i]=origin[i]+3;
    }
    printf("%s",origin);
}
void decrypt()
{
    char code[30];
    printf("Enter the code.\n");
    scanf("%s",code);
    for(int i=0;i<=strlen(code)-1;i++)
    {
        code[i]=code[i]-3;
    }
    printf("%s",code);
}