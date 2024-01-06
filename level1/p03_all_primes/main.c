#include<stdio.h>
#include<time.h>
#include"isprime2.h"
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
        isprime(i);
    }

    last=clock();
    printf("ºÄÊ±%fms",(last-start)/CLOCKS_PER_SEC);
    return 0;
}
