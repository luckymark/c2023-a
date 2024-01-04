#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int getWidth() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
    return info.srWindow.Right - info.srWindow.Left;
}
int main(void){
    int i,j=0,k,l,num=1;
    for(i=0;i<getWidth() - 10;i++)
    {
        for(k=0;k<getWidth() - 10;k++)
        {
            for (l = 0; l < j; l++)
            {
                printf(" ");
            }
            printf("A");
            Sleep(20);
            system("cls");
            j += num;
        }
        num*=-1;
    }
    system("pause");
    return 0;
}