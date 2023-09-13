#include<stdio.h>
int main()
{
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
return 0;
    }
