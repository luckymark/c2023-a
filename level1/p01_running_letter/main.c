#include<stdio.h>
#include<windows.h>
int main(){
    int a=0;//
    while(a<=80){
        system("cls");
        int b=1;
        while(b<=a){
            printf(" ");
            b++;
        }
        printf("字母");
        Sleep(5);
        a++;
    }
    a=0;
    while(a<=80){
        system("cls");
        int b=80;
        while(b>=a){
            printf(" ");
            b--;
        }
        printf("母字");
        Sleep(5);
        a++;
    }
    system("pause");
    return 0;
}