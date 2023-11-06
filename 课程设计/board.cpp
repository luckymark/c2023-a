#include <easyx.h>
#include <graphics.h>
#include "board.h"

#define BOARD_SIZE 15
int board[BOARD_SIZE][BOARD_SIZE];
int start_x,start_y,end_x,end_y;

//重置棋盘
void resetBoard() {
    for (auto & i : board) {
        for (int & j : i) {
            j = 0;
        }
    }
    start_x = 0;
    start_y = 0;
    end_x = 0;
    end_x = 0;
    initgraph(389,389);
}
//黑子下棋
void p1_chess(int x,int y) {
    board[y][x] = 1;
}
//白子下棋
void p2_chess(int x,int y) {
    board[y][x] = -1;
}
// 绘制棋盘
void drawBoard(int win) {
    // 设置棋盘背景颜色
    setfillcolor(RGB(230, 200, 170));
    solidrectangle(0, 0, 389, 389);

    // 绘制网格线
    setlinecolor(BLACK);
    for(int i=1; i<BOARD_SIZE+1; i++) {
        line(0, i*26, 389, i*26);
        line(i*26, 0, i*26, 389);
    }

    // 根据数组绘制棋子
    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j=0; j<BOARD_SIZE; j++) {
            if(board[i][j] == 1) {
                setfillcolor(BLACK);
                solidcircle(j*26+13, i*26+13, 10);
            }
            else if(board[i][j] == -1) {
                setfillcolor(WHITE);
                solidcircle(j*26+13, i*26+13, 10);
            }
        }
    }
    // 显示胜负结果
    if(win != 0) {
        settextstyle(20, 0, "黑体");
        settextcolor(RED);
        if(win == 1) {
            outtextxy(150, 420, "黑棋获胜!");
        }
        else {
            outtextxy(150, 420, "白棋获胜!");
        }
        // 绘制连线
        setlinecolor(RED);
        line(start_x * 26, start_y * 26, end_x * 26, end_y * 26);
    }
}

// 玩家下棋
void playerMove(int win) {
    int is_move = 1;
    while(is_move) {
        MOUSEMSG msg = GetMouseMsg();
        if(msg.mkLButton) {
            int i = msg.x / 26;
            int j = msg.y / 26;
            if(board[j][i] == 0) {
                board[j][i] = -1;
                is_move = 0;
            }
        }
    }
    drawBoard(win);
}
//输入棋盘数据
void input_data(int x,int y,int value) {
    board[y][x] = value;
}
//输出棋盘数据
int output_data(int x,int y) {
    return board[y][x];
}
//判断输赢
int game_terminate() {
    //连续棋子数
    int count;
    //判断黑子胜利，若胜利则输出 1
    //横向遍历
    for (int i = 0; i < BOARD_SIZE; ++i) {
        count = 0;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 1) {
                count++;
            } else {
                count = 0;
            }
            if (count == 5) {
                return 1;
            }
        }
    }
    //竖向遍历
    for (int i = 0; i < BOARD_SIZE; ++i) {
        count = 0;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[j][i] == 1) {
                count++;
            } else {
                count = 0;
            }
            if (count == 5) {
                return 1;
            }
        }
    }
    //判断白子胜利，若胜利则输出 -1
    //横向遍历
    for (int i = 0; i < BOARD_SIZE; ++i) {
        count = 0;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == -1) {
                count++;
            } else {
                count = 0;
            }
            if (count == 5) {
                return -1;
            }
        }
    }
    //竖向遍历
    for (int i = 0; i < BOARD_SIZE; ++i) {
        count = 0;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[j][i] == -1) {
                count++;
            } else {
                count = 0;
            }
            if (count == 5) {
                return -1;
            }
        }
    }
    int i, j;
    // 检查左上-右下对角线
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 11; j++) {
            if (board[i][j] != 0 &&
                board[i][j] == board[i+1][j+1] &&
                board[i][j] == board[i+2][j+2] &&
                board[i][j] == board[i+3][j+3] &&
                board[i][j] == board[i+4][j+4]) {
                return board[i][j];
            }
        }
    }
    // 检查右上-左下对角线
    for (i = 0; i < 11; i++) {
        for (j = 14; j > 3; j--) {
            if (board[i][j] != 0 &&
                board[i][j] == board[i+1][j-1] &&
                board[i][j] == board[i+2][j-2] &&
                board[i][j] == board[i+3][j-3] &&
                board[i][j] == board[i+4][j-4]) {
                return board[i][j];
            }
        }
    }
    return 0;
}
