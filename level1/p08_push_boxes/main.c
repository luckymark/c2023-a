#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

HANDLE console;//窗口句柄
COORD CrPos = {};//保存光标信息
CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;//保存窗口信息


enum {
    PERSON = 6,
    WALL = 1,
    ROAD = 0,
    TARGET = 2,
    BOX = 3
};

enum {
    Up = 1,
    Down = 2,
    Left = 3,
    Right = 4
};

int HIGH = 20, WIDTH = 53;

int map[20][53];

//文件
FILE *fp = NULL;

void init();

//响应键盘事件
void kbEvent();

//更新游戏状态
void updateStatus();

void drawWall();

//判断移动是否合法
bool inValidMove(int x, int y, int dir);

void win();

//清除函数
void cle(COORD ClPos);

//打印函数
void prin(COORD PrPos);

//移动函数
void Move(COORD *MoPos, int key);

void readMap();

void initPerson();

void GetNewPos(COORD *pNewCoord, int key);

int main() {
    init();
    //等待键按下
    while (1) {
        kbEvent();
        updateStatus();
    }
}

bool inValidMove(int x, int y, int dir) {
    switch (dir) {
        case Up:
            return map[y][x / 2] == WALL || (map[y][x / 2] == BOX && map[y - 1][x / 2] == ROAD);
        case Down:
            return map[y][x / 2] == WALL || (map[y][x / 2] == BOX && map[y + 1][x / 2] == ROAD);
        case Left:
            return map[y][x / 2] == WALL || (map[y][x / 2] == BOX && map[y][x / 2 - 1] == ROAD);
        case Right:
            return map[y][x / 2] == WALL || (map[y][x / 2] == BOX && map[y][x / 2 + 1] == ROAD);
        default:
            break;
    }
}


void Move(COORD *MoPos, int key) {
    switch (key) {
        case 72://上
            if (inValidMove(MoPos->X, MoPos->Y - 1, Up))break;
            MoPos->Y--;
            break;
        case 75://左
            if (inValidMove(MoPos->X - 2, MoPos->Y, Left))break;
            MoPos->X -= 2;
            break;
        case 77://右
            if (inValidMove(MoPos->X + 2, MoPos->Y, Right))break;
            MoPos->X += 2;
            break;
        case 80://下
            if (inValidMove(MoPos->X, MoPos->Y + 1, Down))break;
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
    COORD nowPos = {};
    if (kbhit()) {
        //GetNewPos(&nowPos, getch());
        cle(CrPos);//清除原有输出
        Move(&CrPos, getch());
        //prin(CrPos);
    }
}

void GetNewPos(COORD *pNewCoord, int key) {
    switch (key) {
        case 72://上
            pNewCoord->X = CrPos.X;
            pNewCoord->Y = CrPos.Y - 1;
            break;
        case 75://左
            pNewCoord->X = CrPos.X - 2;
            pNewCoord->Y = CrPos.Y;
            break;
        case 77://右
            pNewCoord->X = CrPos.X + 2;
            pNewCoord->Y = CrPos.Y;
            break;
        case 80://下
            pNewCoord->X = CrPos.X;
            pNewCoord->Y = CrPos.Y + 1;
            break;
        default:
            break;
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
            if (map[i][j] == PERSON) {
                CrPos.X = j * 2;
                CrPos.Y = i;
                map[i][j] = ROAD;
            }
        }
    }
}

void readMap() {
    fp = fopen("../../level1/p08_push_boxes/map/1.map", "r");
    fscanf_s(fp, "%d %d", &WIDTH, &HIGH);
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            fscanf_s(fp, "%d", &map[i][j]);
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
