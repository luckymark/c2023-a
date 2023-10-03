//
// Created by ycm on 2023/9/26.
//
#include "math.h"
/*float sqrt(float x){
    float y = x;
    while(y*y<x){
        y = (y+x/y)*0.5;
    }
    return y;
}*/

char is_prime(int n){
    int sq = (int) sqrt(n)+1;
    if(n==2)return 1;
    for(int i=2;i<=sq;i++)if(n%i==0)return 0;
    return 1;
}