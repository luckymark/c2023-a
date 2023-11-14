/*
 * 此文件包含了五子棋游戏所需的基本变量与基本函数
 */
#include "board.h"

//当前实际棋盘
int board_real[SIZE][SIZE];

//当前虚拟棋盘
int board_virtual[SIZE][SIZE];

//输赢
int win = 0;

//相连棋子的首尾坐标
int start_x = 0;
int start_y = 0;
int end_x = 0;
int end_y = 0;

//历史棋盘数据(实际)
HCD HCD_real;

//历史棋盘数据(虚拟)
HCD HCD_virtual;

//重置棋盘
void resetBoard(int type) {
    if (type==REAL) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                board_real[i][j] = 0;
            }
        }
    } else {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                board_virtual[i][j] = board_real[i][j];
            }
        }
    }
}

//判断输赢
void game_terminate(int type) {
    win = 0;
    if (type == REAL) {
        start_x = 0;
        start_y = 0;
        end_x = 0;
        end_y = 0;
        //判断是否出现平局
        int count = 0;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board_real[i][j] != 0) {
                    count++;
                }
            }
        }
        if (count == SIZE*SIZE) {
            win = 3;
        }
        int i, j;
        //横向检查
        for (i = 0; i < SIZE; ++i) {
            for (j = 0; j < SIZE; ++j) {
                if (board_real[i][j] != 0 &&
                    board_real[i][j] == board_real[i][j + 1] &&
                    board_real[i][j] == board_real[i][j + 2] &&
                    board_real[i][j] == board_real[i][j + 3] &&
                    board_real[i][j] == board_real[i][j + 4]) {
                    win = board_real[i][j];
                    start_x = j;
                    start_y = i;
                    end_x = j+4;
                    end_y = i;
                }
            }
        }
        //竖向检查
        for (i = 0; i < SIZE; ++i) {
            for (j = 0; j < SIZE; ++j) {
                if (board_real[i][j] != 0 &&
                    board_real[i][j] == board_real[i + 1][j] &&
                    board_real[i][j] == board_real[i + 2][j] &&
                    board_real[i][j] == board_real[i + 3][j] &&
                    board_real[i][j] == board_real[i + 4][j]) {
                    win = board_real[i][j];
                    start_x = j;
                    start_y = i;
                    end_x = j;
                    end_y = i+4;
                }
            }
        }
        // 检查左上-右下对角线
        for (i = 0; i < 11; i++) {
            for (j = 0; j < 11; j++) {
                if (board_real[i][j] != 0 &&
                    board_real[i][j] == board_real[i + 1][j + 1] &&
                    board_real[i][j] == board_real[i + 2][j + 2] &&
                    board_real[i][j] == board_real[i + 3][j + 3] &&
                    board_real[i][j] == board_real[i + 4][j + 4]) {
                    win = board_real[i][j];
                    start_x = j;
                    start_y = i;
                    end_x = j+4;
                    end_y = i+4;
                }
            }
        }
        // 检查右上-左下对角线
        for (i = 0; i < 11; i++) {
            for (j = 14; j > 3; j--) {
                if (board_real[i][j] != 0 &&
                    board_real[i][j] == board_real[i + 1][j - 1] &&
                    board_real[i][j] == board_real[i + 2][j - 2] &&
                    board_real[i][j] == board_real[i + 3][j - 3] &&
                    board_real[i][j] == board_real[i + 4][j - 4]) {
                    win = board_real[i][j];
                    start_x = j;
                    start_y = i;
                    end_x = j-4;
                    end_y = i+4;
                }
            }
        }
    } else {
        //判断是否出现平局
        int count = 0;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board_virtual[i][j] != 0) {
                    count++;
                }
            }
        }
        if (count == SIZE*SIZE) {
            win = 3;
        }
        int i, j;
        //横向检查
        for (i = 0; i < SIZE; ++i) {
            for (j = 0; j < SIZE; ++j) {
                if (board_virtual[i][j] != 0 &&
                    board_virtual[i][j] == board_virtual[i][j + 1] &&
                    board_virtual[i][j] == board_virtual[i][j + 2] &&
                    board_virtual[i][j] == board_virtual[i][j + 3] &&
                    board_virtual[i][j] == board_virtual[i][j + 4]) {
                    win = board_virtual[i][j];
                }
            }
        }
        //竖向检查
        for (i = 0; i < SIZE; ++i) {
            for (j = 0; j < SIZE; ++j) {
                if (board_virtual[i][j] != 0 &&
                    board_virtual[i][j] == board_virtual[i + 1][j] &&
                    board_virtual[i][j] == board_virtual[i + 2][j] &&
                    board_virtual[i][j] == board_virtual[i + 3][j] &&
                    board_virtual[i][j] == board_virtual[i + 4][j]) {
                    win = board_virtual[i][j];
                }
            }
        }
        // 检查左上-右下对角线
        for (i = 0; i < 11; i++) {
            for (j = 0; j < 11; j++) {
                if (board_virtual[i][j] != 0 &&
                    board_virtual[i][j] == board_virtual[i + 1][j + 1] &&
                    board_virtual[i][j] == board_virtual[i + 2][j + 2] &&
                    board_virtual[i][j] == board_virtual[i + 3][j + 3] &&
                    board_virtual[i][j] == board_virtual[i + 4][j + 4]) {
                    win = board_virtual[i][j];
                }
            }
        }
        // 检查右上-左下对角线
        for (i = 0; i < 11; i++) {
            for (j = 14; j > 3; j--) {
                if (board_virtual[i][j] != 0 &&
                    board_virtual[i][j] == board_virtual[i + 1][j - 1] &&
                    board_virtual[i][j] == board_virtual[i + 2][j - 2] &&
                    board_virtual[i][j] == board_virtual[i + 3][j - 3] &&
                    board_virtual[i][j] == board_virtual[i + 4][j - 4]) {
                    win = board_virtual[i][j];
                }
            }
        }
    }
}

