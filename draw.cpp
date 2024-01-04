//
// Created by taiyehu on 2023/12/25.
//
#include "GameTree.h"
#include <raylib.h>
#include "play.h"
void draw(int (&Board)[15][15]){
    int pointx[15],pointy[15];
    for(int i=1;i<=15;i++) pointx[i-1]=40*i-20;
    for(int j=1;j<=15;j++) pointy[j-1]=40*j-20;
    int x=pointx[7],y=pointy[7];
    int dx,dy,fx,fy;
    int color=2;
    Color c;
    int flag=1;//1为电脑回合(黑棋)
    int r1=1;
    InitWindow(600,600,"");
    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(60);
    Image imgBackground=GenImageColor(600,600,BROWN);
    for(int i=20;i<=580;i+=40) {
        ImageDrawLine(&imgBackground, i, 0, i, 600, BLACK);
        ImageDrawLine(&imgBackground, 0, i, 600, i, BLACK);
    }
    while(!WindowShouldClose()) {
        /*if(r1==1){
            gt.game();
            Board[7][7]=2;
            r1=0;
        }*/
        if(flag==4) {
            if(dx==-1 && dy==-1) imgBackground=GenImageColor(600,600,WHITE);
            if(dx==-2 && dy==-2) imgBackground=GenImageColor(600,600,BLACK);

        }
        if(flag==0) {
            flag=2;
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                fx=x;
                fy=y;
                dx = GetMouseX() / 40;
                dy = GetMouseY() / 40;
                x = pointx[dx];
                y = pointy[dy];
                color = 1;
                flag = 3;
                Board[dx][dy]=1;
            }
        }
        if(flag==1){
            GameTree gt=GameTree(9,2,Board);
            pair<int,int> pos=play(gt,Board);
            dx=pos.first;
            dy=pos.second;
            if(dx<0 && dy<0){
                flag=4;
                continue;
            }
            x = pointx[dx];
            y = pointy[dy];
            color=2;
            flag=2;
            //flagp=1;
        }
        /*if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            x=pointx[GetMouseX()/40];
            y=pointy[GetMouseY()/40];
            color=0;
        }
        if(flagp==1){
            ImageDrawCircle(&imgBackground, x, y, 3, WHITE);
            if(r1==1) r1=0;
            else ImageDrawCircle(&imgBackground, fx, fy, 3, BLACK);
            flagp=0;
        }*/
        if(color==2) c=BLACK;
        if(color==1) c=WHITE;
        //if(color==0) c=BROWN;
        if(flag!=4) {
            ImageDrawCircle(&imgBackground, x, y, 16, c);
        }
        Texture textureBoard = LoadTextureFromImage(imgBackground);
        BeginDrawing();
        DrawTexture(textureBoard, 0, 0, WHITE);
        EndDrawing();
        UnloadTexture(textureBoard);
        if(flag==2) flag=0;
        if(flag==3) flag=1;
    }
    UnloadImage(imgBackground);
    CloseWindow();
}
