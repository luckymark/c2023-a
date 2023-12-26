#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
//*作墙， 作路，+作人，#作箱子,@表示终点
bool flag,flag1;
int dx,dy;
char m[8][11]={
        {'*','*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*',' ',' ',' ',' ',' ','*','*','*'},
        {'*','*','*','#','*','*','*',' ',' ',' ','*'},
        {'*','*',' ',' ',' ','#',' ',' ','#',' ','*'},
        {'*','*',' ','@','@','*',' ','#',' ','*','*'},
        {'*','*','*','@','@','*',' ',' ',' ','*','*'},
        {'*','*','*','*','*','*','*','*','*','*','*'},
};
//存箱子位置
int finx[5]={0,5,5,6,6};
int finy[5]={0,3,4,3,4};
void check_win(){
    int cnt=0;
    for(int i=1;i<=4;i++){
            if(m[finx[i]][finy[i]]=='#') cnt++;
    }
    if(cnt==4) flag1=false;
    return;
}
int check_fin(int x,int y){
    for(int i=1;i<=4;i++){
        if(finx[i]==x && finy[i]==y){
            return i;
        }
    }
    return -1;
}
void print(){
    for(int i=1;i<=7;i++){
        for(int j=1;j<=10;j++){
            printf("%c",m[i][j]);
        }
        printf("\n");
    }
}
void box_canmove(int x,int y,char d){
    flag=false;
    switch(d){
        case 75://left
        {
            if(m[x][y-1]=='*' || m[x][y-1]=='#'){
                return;
            }
            else{
                flag=true;
                return;
            }
        }
        case 77://right
        {
            if(m[x][y+1]=='*' || m[x][y+1]=='#'){
                return;
            }
            else{
                flag=true;
                return;
            }
        }
        case 72://up
        {
            if(m[x-1][y]=='*' || m[x-1][y]=='#'){
                return;
            }
            else{
                flag=true;
                return;
            }
        }
        case 80://down
        {
            if(m[x+1][y]=='*' || m[x+1][y]=='#'){
                return;
            }
            else{
                flag=true;
                return;
            }
        }
        default:
            return;
    }
    return;
}
void move(char x){
    switch(x) {
        case 75://左
        {
            if (m[dx][dy - 1] == '*') {
                return;
            }
            if(m[dx][dy-1]==' ' || m[dx][dy-1]=='@'){
                if(check_fin(dx,dy)==-1) {
                    m[dx][dy] = ' ';
                    dy--;
                    return;
                }
                else{
                    m[dx][dy]='@';
                    dy--;
                    return;
                }
            }
            if(m[dx][dy-1]=='#'){
                box_canmove(dx,dy-1,x);
                if(!flag) return;
                else{
                    m[dx][dy]=' ';
                    m[dx][dy-2]='#';
                    dy--;
                    //check_win();
                    return;
                }
            }
        }
        case 77://右
        {
            if (m[dx][dy + 1] == '*') {
                return;
            }
            if(m[dx][dy+1]==' ' || m[dx][dy+1]=='@'){
                if(check_fin(dx,dy)==-1) {
                    m[dx][dy] = ' ';
                    dy++;
                    return;
                }
                else{
                    m[dx][dy]='@';
                    dy++;
                    return;
                }
            }
            if(m[dx][dy+1]=='#'){
                box_canmove(dx,dy+1,x);
                if(!flag) return;
                else{
                    m[dx][dy]=' ';
                    m[dx][dy+2]='#';
                    dy++;
                    //check_win();
                    return;
                }
            }
        }
        case 72://上
        {
            if (m[dx-1][dy] == '*') {
                return;
            }
            if(m[dx-1][dy]==' ' || m[dx-1][dy]=='@'){
                if(check_fin(dx,dy)==-1) {
                    m[dx][dy] = ' ';
                    dx--;
                    return;
                }
                else{
                    m[dx][dy]='@';
                    dx--;
                    return;
                }
            }
            if(m[dx-1][dy]=='#'){
                box_canmove(dx-1,dy,x);
                if(!flag) return;
                else{
                    m[dx][dy]=' ';
                    m[dx-2][dy]='#';
                    dx--;
                    //check_win();
                    return;
                }
            }
        }
        case 80://下
        {
            if (m[dx+1][dy] == '*') {
                return;
            }
            if(m[dx+1][dy]==' ' || m[dx+1][dy]=='@'){
                if(check_fin(dx,dy)==-1) {
                    m[dx][dy] = ' ';
                    dx++;
                    return;
                }
                else{
                    m[dx][dy]='@';
                    dx++;
                    return;
                }
            }
            if(m[dx+1][dy]=='#'){
                box_canmove(dx+1,dy,x);
                if(!flag) return;
                else{
                    m[dx][dy]=' ';
                    m[dx+2][dy]='#';
                    dx++;
                    //check_win();
                    return;
                }
            }
        }
        default: {
            break;
        }
    }
    return;
}
int main() {
    dx=4;
    dy=3;
    m[4][3]='+';
    print();
    flag1=true;
    while(flag1){
        move(getch());
        m[dx][dy]='+';
        check_win();
        system("cls");
        print();
    }
    system("cls");
    printf("You Win!");
    system("pause");
    return 0;
}