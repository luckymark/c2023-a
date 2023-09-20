#include<stdio.h>
#include<time.h>

int main()
{
    double start,last;
    start=clock();
    int first=3;
    int end=1000;
    int i,j;
    printf("2\n");
    for(i=first;i<end;i+=2)
    {
        int x=i;
        for(j=3;j<x;j+=2)
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
    printf("耗时%fms",(last-start)/CLOCKS_PER_SEC);
    return 0;
}

