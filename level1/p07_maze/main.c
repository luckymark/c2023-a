#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
HANDLE out;
int maze[40][40],footprint[40][40],game=0;
struct foorward{
    int x,y;
}way[4];
void setcursor(int x,int y){
    SetConsoleCursorPosition( out , (COORD){x,y} );
}
void explanation(){
    setcursor(45,5),printf("迷宫游戏");
    setcursor(35,7),printf("请通过方向键移动‘A’,使其到达终点'6'");
    setcursor(0,0);
}
int barrier(int x,int y){
    if( (x*y)<=0 || x>25 || y>25 || footprint[x][y] )return 1;
    return 0;
}
void mazestruct(int x,int y);
void step(int x,int y){
    int a;// 0左 1上 2右 3下
    while(1){
        a=rand()%4;
        if( !barrier( x+way[a].x , y+way[a].y) )break;
    }
    maze[(x+x+way[a].x)/2][(y+y+way[a].y)/2]=0;
    mazestruct(x+way[a].x,y+way[a].y);
}
int flag=0;
void mazestruct(int x,int y){
    footprint[x][y]=1;
    if( barrier(x-2,y) && barrier(x+2,y) && barrier(x,y+2) && barrier(x,y-2) ){
        flag=1;
        return ;
    }
    step(x,y);
    if(flag){
        if( barrier(x-2,y) && barrier(x+2,y) && barrier(x,y+2) && barrier(x,y-2) )return ;
        flag--;
        step(x,y);
    }
}
void mazemake(){
    way[0].x=-2,way[0].y=0,way[1].x=0,way[1].y=-2;
    way[2].x=2,way[2].y=0,way[3].x=0,way[3].y=2;
    for(int i=0;i<=26;i++)
        for(int j=0;j<=26;j++)
            maze[i][j]=1,footprint[i][j]=0;
    for(int i=1;i<=25;i+=2)
        for(int j=1;j<=25;j+=2)
            maze[i][j]=0;
    maze[25][25]=2;
    srand( (unsigned)time(NULL) );
    mazestruct(1,1);
    for(int j=0;j<=26;j++){
        for(int i=0;i<=26;i++){
            if(maze[i][j]==1)printf("#");
            if(maze[i][j]==0)printf(" ");
            if(maze[i][j]==2)printf("6");
        }
        printf("\n");
    }
    maze[25][25]=0;
}
int movecheck(COORD k,int key){//左 75 上 72 右 77 下 80
    if(key==75 && maze[k.X-1][k.Y])return 0;
    if(key==72 && maze[k.X][k.Y-1])return 0;
    if(key==77 && maze[k.X+1][k.Y])return 0;
    if(key==80 && maze[k.X][k.Y+1])return 0;
    return 1;
}
void move( COORD *k , int key ){
    if(key==75)k->X--;
    if(key==72)k->Y--;
    if(key==77)k->X++;
    if(key==80)k->Y++;
    SetConsoleCursorPosition(out,*k);
    printf("A");
    if(k->X==25 && k->Y==25)game=1;
}
void gamerun(){
    setcursor(1,1);printf("A");
    COORD A={1,1};
    while(1){
        if(kbhit()){
            int key=getch();
            if( movecheck(A,key) ){
                setcursor(A.X,A.Y);printf(" ");
                move(&A,key);
            }
        }
        if(game){
            system("cls");
            printf("你赢啦!\n 按任意键继续游戏");
            char ch=getchar();
            return ;
        }
    }
}
int main(){
    while(1){
        game=0;
        out= GetStdHandle(STD_OUTPUT_HANDLE);
        explanation();
        mazemake();
        gamerun();
    }

}
