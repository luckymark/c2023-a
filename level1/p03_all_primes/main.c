#include<stdio.h>
#include<time.h>
int main()
{
time_t start,last;
start=time(NULL);
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
    last=time(NULL);
    printf("耗时%f毫秒", difftime(last,start));
return 0;
}
