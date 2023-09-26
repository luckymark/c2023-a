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
    int flag=0;
    for(int num=6;num<=100;num++){
        flag=0;
        for(int j=2;j<=num-4 && !flag;j++){
            for(int k=2;k<=num-4 && !flag;k++){
                int l=num-j-k;
                if(isP[j]+isP[k]+isP[l]==3){
                    printf("%d=%d+%d+%d\n",num,j,k,l);
                    flag=1;
                }
            }
        }
    }
    system("pause");
}
