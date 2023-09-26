//
// Created by 86182 on 2023/9/26.
//
int isprime(int x)
{int ret=1;
    int i;
    for(i=3;i<x;i++){
        if(x%i==0){
            ret =0;
            break;
        }
    }
    return ret;
}