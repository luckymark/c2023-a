//
// Created by taiyehu on 2023/9/26.
#include <stdbool.h>
bool prime(int n){
    bool flag=true;
    //scanf("%d",&n);
    for (int i=2;i*i<=n;i++){
        if(n%i==0){
            flag=false;
            break;
        }
    }
    if(flag==true) return true;
    else return false;
}