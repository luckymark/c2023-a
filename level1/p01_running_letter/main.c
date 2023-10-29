#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int getWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
    return info.srWindow.Right - info.srWindow.Left;
}
int main()
{
    char letter;
    printf("Enter a letter.\n");
    scanf("%c", &letter);
    int position = 1;
    for (int i = 0; i <= position; i++)
    {
        if (((position - position % getWidth()) / getWidth()) % 2 == 0)
        {
            system("cls");
            for (int j = 0; j <= i%getWidth(); j++)
            {
                printf(" ");
            }
            printf("%c", letter);
            position++;
            Sleep(10);
        }
        else
        {
            system("cls");
            for (int j = 0; j <= getWidth()-i%getWidth(); j++)
            {
                printf(" ");
            }
            printf("%c", letter);
            position++;
            Sleep(10);
        }
    }
    return 0;
}