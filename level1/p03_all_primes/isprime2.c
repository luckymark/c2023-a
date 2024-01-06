//
// Created by 86182 on 2023/9/26.
//
//
// Created by 86182 on 2023/9/26.
//
#include<stdio.h>
int isprime(int x)
{int ret=1;
    int i;
    for(i=3;i<x;i+=2){
        if(x%i==0){
            ret =0;
            break;
        }
    }
    if(ret){
        printf("%d\n",x);
    }
}