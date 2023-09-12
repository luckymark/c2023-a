#include<stdio.h>
int main(){
    int i,x;
    scanf("%d",&x);
    for(i=2;i<x;i++)
    {
        if(x%i==0)
        {
            break;
        }
    }
    if(i==x)
    {
        printf("是素数");
    }else
    {
        printf("不是素数");
    }

    return 0;
}
