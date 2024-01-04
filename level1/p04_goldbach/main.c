#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int kg(int x){
    int k,f=0;
    for(k=2;k<sqrt(x)+1;k++)
    {
        if(x%k==0)
        {
            f=1;
        }
    }
    if(x==1)
    {
        f=0;
    }
    return f;
}
int main(){
    int i,num,j,F=0;
    scanf("%d",&num);
    for(i=2;i<=num;i+=2)
    {
        for(j=1;j<=i/2;j++)
        {
            if (kg(j) == 0 && kg(i-j) == 0)
            {
                break;
            }
        }
        if(j==i/2+1)
        {
            F=1;
            break;
        }
    }
    if(F==1)
    {
        printf("´íÎó\n");
    }
    else
    {
        printf("ÕýÈ·\n");
    }
    system("pause");
    return 0;
}