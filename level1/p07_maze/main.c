//请使用外部控制台，不要用clion带的终端
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#define WIDTH 31
#define HEIGHT 12
#define WINX 29
#define WINY 11
char map[2000] = {"++++++++++++++++++++++++++++++\n   +                         +\n+  +                         +\n+  +                         +\n+  +                         +\n+  ++++++++++++++++++        +\n+  +            +            +\n+  +            +            +\n+  +            +            +\n+                            +\n+                            >\n++++++++++++++++++++++++++++++\n"};
int x = 1;
int y = 2;
int iswin = 0;
void mgoto(int sx, int sy) {
    COORD pos = {sx,sy};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
void loop()
{
    map[x-1 + (y-1) * WIDTH] = 'm';
    //system("cls"); //一闪一闪的很难受
    mgoto(0,0); //代替清屏
    printf("%s", map);
    char input = getch();
    printf("%d,%d",x,y);
    if(x == WINX && y == WINY){
        printf("\n You win!\n");
        iswin = 1;
    }
    switch(input)
    {
        case 'a':
            if(x > 1 && map[x-1-1 + (y-1) * WIDTH] != '+')
            {
                map[x-1 + (y-1) * WIDTH] = ' ';
                x -= 1;
            }
            break;
        case 'w':
            if(y > 1 && map[x-1 + (y-1-1) * WIDTH] != '+')
            {
                map[x-1 + (y-1) * WIDTH] = ' ';
                y -= 1;
            }
            break;
        case 's':
            if(y < HEIGHT && map[x-1 + (y-1+1) * WIDTH] != '+')
            {
                map[x-1 + (y-1) * WIDTH] = ' ';
                y += 1;
            }
            break;
        case 'd':
            if(x < WIDTH-1 && map[x-1+1 + (y-1) * WIDTH] != '+')
            {
                map[x-1 + (y-1) * WIDTH] = ' ';
                x += 1;
            }
            break;
    }
}
int main()
{
    printf("%s",map);
    while(iswin == 0)
    {
        loop();
        Sleep(10);
    }
    return 0;
}