#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int jiami(char x){
    x=(int)x;
    if(65<=x && x<=90)
    {
        x=(x-62)%26+65;
    }
    if(97<=x && x<=122)
    {
        x=(x-94)%26+97;
    }
    return x;
}
int jiemi(int x){
    if(65<=x && x<=90)
    {
        x=(x-68+26)%26+65;
    }
    if(97<=x && x<=122)
    {
        x=(x-100+26)%26+97;
    }
    return x;
}
int main(){
    char str[999];
    int i;
    scanf("%s",str);
    int list[strlen(str)];
    printf("原文:");
    for(i=0;i<strlen(str);i++)
    {
        printf("%c",str[i]);
    }
    printf("\n");
    for(i=0;i<strlen(str);i++)
    {
        list[i] = jiami(str[i]);
    }
    printf("密文:");
    for (i=0;i<sizeof(list)/4;i++)
    {
        printf("%c",list[i]);
    }
    printf("\n解密后:");
    for (i=0;i<sizeof(list)/4;i++)
    {
        list[i]=jiemi(list[i]);
    }
    for (i=0;i<sizeof(list)/4;i++)
    {
        printf("%c",list[i]);
    }
    system("pause");
    return 0;
}