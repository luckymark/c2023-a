#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

HANDLE console;//窗口句柄
COORD CrPos = {2, 1};//保存光标信息
CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;//保存窗口信息


enum{
    PERSON = 6,
    WALL = 1,
    ROAD = 0,
    TARGET = 2
};

int HIGH = 20, WIDTH = 53;

int map[20][53];

//文件
FILE *fp=NULL;

void init();

//响应键盘事件
void kbEvent();

//更新游戏状态
void updateStatus();

void drawWall();

//判断移动是否合法
bool inValidMove(int x, int y);

void win();

//清除函数
void cle(COORD ClPos);

//打印函数
void prin(COORD PrPos);

//移动函数
void Move(COORD *MoPos, int key);


void readMap();

void initPerson();

int main() {
    init();
    //等待键按下
    while (1) {
        kbEvent();
        updateStatus();
    }
}

bool inValidMove(int x, int y) {
    return map[y][x / 2] == ROAD || map[y][x / 2] == TARGET;
}


void Move(COORD *MoPos, int key) {
    switch (key) {
        case 72:
            if (!inValidMove(MoPos->X, MoPos->Y - 1))break;
            MoPos->Y--;
            break;
        case 75:
            if (!inValidMove(MoPos->X - 2, MoPos->Y))break;
            MoPos->X -= 2;
            break;
        case 77:
            if (!inValidMove(MoPos->X + 2, MoPos->Y))break;
            MoPos->X += 2;
            break;
        case 80:
            if (!inValidMove(MoPos->X, MoPos->Y + 1))break;
            MoPos->Y++;
            break;
        default:
            break;
    }
}

void prin(COORD PrPos) {
    SetConsoleCursorPosition(console, PrPos);
    printf("人");
}

void cle(COORD ClPos) {
    SetConsoleCursorPosition(console, ClPos);
    printf(" ");
}

void updateStatus() {
    if (map[CrPos.Y][CrPos.X / 2] == TARGET) {
        win();
    }
}

void win() {
    MessageBox(0, "Congratulation!", "you win!!!!!", 0);
    exit(0);
}

void kbEvent() {
    if (kbhit()) {
        cle(CrPos);//清除原有输出
        Move(&CrPos, getch());
        prin(CrPos);
    }
}

void init() {
    readMap();
    initPerson();

    console = GetStdHandle(STD_OUTPUT_HANDLE);//取句柄
    GetConsoleScreenBufferInfo(console, &ScreenBufferInfo);
    drawWall();
    prin(CrPos);//打印

    //隐藏光标
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);


}

void initPerson() {
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (map[i][j] == PERSON){
                CrPos.X = j * 2;
                CrPos.Y = i;
                map[i][j] = ROAD;
            }
        }
    }
}

void readMap() {
    fp = fopen("1.map", "r");
    fscanf_s(fp,"%d %d", &WIDTH, &HIGH);
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            fscanf_s(fp,"%d", &map[i][j]);
        }
    }
}

void drawWall() {
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (map[i][j] == WALL)printf("墙");
            if (map[i][j] == ROAD)printf("  ");
            if (map[i][j] == TARGET)printf("家");
        }
        putchar('\n');
    }
}
