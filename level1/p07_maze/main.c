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
            if (_kbhit)
            {
                int ch1 = _getch();
                if (ch1 == 224)
                {
                    Move(maze, pi, SIDE, out);
                }
            }
            system("cls");
            Print(maze, player);
            while (1)
            {
                if (_kbhit)
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
