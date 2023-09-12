#include<stdio.h>
#include<math.h>
#include<windows.h>
int Prime(){
    int a;
    printf("请输入一个数:");
    scanf("%d",&a);
    int k=sqrt(a);
    k++;
    if(a==1){
        printf("这不是一个素数\n");
        return 0;
    }
    if(a==2){
        printf("这是一个prime\n");
        return 0;
    }
    for(int i=2;i<=k;i++){
        if( !(a%i) ){
            printf("这不是一个素数\n");
            return 0;
        }
    }
    printf("这是一个prime\n");
}
int main() {
    Prime();
    system("pause");
}
