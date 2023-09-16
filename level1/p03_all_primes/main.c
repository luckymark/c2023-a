#include<stdio.h>
#include<time.h>
int main()
{
int start,last;
start=clock();
int first=2;
int end=1000;
int i,j;
for(i=first;i<end;i++)
{
    int x=i;
    for(j=2;j<x;j++)
    {
        if(x%j==0)
        {

            break;
        }
    }
    if(j==x)
    {
        printf("%d\n",j);
    }
}
    last=clock();
    printf("耗时%d毫秒",last-start);
return 0;
}
