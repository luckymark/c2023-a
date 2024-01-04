#include <stdio.h>
#include <time.h>
int primer(int);
int begintime,endtime;
int main()
{
    begintime=clock();
    int x=2;
    while(x<=1000)
    {
        if(primer(x)==1)
        {
        printf("%5d",x);
        }
        x++;
    }
    printf("\n");
    endtime=clock();
    printf("Time is %d ms",endtime-begintime);
    return 0;
}
int primer(int n)
{
    int k;
    for (int i=2;i<=n-1;i++)
    {
        if (n%i==0)
        {
            k=i;
            break;
        }
        else k=i;
    }
    if (k<n-1)
        n=0;
    else
        n=1;
    return n;
}