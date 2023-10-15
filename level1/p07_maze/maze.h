#define SIDE 42//宏定义方便改变迷宫的边长来改变迷宫的难度
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
//用英文代替上下左右方向的第二个键值

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

typedef struct
{
    int x;
    int y;
}Player;//定义玩家的结构体类型
void Init_maze(int maze[SIDE + 2][SIDE + 2]);//初始化迷宫的函数
void Form_maze(int maze[SIDE + 2][SIDE + 2], int x, int y);//构建迷宫的函数
void Print(int maze[SIDE + 2][SIDE + 2], Player player);//打印迷宫的函数
int In(int maze[SIDE + 2][SIDE + 2]);//设置入口的函数
int Out(int maze[SIDE + 2][SIDE + 2]);//设置出口的函数
void Move(int maze[SIDE + 2][SIDE + 2], Player* pi, int a, int b);//实现方向键控制移动的函数
void Menu();//打印菜单的函数
void Color(int x);//控制字体颜色的函数
void gotoxy(int x, int y);//设置光标位置
void Find_way(int maze[SIDE + 2][SIDE + 2], int way[SIDE + 2][SIDE + 2], int x, int y, Player player,int count);//实现自动寻路的函数
void Print_way(int way[SIDE + 2][SIDE + 2], int maze[SIDE + 2][SIDE + 2], Player player,int out);//打印路径的函数
