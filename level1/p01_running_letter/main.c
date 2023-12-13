#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int getWidth() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
    return info.srWindow.Right - info.srWindow.Left;
}
int main(void){
    int letter_position=0;
    int step=1;
    while(1)
    {
        for(int i = 0;i < getWidth() - 10;i++)
        {
            for (int j = 0; j < letter_position; j++)
            {
                printf(" ");
            }
            printf("Hello_World");
            Sleep(1);
            system("cls");
            letter_position += step;
        }
        step*=-1;
    }
}
