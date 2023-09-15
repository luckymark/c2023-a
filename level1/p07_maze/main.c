#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

HANDLE console;
COORD pPos = {2, 1};
CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;

enum{
    HIGH = 20,
    WIDTH = 53
};

int map[20][53]={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1},
        {1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,1,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,1,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

};

void init();


void kbEvent();


void updateStatus();

void drawMap();


bool inValidMove(int x, int y);

void win();

void cle(COORD ClPos);

void prin(COORD PrPos);

void Move(COORD *MoPos, int key) ;


int main() {
    init();
    while (1) {
        kbEvent();
        updateStatus();
    }
}

bool inValidMove(int x, int y) {
    return map[y][x / 2] == 0 || map[y][x / 2] == 2;
}


void Move(COORD *MoPos, int key) {
    switch (key) {
        case 72:
            if(!inValidMove(MoPos->X, MoPos->Y - 1))break;
            MoPos->Y--;
            break;
        case 75:
            if(!inValidMove(MoPos->X - 2, MoPos->Y))break;
            MoPos->X-=2;
            break;
        case 77:
            if(!inValidMove(MoPos->X + 2, MoPos->Y))break;
            MoPos->X+=2;
            break;
        case 80:
            if(!inValidMove(MoPos->X, MoPos->Y + 1))break;
            MoPos->Y++;
            break;
        default:
            break;
    }
}

void prin(COORD PrPos){
    SetConsoleCursorPosition(console, PrPos);
    printf("人");
}

void cle(COORD ClPos) {
    SetConsoleCursorPosition(console, ClPos);
    printf("  ");
}

void updateStatus() {
    if(map[pPos.Y][pPos.X / 2] == 2) {
        win();
    }
}

void win() {
    MessageBox(0,"Congratulation!","you win!!!!!",0);
    exit(0);
}

void kbEvent() {
    if (kbhit()) {
        cle(pPos);
        Move(&pPos, getch());
        prin(pPos);
    }
}

void init() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &ScreenBufferInfo);
    drawMap();
    prin(pPos);

    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);


}

void drawMap() {
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if(map[i][j]==1)printf("墙");
            if(map[i][j]==0)printf("  ");
            if(map[i][j]==2)printf("家");
        }
        putchar('\n');
    }
}
/*
#include<windows.h>
#include<conio.h>
#define Long 21
int c, i, place = Long, map[Long * Long] = { 0 };
int move[8] = { -1,1,-Long,Long,'a','d','w','s' };
void dig(int v) {
    int a[4] = { 2,-2,2 * Long,-2 * Long }, i = 0, j;
    for (; j = rand() % 4, i < 4; i++)i - j && (a[i] ^= a[j] ^= a[i] ^= a[j]);
    for (map[v] = 1, i = 0; i < 4; i++) {
        if (v + a[i] < 0 || Long * Long < v + a[i] || map[v + a[i]])continue;
        if ((a[i] == 2 || a[i] == -2) && v / Long - (a[i] + v) / Long)continue;
        map[v + a[i] / 2] = 1, dig(v + a[i]);
    }
}
int main() {
    srand((unsigned)malloc(!system("mode con:cols=42 lines=21")));
    SetConsoleCursorInfo(GetStdHandle((DWORD)-11), &(CONSOLE_CURSOR_INFO){25});
    dig(Long + 1), map[Long] = map[Long*Long - Long - 1] = 1;
    for (c = 0; c = _getch(), place - Long * Long + Long + 1;) {
        for (i = 0; c - move[i + 4] && i < 4; i++);
        i < 4 && map[place + move[i]] && (place += move[i]);
        SetConsoleCursorPosition(GetStdHandle((DWORD)-11), (COORD){0});
        for (i = 0; i < Long*Long; i++)
            _cputs(i - place ? map[i] ? "  " : "[]" : "<>");
    }
}
*/