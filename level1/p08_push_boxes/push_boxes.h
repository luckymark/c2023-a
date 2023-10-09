#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
typedef struct
{
    int x;
    int y;
}Player;
void Print_map(FILE* map,int level,Player* pi);
void Form_arr(FILE* map,int level,int arr1[20][20],int arr2[20][20]);
void Move(int arr1[20][20],int arr2[20][20], Player* pi,int* pc);
int Is_win(int arr1[20][20],int arr2[20][20]);
void Color(int x);
void gotoxy(int x, int y);
void Game(int level);


