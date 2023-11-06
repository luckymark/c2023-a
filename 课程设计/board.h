//
// Created by Administrator on 2023/10/17 0017.
//

#ifndef C2023_CHALLENGE_BOARD_H
#define C2023_CHALLENGE_BOARD_H
void resetBoard();
void p1_chess(int x,int y);
void p2_chess(int x,int y);
void drawBoard(int win);
void playerMove(int win);
void input_data(int x,int y,int value);
int output_data(int x,int y);
int game_terminate();
#endif //C2023_CHALLENGE_BOARD_H
