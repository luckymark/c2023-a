#include<stdio.h>
#include<math.h>
#include<windows.h>
int Prime(){
    int a;
    printf("������һ����:");
    scanf("%d",&a);
    int k=sqrt(a);
    k++;
    if(a==1){
        printf("�ⲻ��һ������\n");
        return 0;
    }
    if(a==2){
        printf("����һ��prime\n");
        return 0;
    }
    for(int i=2;i<=k;i++){
        if( !(a%i) ){
            printf("�ⲻ��һ������\n");
            return 0;
        }
    }
    printf("����һ��prime\n");
}
int main() {
    Prime();
    system("pause");
}
