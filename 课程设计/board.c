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

//神经网络输入
HCD NN_input;

//历史棋盘数据(真实)
int Board_History_Real[8][SIZE][SIZE];

//历史棋盘数据(虚拟)
int Board_History_Virtual[8][SIZE][SIZE];

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

//初始化历史棋盘数据
void reset_HCD(int type) {
    if (type == REAL) {
        for (int i = 0; i <8; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    Board_History_Real[i][j][k] = 0;
                }
            }
        }
    } else {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    Board_History_Virtual[i][j][k] = Board_History_Real[i][j][k];
                }
            }
        }
    }
}

//记录历史落子数据
void write_chessboard_data(int D_type) {
    if (D_type == REAL) {
        for (int i = 7; i > 0; --i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    Board_History_Real[i][j][k] = Board_History_Real[i-1][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                Board_History_Real[0][i][j] = board_real[i][j];
            }
        }
    } else {
        for (int i = 7; i > 0; --i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    Board_History_Virtual[i][j][k] = Board_History_Virtual[i-1][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                Board_History_Virtual[0][i][j] = board_virtual[i][j];
            }
        }
    }
}

//数据转录
void data_trans(int B_type,int D_type) {
    if (D_type == REAL) {
        NN_input.type = B_type;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                NN_input.X1[i][j] = Board_History_Real[0][i][j] == B_type ? 1 : 0;
                NN_input.X2[i][j] = Board_History_Real[1][i][j] == B_type ? 1 : 0;
                NN_input.X3[i][j] = Board_History_Real[2][i][j] == B_type ? 1 : 0;
                NN_input.X4[i][j] = Board_History_Real[3][i][j] == B_type ? 1 : 0;
                NN_input.X5[i][j] = Board_History_Real[4][i][j] == B_type ? 1 : 0;
                NN_input.X6[i][j] = Board_History_Real[5][i][j] == B_type ? 1 : 0;
                NN_input.X7[i][j] = Board_History_Real[6][i][j] == B_type ? 1 : 0;
                NN_input.X8[i][j] = Board_History_Real[7][i][j] == B_type ? 1 : 0;
                NN_input.Y1[i][j] = Board_History_Real[0][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y2[i][j] = Board_History_Real[1][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y3[i][j] = Board_History_Real[2][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y4[i][j] = Board_History_Real[3][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y5[i][j] = Board_History_Real[4][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y6[i][j] = Board_History_Real[5][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y7[i][j] = Board_History_Real[6][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y8[i][j] = Board_History_Real[7][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
            }
        }
    } else {
        NN_input.type = B_type;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                NN_input.X1[i][j] = Board_History_Virtual[0][i][j] == B_type ? 1 : 0;
                NN_input.X2[i][j] = Board_History_Virtual[1][i][j] == B_type ? 1 : 0;
                NN_input.X3[i][j] = Board_History_Virtual[2][i][j] == B_type ? 1 : 0;
                NN_input.X4[i][j] = Board_History_Virtual[3][i][j] == B_type ? 1 : 0;
                NN_input.X5[i][j] = Board_History_Virtual[4][i][j] == B_type ? 1 : 0;
                NN_input.X6[i][j] = Board_History_Virtual[5][i][j] == B_type ? 1 : 0;
                NN_input.X7[i][j] = Board_History_Virtual[6][i][j] == B_type ? 1 : 0;
                NN_input.X8[i][j] = Board_History_Virtual[7][i][j] == B_type ? 1 : 0;
                NN_input.Y1[i][j] = Board_History_Virtual[0][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y2[i][j] = Board_History_Virtual[1][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y3[i][j] = Board_History_Virtual[2][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y4[i][j] = Board_History_Virtual[3][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y5[i][j] = Board_History_Virtual[4][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y6[i][j] = Board_History_Virtual[5][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y7[i][j] = Board_History_Virtual[6][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y8[i][j] = Board_History_Virtual[7][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
            }
        }        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                NN_input.X1[i][j] = Board_History_Virtual[0][i][j] == B_type ? 1 : 0;
                NN_input.X2[i][j] = Board_History_Virtual[1][i][j] == B_type ? 1 : 0;
                NN_input.X3[i][j] = Board_History_Virtual[2][i][j] == B_type ? 1 : 0;
                NN_input.X4[i][j] = Board_History_Virtual[3][i][j] == B_type ? 1 : 0;
                NN_input.X5[i][j] = Board_History_Virtual[4][i][j] == B_type ? 1 : 0;
                NN_input.X6[i][j] = Board_History_Virtual[5][i][j] == B_type ? 1 : 0;
                NN_input.X7[i][j] = Board_History_Virtual[6][i][j] == B_type ? 1 : 0;
                NN_input.X8[i][j] = Board_History_Virtual[7][i][j] == B_type ? 1 : 0;
                NN_input.Y1[i][j] = Board_History_Virtual[0][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y2[i][j] = Board_History_Virtual[1][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y3[i][j] = Board_History_Virtual[2][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y4[i][j] = Board_History_Virtual[3][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y5[i][j] = Board_History_Virtual[4][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y6[i][j] = Board_History_Virtual[5][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y7[i][j] = Board_History_Virtual[6][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
                NN_input.Y8[i][j] = Board_History_Virtual[7][i][j] == (B_type == B_BLACK ? B_WHITE : B_BLACK) ? 1 : 0;
            }
        }
    }
}

//落子
void chess(int x,int y,int B_type,int D_type) {
    if (D_type == REAL) {
        board_real[y][x] = B_type;
        write_chessboard_data(REAL);
    } else {
        board_virtual[y][x] = B_type;
        write_chessboard_data(VIRTUAL);
    }
}