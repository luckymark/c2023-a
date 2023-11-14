#include <easyx.h>
#include <graphics.h>
#include "board_paint.h"

#define _UNICODE
#define UNICODE
//运行次数
int run_time = 0;

// 绘制棋盘
void drawBoard() {
    if (run_time == 0) {
        initgraph(389, 389);
    }
    run_time++;
    // 设置棋盘背景颜色
    setfillcolor(RGB(230, 200, 170));
    solidrectangle(0, 0, 389, 389);

    // 绘制网格线
    setlinecolor(BLACK);
    for(int i=1; i<SIZE+1; i++) {
        line(0, i*26, 389, i*26);
        line(i*26, 0, i*26, 389);
    }

    // 根据数组绘制棋子
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            if(board_real[i][j] == 1) {
                setfillcolor(BLACK);
                solidcircle(j*26+13, i*26+13, 10);
            }
            else if(board_real[i][j] == 2) {
                setfillcolor(WHITE);
                solidcircle(j*26+13, i*26+13, 10);
            }
        }
    }
    // 显示胜负结果
    if(win != 0) {
        // 绘制连线
        setlinecolor(RED);
        setlinestyle(PS_SOLID,5,NULL,0);
        line(start_x * 26+13, start_y * 26+13, end_x * 26+13, end_y * 26+13);
    }
}

// 玩家下棋
void playerMove() {
    int is_move = 1;
    while(is_move) {
        MOUSEMSG msg = GetMouseMsg();
        if(msg.mkLButton) {
            int i = msg.x / 26;
            int j = msg.y / 26;
            if(board_real[j][i] == B_EMPTY) {
                chess(i,j,B_WHITE,REAL);
                write_chessboard_data(B_WHITE,REAL);
                is_move = 0;
            }
        }
    }
    drawBoard();
}
