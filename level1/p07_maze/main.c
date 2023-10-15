#include "maze.h"
int main()
{
    while (1)
    {
        int input, in, out;
        int maze[SIDE + 2][SIDE + 2];
        int way[SIDE + 2][SIDE + 2] = {0};
        Menu();
        scanf_s("%d", &input);
        if (input == 1)
        {
            gotoxy(2*SIDE+5,3);
            printf("Please remember:'#' is wall,'&' is player,'@' is exit");
            gotoxy(2*SIDE+5,4);
            printf("If you can't get out of the maze,please press 'Tab' to find way");
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
            gotoxy(0,0);
            Print(maze, player);
            Player* pi = &player;
            clock_t start = clock();
            int temp=-1;
            while (1)
            {
                clock_t point = clock();
                int time = (point - start) / 1000;
                if(time==temp+1)
                {
                    temp=time;
                    gotoxy(0, 0);
                    printf("The time you use now is %d min %2d s", temp/60,temp%60);
                }
                if (_kbhit())
                {
                    int ch1 = _getch();
                    if (ch1 == 224)
                    {
                        Move(maze, pi, SIDE, out);
                    }
                    else if (ch1 == 9)
                    {
                        Find_way(maze,way, SIDE, out, player,0);
                        gotoxy(0, 0);
                        Print_way(way,maze, player, out);
                        Print(maze, player);
                    }
                }
                if (maze[player.y][player.x] == 3)
                    break;
            }
            Color(6);
            gotoxy(2*SIDE+5,5);
            printf("Congratulation!");
            gotoxy(2*SIDE+5,6);
            printf("You are winning.");
            Color(7);
            Sleep(5000);
            system("cls");
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
