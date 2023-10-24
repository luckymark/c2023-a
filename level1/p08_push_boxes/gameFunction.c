#include <stdio.h>
#include <conio.h>
#include "shellControl.h"

typedef struct{
    int x;
    int y;
} point;

enum direction{Up,Down,Left,Right};

void setmap(char (*walls)[10],const point *player,point target[],int targets){

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            gotoxy(2 * j,i);
            switch( *(walls[i]+j) ){
                case (char)1:printf("■");break;
                case (char)2:printf("□");break;
                default:break;
            }
        }
    }

    for(int i = 0; i < targets; i++){
        if(*(walls[target[i].y]+target[i].x) == (char)0){
            gotoxy(2*target[i].x,target[i].y);
            printf("×");
        }
    }

    gotoxy(2*player->x,player->y);
    printf("♀");
}

void playermove(char (*walls)[10],point *player,enum direction a){
    point next,next2;
    next2.y = next.y = player->y;
    next2.x = next.x = player->x;
    switch (a){
        case Up: next.y--;next2.y-=2;break;
        case Down: next.y++;next2.y+=2;break;
        case Left: next.x--;next2.x-=2;break;
        case Right: next.x++;next2.x+=2;break;
        default: break;
    }

    if (*(walls[next.y]+next.x) == (char)1){
        return;
    }

    if (*(walls[next.y]+next.x) == (char)0 || *(walls[next.y]+next.x) == (char)-2){
        gotoxy(2*player->x,player->y);
        printf(" ");
        player->x = next.x;
        player->y = next.y;
        return;
    }

    if (*(walls[next.y]+next.x) == (char)2){
        if(*(walls[next2.y]+next2.x)==(char)1 || *(walls[next2.y]+next2.x)==(char)2){
            return;
        } else{
            *(walls[next2.y]+next2.x) = (char)2;
            *(walls[next.y]+next.x) = (char)0;

            gotoxy(2*player->x,player->y);
            printf(" ");
            player->x = next.x;
            player->y = next.y;
            return;

        }
    }

}

int allBack(char (*walls)[10],point target[],int targets){
    int allBack = 1;
    for(int i = 0; i < targets; i++){
        if(*(walls[target[i].y]+target[i].x) != (char)2){
            allBack = 0;
        }
    }
    return allBack;
};
void gameover(int step){
    gotoxy(27,2);
    printf("Steps:%d",step);
    gotoxy(27,4);
    printf("Success!");
    gotoxy(2*13,5);
    printf("Game  Over");
    getch();
}