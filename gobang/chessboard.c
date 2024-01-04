#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Evaluate.h"
#include "Minimax_Search.h"
#include "Inspire_Search.h"
int main()
{
    //初始化棋盘
    int map[15][15]={};
    map[7][7]=1;
    InitWindow(960,960,"Chessboard");
    //反复渲染棋盘
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            int m = (int) ((GetMouseX() - 30) / 60);
            int n = (int) ((GetMouseY() - 30) / 60);
            if (m >= 0 && m <= 14 && n >= 0 && n <= 14 && map[m][n]!=-1)
            {
                map[m][n] = 1;
            }
            Root* pt = Create_Root(map);
            int score=pt->score;
            int x= pt->x;
            int y= pt->y;
            map[x][y]=-1;
            printf("%d x=%d y=%d\n",score,x,y);
        }
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            int m = (int) ((GetMouseX() - 30) / 60);
            int n = (int) ((GetMouseY() - 30) / 60);
            if (m >= 0 && m <= 14 && n >= 0 && n <= 14 && map[m][n]!=1)
            {
                map[m][n] = -1;
            }
        }
        BeginDrawing();
        ClearBackground(SKYBLUE);
        for (int i = 60; i <= 900; i += 60)
        {
            DrawLine(i, 60, i, 900, RED);
        }
        for (int i = 60; i <= 900; i += 60)
        {
            DrawLine(60, i, 900, i, RED);
        }
        for (int i = 0; i <= 14; i++)
        {
            for (int j = 0; j <= 14; j++)
            {
                if (map[i][j] == 1)
                {
                    DrawCircle(60 * (i + 1), 60 * (j + 1), 25, BLACK);
                }
                if (map[i][j] == -1)
                {
                    DrawCircle(60 * (i + 1), 60 * (j + 1), 25, WHITE);
                }
            }
        }
        EndDrawing();
        if(IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
        {
            int score = Evaluate(map);
            printf("%d\n",score);
        }
    }
    return 0;
}