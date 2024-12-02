#include <stdio.h>
#include <windows.h>
int main() {
    for(int i=1;i<=50;i++){
        for(int j=1;j<i;j++)printf(" ");
        printf("C");
        Sleep(100);
        system("cls");
    }

    for(int i=50;i;i--){
        for(int j=1;j<i;j++)printf(" ");
        printf("C");
        Sleep(100);
        system("cls");
    }
    system("pause");
}
