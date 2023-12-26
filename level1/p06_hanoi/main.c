#include <stdio.h>
#include <windows.h>
void move(char a,char b){
    printf("%c -> %c\n",a,b);
    return;
}
void hanoi(int n,char a,char b,char c){
    if(n==1){
        move(a,c);
        return;
    }
    hanoi(n-1,a,c,b);
    move(a,c);
    hanoi(n-1,b,a,c);
    return;
}
int main(){
    hanoi(64,'A','B','C');
    system("pause");
    return 0;//
}