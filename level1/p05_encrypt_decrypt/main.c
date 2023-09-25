#include<stdio.h>
#include<string.h>
#define N 52
void encode(char str[N],int n);
void decode(char str[N],int n);
int main()
{
char str[N];
int n;
printf("请输入一个字符串:");
gets(str);
printf("请输入要移位的数字密钥:");
scanf("%d",&n);
encode(str,n);
        printf("加密后的密文：%s\n",str);
decode(str,n);
printf("解密后的明文：%s",str);
             return 0;
}
void encode(char str[N],int n)
{int i;
    for(i=0;i<strlen(str);i++)
    {
        str[i]+=n;
        if(str[i]>'z'||str[i]>"Z")
        str[i]-=26;
    }
}
void decode(char str[N],int n)
{int i;
    for(i=0;i<strlen(str);i++)
    {
        str[i]-=n;
        if(str[i]>'z'||str[i]>"Z")
        str[i]-=26;
    }
}
