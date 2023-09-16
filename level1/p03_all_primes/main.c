#include<stdio.h>
#include<time.h>
#include<windows.h>
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
    Sleep(10);
    last=clock();
    printf("%dms", last-start);
    return 0;
}