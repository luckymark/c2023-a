//用‘+’作墙，用*作玩家
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
int dx,dy,cnt=0,n;
int px[5]={0,0,1,0,-1};
int py[5]={0,1,0,-1,0};
bool flag=true;
int wx[11111];
int wy[11111];
int nx[111][111];//1是墙,2是未被连接的节点,0是被破开的墙,3是被连接的节点
int jx[111][111];
bool fx[111][111];
char m[111][111];
/*={
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','*','*','*','*','*','*','*','*','*','*'},
        {' ','*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
        {' ','*','*','*','*',' ','*','*','*','*','*'},
        {'*','*',' ','*','*',' ','*',' ',' ',' ','*'},
        {'*','*',' ','*','*',' ',' ',' ',' ',' ','*'},
        {' ','*',' ','*','*',' ','*','*','*',' ','*'},
        {' ','*',' ',' ',' ',' ',' ',' ','*',' ','*'},
        {' ','*','*','*','*',' ','*','*','*',' ','*'},
        {' ','*',' ',' ',' ',' ','*',' ',' ',' ','*'},
        {' ','*','*','*','*','*','*','*','*','$','*'}


        {'*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','*',' ','*',' ','*',' ','*',' ','*',' ','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','*',' ','*',' ','*',' ','*',' ','*',' ','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','*',' ','*',' ','*',' ','*',' ','*',' ','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','*',' ','*',' ','*',' ','*',' ','*',' ','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','*',' ','*',' ','*',' ','*',' ','*',' ','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*'}
}*/
void init(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            jx[i][j]=20001;
            if(i%2==0 && j%2==0){
                m[i][j]=' ';
            }
            else{
                m[i][j]='*';
            }
            //printf("%c",m[i][j]);
        }
        //printf("\n");
    }
    /*for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) printf("%c",m[i][j]);
        printf("\n");
    }*/
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) {
            if(m[i][j]=='*'){
                nx[i][j]=1;
                jx[i][j]=-1;
            }
            else{
                nx[i][j]=2;
            }
        }
    }
    return;
}
void search(int x,int y){
    int tmp=0;
    for(int i=1;i<=4;i++){
        if(nx[x+px[i]][y+py[i]]==2){
            tmp++;
            dx=x+px[i];
            dy=y+py[i];
        }
        if(nx[x+px[i]][y+py[i]]==0){
            return;
        }
    }
    if(tmp==1){
        nx[dx][dy]=3;
        flag=true;
    }
    return;
}
void dig(int x,int y){
    if(x==1 || y==1 || x==n || y==n ) return;
    //srand((unsigned)time(0));
    int r=rand()%4;
    int t=rand()%2;
    //把墙放进栈
    if(t==0) {
        for (int i = 1; i <= 4; i++) {
            //int r=rand()%4;
            //int t=rand()%2;
            int way = (i + r) % 4 + 1;
            if (x + px[way] == 1 || y + py[way] == 1 || x + px[way] == n || y + py[way] == n) {
                continue;
            }
            if (nx[x + px[way]][y + py[way]] != 1) {
                continue;
            }
            wx[++cnt] = x + px[way];
            wy[cnt] = y + py[way];
        }
    }
    else{
        for (int i = 4; i >= 1; i--) {
            //int r=rand()%4;
            //int t=rand()%2;
            int way = (i + r) % 4 + 1;
            if (x + px[way] == 1 || y + py[way] == 1 || x + px[way] == n || y + py[way] == n) {
                continue;
            }
            if (nx[x + px[way]][y + py[way]] != 1) {
                continue;
            }
            wx[++cnt] = x + px[way];
            wy[cnt] = y + py[way];
        }
    }
    while(cnt>0){
        int wayx=wx[cnt];
        int wayy=wy[cnt];
        cnt--;
        flag=false;
        search(wayx,wayy);
        if(flag){
            m[wayx][wayy]=' ';
            nx[wayx][wayy]=0;
            dig(dx,dy);
            return;
        }
    }
}
void move(char x){
    switch(x) {
        case 75://左
        {
            if(m[dx][dy-1]=='$'){
                m[dx][dy]=' ';
                flag=false;
                break;
            }
            if (m[dx][dy - 1] == '*') {
                break;
            } else {
                m[dx][dy]=' ';
                dy--;
                break;
            }
        }
        case 77://右
        {
            if(m[dx][dy+1]=='$'){
                m[dx][dy]=' ';
                flag=false;
                break;
            }
            if (m[dx][dy + 1] == '*') {
                break;
            } else {
                m[dx][dy]=' ';
                dy++;
                break;
            }
        }
        case 72://上
        {
            if(m[dx-1][dy]=='$'){
                m[dx][dy]=' ';
                flag=false;
                break;
            }
            if (m[dx - 1][dy] == '*') {
                break;
            } else {
                m[dx][dy]=' ';
                dx--;
                break;
            }
        }
        case 80://下
        {
            if(m[dx+1][dy]=='$'){
                m[dx][dy]=' ';
                flag=false;
                break;
            }
            if (m[dx + 1][dy] == '*') {
                break;
            } else {
                m[dx][dy]=' ';
                dx++;
                break;
            }
        }
        default: {
            break;
        }
    }
    return;
}
/*void gotoxy(int x,int y){
    COORD pos={x,y};
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout,pos);
}*/
void print(){
    /*for(int i=1;i<=10;i++){
        if(i==1 || i==10) for(int j=1;j<=10;j++) m[i][j]='*';
        else {
            m[i][1]='*';
            m[i][10]='*';
        }
    }*/
    for(int i=1;i<=n;i++) {
        for (int j = 1; j <= n; j++){
            printf("%c", m[i][j]);
        }
        printf("\n");
    }
    return;
}
void finale(int x,int y,int step){
    if(nx[x][y]==1 || fx[x][y]){
        return;
    }
    jx[x][y]=min(step,jx[x][y]);
    for(int i=1;i<=4;i++){
        int wayx=x+px[i];
        int wayy=y+py[i];
        fx[x][y]=true;
        finale(wayx,wayy,step+1);
    }
    fx[x][y]=false;
    return;
}
int main() {
    printf("size:");
    scanf("%d",&n);
    init();
    //print();
    nx[2][2]=3;
    dig(2,2);
    m[2][2]='+';
    dx=2;
    dy=2;
    finale(2,2,0);
    int temp=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(temp<jx[i][j]){
                temp=jx[i][j];
                dx=i;
                dy=j;
            }
        }
    }
    m[dx][dy]='$';
    print();
    /*for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d",nx[i][j]);
        }
        printf("\n");
    }*/
    flag=true;
    dx=2;
    dy=2;
    while(flag) {
        move(getch());
        m[dx][dy]='+';
        system("cls");
        print();
    }
    for(int i=1;i<=3;i++){
        Sleep(20);
        system("cls");
        print();
    }
    system("cls");
    printf("you win");
    system("pause");
    return 0;
}