//初始化落子数据
void reset_HCD(int type) {
    if (type == REAL) {
        HCD_real.type = B_EMPTY;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                HCD_real.B1[i][j] = 0;
                HCD_real.W1[i][j] = 0;
                HCD_real.B2[i][j] = 0;
                HCD_real.W2[i][j] = 0;
                HCD_real.B3[i][j] = 0;
                HCD_real.W3[i][j] = 0;
                HCD_real.B4[i][j] = 0;
                HCD_real.W4[i][j] = 0;
                HCD_real.B5[i][j] = 0;
                HCD_real.W5[i][j] = 0;
                HCD_real.B6[i][j] = 0;
                HCD_real.W6[i][j] = 0;
                HCD_real.B7[i][j] = 0;
                HCD_real.W7[i][j] = 0;
                HCD_real.B8[i][j] = 0;
                HCD_real.W8[i][j] = 0;
            }
        }
    } else {
        HCD_virtual.type = B_EMPTY;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                HCD_virtual.B1[i][j] = HCD_real.B1[i][j];
                HCD_virtual.W1[i][j] = HCD_real.W1[i][j];
                HCD_virtual.B2[i][j] = HCD_real.B2[i][j];
                HCD_virtual.W2[i][j] = HCD_real.W2[i][j];
                HCD_virtual.B3[i][j] = HCD_real.B3[i][j];
                HCD_virtual.W3[i][j] = HCD_real.W3[i][j];
                HCD_virtual.B4[i][j] = HCD_real.B4[i][j];
                HCD_virtual.W4[i][j] = HCD_real.W4[i][j];
                HCD_virtual.B5[i][j] = HCD_real.B5[i][j];
                HCD_virtual.W5[i][j] = HCD_real.W5[i][j];
                HCD_virtual.B6[i][j] = HCD_real.B6[i][j];
                HCD_virtual.W6[i][j] = HCD_real.W6[i][j];
                HCD_virtual.B7[i][j] = HCD_real.B7[i][j];
                HCD_virtual.W7[i][j] = HCD_real.W7[i][j];
                HCD_virtual.B8[i][j] = HCD_real.B8[i][j];
                HCD_virtual.W8[i][j] = HCD_real.W8[i][j];
            }
        }
    }
}

