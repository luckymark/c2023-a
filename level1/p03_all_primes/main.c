#include<stdio.h>
#include<windows.h>
#include<time.h>
#define MAX 1001
int prime[500],isP[1020];
void Prime(){
    for(int i=1;i<=MAX;i++)isP[i]=1;
    int num=1;
    isP[1]=0,isP[2]=1;
    for(int i=2;i<=MAX;i++){
        if(isP[i]){
            prime[num++]=i;
            for(int j=2;j*i<=MAX;j++){
                isP[j*i]=0;
            }
        }
    }
}
int main() {
    Prime();
    for(int i=1;i<=1000;i++){
        if(isP[i])printf("%d ",i);
    }
    printf("\n");
    printf("所用时间:%.2lfs\n",(double)clock()/ CLOCKS_PER_SEC);
    system("pause");
}
