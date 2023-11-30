#include <easyx.h>
#include <graphics.h>
#include "board_paint.h"

//运行次数
int run_time = 0;

void drawPoint() {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board_real[i][j] == 0) {
                setfillcolor(BLACK);
                solidcircle(j*26+51, i*26+51, 2);
            }
        }
    }
}

// 绘制棋盘
void drawBoard() {
    if (run_time == 0) {
        initgraph(468,468);
    }
    run_time++;
    setfillcolor(RGB(230, 200, 170));
    setlinestyle(PS_SOLID,3,NULL,0);
    solidrectangle(0, 0, 468, 468);
    setlinecolor(BLACK);
    line(25,25,25,441);
    line(25,25,441,25);
    line(441,441,25,441);
    line(441,441,441,25);
    for (int i = 0; i < 15; ++i) {
        setlinestyle(PS_SOLID,1,NULL,0);
        line(51,51+i*26,415,51+i*26);
        line(51+i*26,51,51+i*26,415);
    }
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board_real[i][j] == B_BLACK) {
                setfillcolor(BLACK);
                solidcircle(j*26+51, i*26+51, 10);
            } else if (board_real[i][j] == B_WHITE) {
                setfillcolor(WHITE);
                solidcircle(j*26+51, i*26+51, 10);
            }
        }
    }
    drawPoint();
    // 显示胜负结果
    if(win != 0) {
        // 绘制连线
        setlinecolor(RED);
        setlinestyle(PS_SOLID,5,NULL,0);
        line(start_x * 26+51, start_y * 26+51, end_x * 26+51, end_y * 26+51);
    }
}

// 玩家下棋
void playerMove() {
    int is_move = 1;
    while(is_move) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.x < 428 && msg.x > 38 && msg.y < 428 && msg.y > 38) {
            int i = (msg.y-38)/26;
            int j = (msg.x-38)/26;
            drawPoint();
            if (board_real[j][i] == 0) {
                setfillcolor(RED);
                solidcircle(j*26+51, i*26+51, 2);
            }
            if(msg.mkLButton) {
                if(board_real[j][i] == 0) {
                    chess(j,i,B_WHITE,REAL);
                    is_move = 0;
                }
            }
        }
    }
    drawBoard();
}
