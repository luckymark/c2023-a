#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main(){
    int ts,te;
    ts=clock();
    int i,k,f;
    for(i=2;i<1001;i++)
    {
        f=0;
        for(k=2;k<sqrt(i)+1;k++)
        {
            if(i%k==0)
            {
                f=1;
            }
        }
        if(f==0)
        {
            printf("%d,",i);
        }
    }
    te=clock();
    printf("\nÓÃÊ±:%dºÁÃë",te-ts);
    system("pause");
    return 0;
}