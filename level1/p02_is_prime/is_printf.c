//
// Created by 10275 on 2023/9/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void is_printf(){
    int i,k,f;
    scanf("%d",&i);
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
        printf("%d是素数\n",i);
    }
    else
    {
        printf("%d不是素数\n",i);
    }
    system("pause");
}

