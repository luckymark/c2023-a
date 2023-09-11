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
void cle();

//打印函数
void prin(const char *putChar);

//移动函数
void Move(int key);

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

bool inValidMove(int x, int y, int dir) {
    switch (dir) {
        case Up:
            return map[y][x / 2] == WALL ||
                   (map[y][x / 2] == BOX && (map[y - 1][x / 2] == ROAD || map[y - 1][x / 2] == TARGET));
        case Down:
            return map[y][x / 2] == WALL ||
                   (map[y][x / 2] == BOX && (map[y + 1][x / 2] == ROAD || map[y + 1][x / 2] == TARGET));
        case Left:
            return map[y][x / 2] == WALL ||
                   (map[y][x / 2] == BOX && (map[y][x / 2 - 1] == ROAD || map[y][x / 2 - 1] == TARGET));
        case Right:
            return map[y][x / 2] == WALL ||
                   (map[y][x / 2] == BOX && (map[y][x / 2 + 1] == ROAD || map[y][x / 2 + 1] == TARGET));
        default:
            break;
    }
}


void Move(int key) {
    COORD tmpCoord;
    switch (key) {
        case 72://上
            if (inValidMove(CrPos.X, CrPos.Y - 1, Up))break;
            if (map[CrPos.Y - 1][CrPos.X] == BOX) {
                tmpCoord.X = CrPos.X, tmpCoord.Y = CrPos.Y - 2;
                SetConsoleCursorPosition(console, tmpCoord);
                printf("箱");
            }
            CrPos.Y -= 1;
            prin("人");
            break;

        case 75://左
            if (inValidMove(CrPos.X - 2, CrPos.Y, Up))break;
            if (map[CrPos.Y][CrPos.X - 2] == BOX) {
                tmpCoord.X = CrPos.X - 4, tmpCoord.Y = CrPos.Y;
                SetConsoleCursorPosition(console, tmpCoord);
                printf("箱");
            }
            CrPos.X -= 2;
            prin("人");
            break;

        case 77://右
            if (inValidMove(CrPos.X + 2, CrPos.Y, Up))break;
            if (map[CrPos.Y][CrPos.X + 2] == BOX) {
                tmpCoord.X = CrPos.X + 4, tmpCoord.Y = CrPos.Y;
                SetConsoleCursorPosition(console, tmpCoord);
                printf("箱");
            }
            CrPos.X += 2;
            prin("人");
            break;

        case 80://下
            if (inValidMove(CrPos.X, CrPos.Y + 1, Up))break;
            if (map[CrPos.Y + 1][CrPos.X] == BOX) {
                tmpCoord.X = CrPos.X, tmpCoord.Y = CrPos.Y + 2;
                SetConsoleCursorPosition(console, tmpCoord);
                printf("箱");
            }
            CrPos.Y += 1;
            prin("人");
            break;
        default:
            break;
    }
}



void prin(const char *putChar) {
    SetConsoleCursorPosition(console, CrPos);
    printf("%s", putChar);
}

void cle() {
    SetConsoleCursorPosition(console, CrPos);
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
        //GetNewPos(&nowPos, getch());
        cle();//清除原有输出
        Move(getch());
        //prin(CrPos);
    }
}

void init() {
    readMap();
    initPerson();

    console = GetStdHandle(STD_OUTPUT_HANDLE);//取句柄
    GetConsoleScreenBufferInfo(console, &ScreenBufferInfo);
    drawWall();
    prin("人");//打印

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
            if (map[i][j] == TARGET)printf("标");
            if (map[i][j] == BOX)printf("箱");
        }
        putchar('\n');
    }
}