//记录历史落子数据
void write_chessboard_data(int B_type, int D_type) {
    if (D_type == REAL) {
        if (B_type == B_BLACK) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    HCD_real.B8[i][j] = HCD_real.B7[i][j];
                    HCD_real.B7[i][j] = HCD_real.B6[i][j];
                    HCD_real.B6[i][j] = HCD_real.B5[i][j];
                    HCD_real.B5[i][j] = HCD_real.B4[i][j];
                    HCD_real.B4[i][j] = HCD_real.B3[i][j];
                    HCD_real.B3[i][j] = HCD_real.B2[i][j];
                    HCD_real.B2[i][j] = HCD_real.B1[i][j];
                    if (board_real[i][j] == B_BLACK) {
                        HCD_real.B1[i][j] = 1;
                    }
                }
            }
            HCD_real.type = B_WHITE;
        } else {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    HCD_real.W8[i][j] = HCD_real.W7[i][j];
                    HCD_real.W7[i][j] = HCD_real.W6[i][j];
                    HCD_real.W6[i][j] = HCD_real.W5[i][j];
                    HCD_real.W5[i][j] = HCD_real.W4[i][j];
                    HCD_real.W4[i][j] = HCD_real.W3[i][j];
                    HCD_real.W3[i][j] = HCD_real.W2[i][j];
                    HCD_real.W2[i][j] = HCD_real.W1[i][j];
                    if (board_real[i][j] == B_WHITE) {
                        HCD_real.B1[i][j] = 1;
                    }
                }
            }
            HCD_real.type = B_BLACK;
        }
    } else {
        if (B_type == B_BLACK) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    HCD_virtual.B8[i][j] = HCD_virtual.B7[i][j];
                    HCD_virtual.B7[i][j] = HCD_virtual.B6[i][j];
                    HCD_virtual.B6[i][j] = HCD_virtual.B5[i][j];
                    HCD_virtual.B5[i][j] = HCD_virtual.B4[i][j];
                    HCD_virtual.B4[i][j] = HCD_virtual.B3[i][j];
                    HCD_virtual.B3[i][j] = HCD_virtual.B2[i][j];
                    HCD_virtual.B2[i][j] = HCD_virtual.B1[i][j];
                    if (board_virtual[i][j] == B_BLACK) {
                        HCD_virtual.B1[i][j] = 1;
                    }
                }
            }
            HCD_virtual.type = B_WHITE;
        } else {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    HCD_virtual.W8[i][j] = HCD_virtual.W7[i][j];
                    HCD_virtual.W7[i][j] = HCD_virtual.W6[i][j];
                    HCD_virtual.W6[i][j] = HCD_virtual.W5[i][j];
                    HCD_virtual.W5[i][j] = HCD_virtual.W4[i][j];
                    HCD_virtual.W4[i][j] = HCD_virtual.W3[i][j];
                    HCD_virtual.W3[i][j] = HCD_virtual.W2[i][j];
                    HCD_virtual.W2[i][j] = HCD_virtual.W1[i][j];
                    if (board_virtual[i][j] == B_WHITE) {
                        HCD_virtual.B1[i][j] = 1;
                    }
                }
            }
            HCD_virtual.type = B_BLACK;
        }
    }
}


//直接对棋盘落子
void chess(int x,int y,int B_type,int D_type) {
    if (D_type == REAL) {
        board_real[y][x] = B_type;
    } else {
        board_virtual[y][x] = B_type;
    }
}

//根据节点落子（同时写入历史棋盘数据）
void node_chess(Node* input,int D_type) {
    chess(input->X,input->Y,input->type,D_type);
    write_chessboard_data(input->type,D_type);
}