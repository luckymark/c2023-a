#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

HANDLE console;//窗口句柄
COORD CrPos = {};//保存光标信息
CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;//保存窗口信息
COORD ZERO_COORD = {0, 0};

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

//记录用户移动步数
int stepCC;

//目标关卡
int targetLevel;

//文件
FILE *fp = NULL;

void gameInit();

//响应键盘事件
void kbEvent();

//更新游戏状态
bool gameStatusIsNotStop();

void drawWall();

//判断移动是否合法
bool ValidMove(int x, int y, int dir);

//赢了游戏之后程序的响应
void win();

//清除函数
void cle();

//清屏函数
void clearScreen();

//打印函数
void prin(const char *putChar);

//移动函数
void Move(int key);

//读取地图内容
void readMap();

//初次识别人的位置并存储其位置信息
void initPerson();

//检测所有的目标都已经清除了
bool allTargetCleared();

void printMenu();

int main() {
    while(1){
        clearScreen();
        printMenu();
        gameInit();
        //对游戏状态更新
        while (gameStatusIsNotStop()) {
            kbEvent(); //响应键盘事件
        }
    }
}

void printMenu() {
    printf("请输入想挑战的关卡(1~2):");
    scanf_s("%d", &targetLevel);
    if (!(targetLevel >= 1 && targetLevel <= 2)) {
        MessageBox(0, "输入了不合法的数字", "即将退出", 0);
        exit(EXIT_FAILURE);
    }
}

void gameInit() {
    //清空地图存档
    memset(map, 0, sizeof(map));
    //清空步数
    stepCC = 0;

    clearScreen();
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
    char fileDir[30];
    sprintf(fileDir,"../../level1/p08_push_boxes/map/%d.map", targetLevel);
    fp = fopen(fileDir, "r");
    fscanf_s(fp, "%d %d", &WIDTH, &HIGH);
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            fscanf_s(fp, "%d", &map[i][j]);
        }
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

void clearScreen(){
    SetConsoleCursorPosition(console, ZERO_COORD);
    system("cls");
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


void kbEvent() {
    if (kbhit()) {
        //GetNewPos(&nowPos, getch());
        cle();//清除原有输出
        Move(getch());
        //prin(CrPos);
    }
}

void Move(int key) {
    COORD tmpCoord;
    switch (key) {
        case 72://上
            if (!ValidMove(CrPos.X, CrPos.Y - 1, Up)) {
                prin("人");
                break;
            }
            if (map[CrPos.Y - 1][CrPos.X / 2] == BOX) {
                tmpCoord.X = CrPos.X, tmpCoord.Y = CrPos.Y - 2;
                SetConsoleCursorPosition(console, tmpCoord);
                printf("箱");
                map[CrPos.Y - 2][CrPos.X / 2] = BOX;
                map[CrPos.Y - 1][CrPos.X / 2] = ROAD;
            }
            //检查是否是原来占着标的位置
            if(map[CrPos.Y][CrPos.X/2]==TARGET){
                prin("标");
            }
            CrPos.Y -= 1;
            prin("人");
            stepCC++;
            break;

        case 75://左
            if (!ValidMove(CrPos.X - 2, CrPos.Y, Left)) {
                prin("人");
                break;
            }
            if (map[CrPos.Y][(CrPos.X - 2) / 2] == BOX) {
                tmpCoord.X = CrPos.X - 4, tmpCoord.Y = CrPos.Y;
                SetConsoleCursorPosition(console, tmpCoord);
                printf("箱");
                map[CrPos.Y][(CrPos.X - 2) / 2] = ROAD;
                map[CrPos.Y][(CrPos.X - 4) / 2] = BOX;
            }
            if(map[CrPos.Y][CrPos.X/2]==TARGET){
                prin("标");
            }
            CrPos.X -= 2;
            prin("人");
            stepCC++;
            break;

        case 77://右
            if (!ValidMove(CrPos.X + 2, CrPos.Y, Right)) {
                prin("人");
                break;
            }
            if (map[CrPos.Y][(CrPos.X + 2) / 2] == BOX) {
                tmpCoord.X = CrPos.X + 4, tmpCoord.Y = CrPos.Y;
                SetConsoleCursorPosition(console, tmpCoord);
                printf("箱");
                map[CrPos.Y][(CrPos.X + 2) / 2] = ROAD;
                map[CrPos.Y][(CrPos.X + 4) / 2] = BOX;
            }
            if(map[CrPos.Y][CrPos.X/2]==TARGET){
                prin("标");
            }
            CrPos.X += 2;
            prin("人");
            stepCC++;
            break;

        case 80://下
            if (!ValidMove(CrPos.X, CrPos.Y + 1, Down)) {
                prin("人");
                break;
            }
            if (map[CrPos.Y + 1][CrPos.X / 2] == BOX) {
                tmpCoord.X = CrPos.X, tmpCoord.Y = CrPos.Y + 2;
                SetConsoleCursorPosition(console, tmpCoord);
                printf("箱");
                map[CrPos.Y + 2][CrPos.X / 2] = BOX;
                map[CrPos.Y + 1][CrPos.X / 2] = ROAD;
            }
            if(map[CrPos.Y][CrPos.X/2]==TARGET){
                prin("标");
            }
            CrPos.Y += 1;
            prin("人");
            stepCC++;
            break;
        default:
            break;
    }
}

bool ValidMove(int x, int y, int dir) {
    switch (dir) {
        case Up:
            return map[y][x / 2] == ROAD ||map[y][x / 2] == TARGET ||
                   (map[y][x / 2] == BOX && (map[y - 1][x / 2] == ROAD || map[y - 1][x / 2] == TARGET));
        case Down:
            return map[y][x / 2] == ROAD ||map[y][x / 2] == TARGET ||
                   (map[y][x / 2] == BOX && (map[y + 1][x / 2] == ROAD || map[y + 1][x / 2] == TARGET));
        case Left:
            return map[y][x / 2] == ROAD ||map[y][x / 2] == TARGET ||
                   (map[y][x / 2] == BOX && (map[y][x / 2 - 1] == ROAD || map[y][x / 2 - 1] == TARGET));
        case Right:
            return map[y][x / 2] == ROAD ||map[y][x / 2] == TARGET ||
                   (map[y][x / 2] == BOX && (map[y][x / 2 + 1] == ROAD || map[y][x / 2 + 1] == TARGET));
        default:
            break;
    }
}

bool gameStatusIsNotStop() {
    if (allTargetCleared()) {
        win();
        return false;
    }
    return true;
}

bool allTargetCleared() {
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if(map[i][j]==TARGET) return false;
        }
    }
    return true;
}

void win() {
    char message[100];
    sprintf(message, "Your Step: %d", stepCC);
    MessageBox(0, message, "you win!!!!!", 0);
    //exit(0);
}
