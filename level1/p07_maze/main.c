#define SIDE 20 //宏定义方便改变迷宫的边长来改变迷宫的难度
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
int Find_way(int maze[SIDE + 2][SIDE + 2], int x, int y, Player player);

void Init_maze(int maze[SIDE + 2][SIDE + 2])
{
    for (int i = 0; i < SIDE + 2; i++)
    {
        for (int j = 0; j < SIDE + 2; j++)
        {
            maze[i][j] = 0;
        }
    }
    for (int i = 0; i < SIDE + 2; i++)
    {
        maze[0][i] = 2;
        maze[SIDE + 1][i] = 2;
        maze[i][0] = 2;
        maze[i][SIDE + 1] = 2;
    }
}
void Form_maze(int maze[SIDE + 2][SIDE + 2], int x, int y)
{

    if (maze[x][y] == 0)
    {
        if (maze[x + 1][y] + maze[x - 1][y] + maze[x][y + 1] + maze[x][y - 1] < 2)
        {
            maze[x][y] = 1;
            int arr[4] = { 4,4,4,4 };
            for (int i = 0; i < 4; i++)
            {
                flag:
                {
                    int num = (rand()) % 4;
                    if (arr[0] == num || arr[1] == num || arr[2] == num || arr[3] == num)
                        goto flag;
                    arr[i] = num;
                    switch (num)
                    {
                        case 0:
                            Form_maze(maze, x + 1, y);
                            break;
                        case 1:
                            Form_maze(maze, x - 1, y);
                            break;
                        case 2:
                            Form_maze(maze, x, y + 1);
                            break;
                        case 3:
                            Form_maze(maze, x, y - 1);
                            break;
                        default:
                            printf("error");
                    }
                }

            }
        }
    }
}
void Print(int maze[SIDE + 2][SIDE + 2], Player player)
{
    for (int i = 0; i < SIDE + 2; i++)
    {
        for (int j = 0; j < SIDE + 2; j++)
        {
            if (i == player.y && j == player.x)
            {
                Color(4);
                printf("& ");
            }
            else if (maze[i][j] == 0)
            {
                Color(9);
                printf("# ");
            }
            else if (maze[i][j] == 1)
            {
                Color(9);
                printf("  ");
            }
            else if (maze[i][j] == 3)
            {
                Color(6);
                printf("@ ");
            }
            else if (maze[i][j] == 4)
            {
                Color(2);
                printf("* ");
            }
        }
        printf("\n");
    }
    Color(7);
}
int In(int maze[SIDE + 2][SIDE + 2])
{
    int in;
    while (1)
    {
        in = (rand() % (SIDE - 2)) + 2;
        if (maze[in][2] == 1)
            break;
    }
    return in;
}
int Out(int maze[SIDE + 2][SIDE + 2])
{
    int out;
    while (1)
    {
        out = (rand() % (SIDE - 2)) + 2;
        if (maze[out][SIDE - 1] == 1)
            break;
    }
    return out;
}
void Move(int maze[SIDE + 2][SIDE + 2], Player* pi, int x, int y)
{
    if (_kbhit)
    {
        int ch1 = _getch();
        if (ch1 == 224)
        {
            int ch2 = _getch();
            int dx = 0, dy = 0;
            switch (ch2)
            {
                case UP:
                    dy = -1;
                    break;
                case DOWN:
                    dy = 1;
                    break;
                case LEFT:
                    dx = -1;
                    break;
                case RIGHT:
                    dx = 1;
                    break;
            }
            if (maze[(*pi).y + dy][(*pi).x + dx] != 0 )
            {
                gotoxy(2 * (*pi).x-2, (*pi).y);
                printf("  ");
                (*pi).x = (*pi).x + dx;
                (*pi).y = (*pi).y + dy;
                gotoxy(2 * (*pi).x-2, (*pi).y);
                Color(4);
                printf("&");
                Color(7);
            }
        }
        else if (ch1 == 9)
        {
            gotoxy(1, 0);
            while (1)
            {
                Find_way(maze, x, y, *pi);
                if (maze[(*pi).y][(*pi).x] != 4)
                {
                    for (int i = 0; i < SIDE + 2; i++)
                    {
                        for (int j = 0; j < SIDE + 2; j++)
                        {
                            if (maze[i][j] == 4)
                                maze[i][j] = 1;
                        }
                    }
                }
                else
                    break;
            }
            Print(maze, *pi);
        }
    }
}
void Menu()
{
    printf("Welcome to MAZE game!\n");
    printf("Please choose:\n1.play game\n2.exit\n");
}
void Color(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int Find_way(int maze[SIDE + 2][SIDE + 2], int x, int y, Player player)
{
    int count = 0;
    if (player.y == y && player.x == x)
    {
        maze[y][x] = 4;
        goto arrow;
    }
    if (maze[y][x] == 1)
    {
        count++;
        maze[y][x] = 4;
        int arr[4] = { 4,4,4,4 };
        for (int i = 0; i < 4; i++)
        {
            flag:
            {
                int num = (rand()) % 4;
                if (arr[0] == num || arr[1] == num || arr[2] == num || arr[3] == num)
                    goto flag;
                arr[i] = num;
                switch (num)
                {
                    case 0:
                        if (Find_way(maze, x + 1, y, player) == 1)
                            goto arrow;
                        break;
                    case 1:
                        if (Find_way(maze, x - 1, y, player) == 1)
                            goto arrow;
                        break;
                    case 2:
                        if (Find_way(maze, x, y + 1, player) == 1)
                            goto arrow;
                        break;
                    case 3:
                        if (Find_way(maze, x, y - 1, player) == 1)
                            goto arrow;
                        break;
                    default:
                        printf("error");
                }
            }
        }
    }
    arrow:;
    return count;
}

int main()
{
    while (1)
    {
        int input, in, out;
        int maze[SIDE + 2][SIDE + 2];
        Menu();
        scanf_s("%d", &input);
        if (input == 1)
        {
            printf("Please remember:'#' is wall,'&' is player,'@' is exit\n");
            printf("If you can't get out of the maze,please press 'Tab' to find way\n");
            Init_maze(maze);
            srand((unsigned int)time(NULL));
            int ori1 = rand() % (SIDE - 2) + 2;
            int ori2 = rand() % (SIDE - 2) + 2;
            Form_maze(maze, ori1, ori2);
            in = In(maze);
            Player player = { 1,in };
            out = Out(maze);
            maze[out][SIDE] = 1;
            maze[out][SIDE + 1] = 3;
            Print(maze, player);
            Player* pi = &player;
            Move(maze, pi, SIDE, out);
            system("cls");
            Print(maze, player);
            while (1)
            {
                Move(maze, pi, SIDE, out);
                if (maze[player.y][player.x] == 3)
                    break;
            }
            system("cls");
            Color(6);
            printf("Congratulation!\nYou are winning.\n\n");
            Color(7);
        }
        else if (input == 2)
            break;
        else
        {
            printf("ERROR\n");
        }
    }
    return 0;
}
