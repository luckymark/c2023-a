#include "maze.h"
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
            else
                printf("  ");
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
    int ch2=_getch();
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
    if (maze[(*pi).y + dy][(*pi).x + dx] != 0)
    {
        gotoxy(2 * (*pi).x, (*pi).y);
        printf("  ");
        (*pi).x = (*pi).x + dx;
        (*pi).y = (*pi).y + dy;
        gotoxy(2 * (*pi).x, (*pi).y);
        Color(4);
        printf("&");
        Color(7);
    }

}
void Menu()
{
    gotoxy(2*SIDE+5,0);
    printf("Welcome to MAZE game!");
    gotoxy(2*SIDE+5,1);
    printf("Please choose:");
    gotoxy(2*SIDE+5,2);
    printf("1.play game    2.exit     ");
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
void Find_way(int maze[SIDE + 2][SIDE + 2], int way[SIDE + 2][SIDE + 2], int x, int y, Player player,int count)
{

    if (player.y == y && player.x == x)
    {
        maze[y][x] = -1;
        way[y][x] = count;
        return;
    }
    if (maze[y][x] == 1)
    {
        maze[y][x] = -1;
        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
                case 0:
                    Find_way(maze, way, x - 1, y, player, count + 1);
                    break;
                case 1:
                    Find_way(maze, way, x, y + 1, player, count + 1);
                    break;
                case 2:
                    Find_way(maze, way, x, y - 1, player, count + 1);
                    break;
                case 3:
                    Find_way(maze, way, x + 1, y, player, count + 1);
                    break;
                default:
                    printf("error");
            }

        }
    }
    way[y][x] = count;
}
void Print_way(int way[SIDE + 2][SIDE + 2], int maze[SIDE + 2][SIDE + 2], Player player,int out)
{
    int x = player.x;
    int y = player.y;
    for (int i = 0; i < SIDE + 2; i++)
    {
        for (int j = 0; j < SIDE + 2; j++)
        {
            if (maze[i][j] == 0)
                way[i][j] = 0;
        }
    }
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            int dx = 0, dy = 0;
            switch(i)
            {
                case 0:
                    dx = 1;
                    break;
                case 1:
                    dy = 1;
                    break;
                case 2:
                    dy = -1;
                    break;
                case 3:
                    dx = -1;
                    break;
                default:
                    printf("error");
            }
            if (way[y][x] - way[y + dy][x + dx] == 1)
            {
                y = y + dy;
                x = x + dx;
                maze[y][x] = 4;
                break;
            }
        }
        if (x == SIDE && y == out)
        {
            break;
        }

    }
}
