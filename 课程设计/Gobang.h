#ifndef C2023_CHALLENGE_GOBANG_H
#define C2023_CHALLENGE_GOBANG_H
#define SIDE 15
#define EMPTY 0
#define Black 1
#define White -1
#define MAX 2147483647

#include <cstdio>
#include <cstdlib>
#include <easyx.h>
#include <cmath>
#include <ctime>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
//栈的实现
typedef struct {
    int x;
    int y;
} Step;
typedef struct Stack {
    Step *data;
    int count;
    int size;
} Stack;

Stack *creat_stack(int size);

int is_empty(Stack *stack);

int is_full(Stack *stack);

void stack_push(Stack *stack, Step *value);

Step *stack_pop(Stack *stack);

//GUI图形界面
typedef struct {
    int x;
    int y;
    int w;
    int h;
} Button;

void menu1();

void print_button(Button b, const char *text, int bk_color, int text_color, int text_size, const char *text_style);

int in_button_area(Button b, ExMessage msg);

int is_press(Button b, ExMessage msg);

void print_board();
//void play_music(const char* music, int volumn, bool is_re);

void init_board(int **b);

int is_four(int **board, int x, int y, int player);

int is_five(int **board, int x, int y, int player);

int is_live(int **b, int x, int y, int player, int n);

int is_dead(int **board, int x, int y, int player, int n);

int is_win(int **board, int player);

int out_range(int x, int y);

//算法
int score(int **board, int player, int w);

int judge(int **board, int x, int y);

void move(ExMessage msg, int **board, int *count, int player, Stack *s);

int minimax(int **board, int depth, int player, int alpha, int beta, int *Row, int *Col, int w);

void ai_move(int **board, int depth, int player, int w, int *c, Stack *s);

//悔棋
void clear_chess(int x, int y, Stack *s, int player, int *c);

void back_move(int **board, Stack *s, int *c, int player);

#endif //C2023_CHALLENGE_GOBANG_H
