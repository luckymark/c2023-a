#include <stdio.h>
#include <windows.h>
#include <conio.h>

//请生成可执行文件，用Windows的终端运行，勿用Clion的内置终端运行。
//采用的编码格式：GBK。
typedef struct{
    int x;
    int y;
} point;

enum direction{Up,Down,Left,Right};
void gotoxy(int x, int y);
void playermove(char (*walls)[10],point *player,enum direction a);
void setmap(char (*walls)[10],const point *player,const point *exit);
void gameover();

int main(){
    point player={2,9};
    point exit={3,0};
    char walls[10][10]={{1,1,1,1,1,1,1,1,1,1},
                        {1,0,0,0,0,1,0,0,0,1},
                        {1,0,1,1,1,1,0,1,0,1},
                        {1,0,0,0,0,0,0,1,0,1},
                        {1,1,1,1,1,0,1,1,1,1},
                        {1,0,0,0,1,0,0,0,0,1},
                        {1,0,1,1,1,1,1,0,1,1},
                        {1,0,1,0,0,0,0,0,0,1},
                        {1,0,0,0,1,1,1,1,1,1},
                        {1,1,1,1,1,1,1,1,1,1},
    };
    while (exit.x != player.x || exit.y != player.y){
        setmap(&walls,&player,&exit);
        int input = getch();
        switch(input){
            case 'W': playermove(&walls,&player,Up);break;
            case 'w': playermove(&walls,&player,Up);break;
            case 'S': playermove(&walls,&player,Down);break;
            case 's': playermove(&walls,&player,Down);break;
            case 'A': playermove(&walls,&player,Left);break;
            case 'a': playermove(&walls,&player,Left);break;
            case 'D': playermove(&walls,&player,Right);break;
            case 'd': playermove(&walls,&player,Right);break;
            default: break;
        }
    }
    gameover();
    return 0;
}

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord);
}

void setmap(char (*walls)[10],const point *player,const point *exit){

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if( *(walls[i]+j) == (char)1 ){
                gotoxy(2 * j,i);
                printf("■");
            }
        }
    }

    *(walls[exit->y]+exit->x) = (char)0;
    *(walls[player->y]+player->x) = (char)0;
    gotoxy(2*exit->x,exit->y);
    printf(" ");
    gotoxy(2*player->x,player->y);
    printf("◆");
}

void playermove(char (*walls)[10],point *player,enum direction a){
    point next;
    next.y = player->y;
    next.x = player->x;
    switch (a){
        case Up: next.y--;break;
        case Down: next.y++;break;
        case Left: next.x--;break;
        case Right: next.x++;break;
        default: break;
    }

    int collision = 0;

    if (*(walls[next.y]+next.x) == (char)1){
        collision = 1;
    }
    if (next.y > 9 || next.x > 9 || next.y < 0 || next.x < 0){
        collision = 1;
    }

    if (collision){
        return;
    }
    else{
        gotoxy(2*player->x,player->y);
        printf(" ");
        player->x = next.x;
        player->y = next.y;
    }
}

void gameover(){
    gotoxy(2*13,5);
    printf("Game  Over");
    gotoxy(27,4);
    printf("Success!");
    getch();
}