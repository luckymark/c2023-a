#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
int main()
{
    CONSOLE_SCREEN_BUFFER_INFO c;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);
    int x = c.srWindow.Right - c.srWindow.Left;
    int now = 1;
    int step = 1;
    while(1)
    {
        for(int i = 1; i <= x+3; i++)
        {
            if(i == now)
            {
                printf("apple");
                i += 5;
            }
            else
            {
                printf(" ");
            }
        }
        now += step;
        if(now >= x - 5)
        {
            step = -1;
        }
        else if(now <= 1)
        {
            step = 1;
        }
        Sleep(20);
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);
        x = c.srWindow.Right - c.srWindow.Left;
        system("cls");
    }
    return 0;
}
