#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

HANDLE console;//窗口句柄
COORD pPos = {};//保存人物坐标信息（屏幕坐标）
CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;//保存窗口信息
COORD ZERO_COORD = {0, 0};

enum {
    WALL = 1 << 0,
    TARGET = 1 << 1,
    BOX = 1 << 2,
    PERSON = 1 << 3
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

void drawMap();

//判断移动是否合法 输入的是目标map坐标
bool invalidMove(int x, int y, int dir);

//赢了游戏之后程序的响应
void win();

//清屏函数
void clearScreen();

//移动函数
void Move(int key);

//读取地图内容
void readMap();

//初次识别人的位置并存储其位置信息
void initPerson();

//检测所有的目标都已经清除了
bool allTargetCleared();

void printMenu();

void updateCoord(int x_map, int y_map);

int main() {
    while (1) {
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
    drawMap();

    //隐藏光标
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);

}

void initPerson() {
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (map[i][j] & PERSON) {
                pPos.X = j * 2;
                pPos.Y = i;
            }
        }
    }
}

void readMap() {
    char fileDir[30];
    sprintf(fileDir, "../../level1/p08_push_boxes/map/%d.map", targetLevel);
    fp = fopen(fileDir, "r");
    fscanf_s(fp, "%d %d", &WIDTH, &HIGH);
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            fscanf_s(fp, "%d", &map[i][j]);
        }
    }
}

void clearScreen() {
    SetConsoleCursorPosition(console, ZERO_COORD);
    system("cls");
}


void drawMap() {
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            updateCoord(j, i);
        }
    }
}


void kbEvent() {
    if (kbhit()) {
        Move(getch());
    }
}

void Move(int key) {
    switch (key) {
        case 72://上
            if (invalidMove(pPos.X, pPos.Y - 1, Up)) {
                return;
            }
            //如果上面一格的是箱子
            if (map[pPos.Y - 1][pPos.X / 2] & BOX) {
                map[pPos.Y - 2][pPos.X / 2] |= BOX;//将上面两格的标记为箱子
                map[pPos.Y - 1][pPos.X / 2] &= ~BOX;//将上面一格的取消标记
                updateCoord(pPos.X / 2, pPos.Y - 2);//打印更新上两格的状态
            }
            //打印更新上面一格和原来的格子的状态
            map[pPos.Y - 1][pPos.X / 2] |= PERSON;
            map[pPos.Y][pPos.X / 2] &= ~PERSON;
            updateCoord(pPos.X / 2, pPos.Y - 1);
            updateCoord(pPos.X / 2, pPos.Y);
            //记录人的移动
            pPos.Y -= 1;
            stepCC++;
            break;

        case 75://左
            if (invalidMove(pPos.X - 2, pPos.Y, Left)) {
                return;
            }
            if (map[pPos.Y][pPos.X / 2 - 1] & BOX) {
                map[pPos.Y][pPos.X / 2 - 2] |= BOX;
                map[pPos.Y][pPos.X / 2 - 1] &= ~BOX;
                updateCoord(pPos.X / 2 - 2, pPos.Y);
            }
            map[pPos.Y][pPos.X / 2 - 1] |= PERSON;
            map[pPos.Y][pPos.X / 2] &= ~PERSON;
            updateCoord(pPos.X / 2 - 1, pPos.Y);
            updateCoord(pPos.X / 2, pPos.Y);
            pPos.X -= 2;
            stepCC++;
            break;


        case 77://右
            if (invalidMove(pPos.X + 2, pPos.Y, Right)) {
                return;
            }
            if (map[pPos.Y][pPos.X / 2 + 1] & BOX) {
                map[pPos.Y][pPos.X / 2 + 2] |= BOX;
                map[pPos.Y][pPos.X / 2 + 1] &= ~BOX;
                updateCoord(pPos.X / 2 + 2, pPos.Y);
            }
            map[pPos.Y][pPos.X / 2 + 1] |= PERSON;
            map[pPos.Y][pPos.X / 2] &= ~PERSON;
            updateCoord(pPos.X / 2 + 1, pPos.Y);
            updateCoord(pPos.X / 2, pPos.Y);
            pPos.X += 2;
            stepCC++;
            break;

        case 80://下
            if (invalidMove(pPos.X, pPos.Y + 1, Down)) {
                return;
            }
            if (map[pPos.Y + 1][pPos.X / 2] & BOX) {
                map[pPos.Y + 2][pPos.X / 2] |= BOX;
                map[pPos.Y + 1][pPos.X / 2] &= ~BOX;
                updateCoord(pPos.X / 2, pPos.Y + 2);
            }
            map[pPos.Y + 1][pPos.X / 2] |= PERSON;
            map[pPos.Y][pPos.X / 2] &= ~PERSON;
            updateCoord(pPos.X / 2, pPos.Y + 1);
            updateCoord(pPos.X / 2, pPos.Y);
            pPos.Y += 1;
            stepCC++;
            break;

        default:
            break;
    }
}

void updateCoord(int x_map, int y_map) {
    COORD tmpCoord = {x_map * 2, y_map};
    SetConsoleCursorPosition(console, tmpCoord);
    if (map[y_map][x_map] & TARGET) printf("\033[40;32m");
    if (map[y_map][x_map] & WALL) {
        printf("墙\033[0m");
        return;
    }
    if (map[y_map][x_map] & BOX) {
        printf("箱\033[0m");
        return;
    }
    if (map[y_map][x_map] & PERSON) {
        printf("人\033[0m");
        return;
    }
    if (map[y_map][x_map] & TARGET) {
        printf("标\033[0m");
        return;
    }
    printf("  \033[0m");
}

bool invalidMove(int x, int y, int dir) {
    switch (dir) {
        case Up:
            return (map[y][x / 2] & WALL) || ((map[y][x / 2] & BOX) && (map[y - 1][x / 2] & (WALL | BOX)));
        case Down:
            return (map[y][x / 2] & WALL) || ((map[y][x / 2] & BOX) && (map[y + 1][x / 2] & (WALL | BOX)));
        case Left:
            return (map[y][x / 2] & WALL) || ((map[y][x / 2] & BOX) && (map[y][x / 2 - 1] & (WALL | BOX)));
        case Right:
            return (map[y][x / 2] & WALL) || ((map[y][x / 2] & BOX) && (map[y][x / 2 + 1] & (WALL | BOX)));
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
            if ((map[i][j] & TARGET) && (!(map[i][j] & BOX))) return false;
        }
    }
    return true;
}

void win() {
    char scoreFile[100] = "../../level1/p08_push_boxes/score.table";
    FILE *fsm = fopen(scoreFile, "r");
    int scoreTable[10] ;
    memset(scoreTable,0x7f,sizeof scoreTable);
    for (int i = 0; i < 2; ++i) {
        fscanf_s(fsm,"%d",&scoreTable[i]);
    }

    char message[100];
    scoreTable[targetLevel-1] = min(scoreTable[targetLevel-1], stepCC);
    sprintf(message, "Your Step: %d\nBest score: %d", stepCC, scoreTable[targetLevel-1]);
    MessageBox(0, message, "you win!!!!!", 0);
    fsm = fopen(scoreFile, "w");
    for (int i = 0; i < 2; ++i) {
        fprintf(fsm,"%d\n", scoreTable[i]);
    }
    fclose(fsm);
}

#pragma clang diagnostic pop