#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define WIDTH 31
#define HEIGHT 12
int score = 100;
int winx;
int winy;
char map[2000];
int boxnum;
int boxx[100],boxy[100],is[100];
int x = 1;
int y = 2;
int level = 1;
int iswin = 0;
int winnum = 0;
char s[2000];
void start()
{
    memset(is,0,sizeof(is));
    score = 100;
    x = 1;
    y = 2;
    winnum = 0;
    FILE* f;
    char name[40] = "";
    strcat(name,"level");
    char ss[200];
    itoa(level,ss,10);
    strcat(name,ss);
    strcat(name,".txt");
    f = fopen(name,"r");
    //fgets(s, 10, f);
    //int number = atoi(s);
    memset(s,0,sizeof(s));
    fgets(s, 2000, f);
    //printf("%s",s);
    //strcpy(s,"++++++++++++++++++++++++++++++@   +                         +@+  +                         +@+  +                         +@+  +                         +@+  ++++++++++++++++++        +@+  +            +            +@+  +            +            +@+  +            +            +@+                            +@+                            +@++++++++++++++++++++++++++++++@");
    int i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == '@')
            s[i] = '\n';
        i++;
    }
    //printf("%s",s);
    strcpy(map,s);
    fgets(s, 10, f);
    boxnum = atoi(s);
    for(int i = 0; i<boxnum;i++)
    {
        fgets(s, 10, f);
        boxx[i] = atoi(s);
        fgets(s, 10, f);
        boxy[i] = atoi(s);
    }
    fgets(s, 10, f);
    winx = atoi(s);
    fgets(s, 10, f);
    winy = atoi(s);
    fclose(f);
}
void mgoto(int sx, int sy) {
    COORD pos = {sx,sy};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
void next()
{
    FILE* f;
    f = fopen("score.txt", "w");
    char ss[4];
    itoa(score,ss,10);
    fputs("score:",f);
    fputs(ss,f);
    fputs("\n",f);
    fclose(f);
    system("cls");
    level++;
    printf("score:%d",score);
    if(level == 3)
    {
        system("cls");
        printf("you win");
        iswin = 1;
    }
    Sleep(2000);
    start();
    return;
}
void loop()
{
    if(score<=0)
    {
        system("cls");
        printf("you lost");
        Sleep(10000);
        iswin = 1;
    }
    if(winnum == boxnum)
    {
        mgoto(0,0);
        next();
    }
    map[winx-1 + (winy-1) * WIDTH] = '!';
    for(int i = 0; i < boxnum; i++)
    {
        if(is[i] == 1)
        {
            continue;
        }
        if(boxx[i] == winx && boxy[i] == winy)
        {
            winnum++;
            is[i] = 1;
        }
        map[boxx[i]-1 + (boxy[i]-1) * WIDTH] = 'a';
        //printf("%d\n",boxx[i]-1 + (boxy[i]-1) * WIDTH);
    }
    map[x-1 + (y-1) * WIDTH] = 'm';
    //system("cls"); //一闪一闪的很难受
    mgoto(0,0); //代替清屏
    printf("%s", map);
    char input = getch();
    printf("score:%03d  \n",score);
    /*
    if(x == WINX && y == WINY){
        printf("\n You win!\n");
        iswin = 1;
    }
    */
    map[x-1 + (y-1) * WIDTH] = ' ';
    map[winx-1 + (winy-1) * WIDTH] = ' ';
    switch(input)
    {
        case 'a':
            if(x > 1 && map[x-1-1 + (y-1) * WIDTH] == ' ')
            {
                map[x-1 + (y-1) * WIDTH] = ' ';
                x -= 1;
                score--;
            }
            else if(x > 1 && map[x-1-1 + (y-1) * WIDTH] == 'a' && map[x-1-2 + (y-1) * WIDTH] == ' ')
            {
                map[x-1-1 + (y-1) * WIDTH] = ' ';
                x -= 1;
                score--;
                for(int i = 0; i < boxnum; i++)
                {
                    if(boxx[i] == x && boxy[i] == y)
                    {
                        boxx[i] -= 1;
                    }
                }
            }
            break;
        case 'w':
            if(y > 1 && map[x-1 + (y-1-1) * WIDTH] == ' ')
            {
                map[x-1 + (y-1) * WIDTH] = ' ';
                y -= 1;
                score--;
            }
            else if(y > 1 && map[x-1 + (y-1-1) * WIDTH] == 'a' && map[x-1 + (y-1-2) * WIDTH] == ' ')
            {
                map[x-1 + (y-1-1) * WIDTH] = ' ';
                y -= 1;
                score--;
                for(int i = 0; i < boxnum; i++)
                {

                    if(boxx[i] == x && boxy[i] == y)
                    {
                        boxy[i] -= 1;
                    }
                }
            }
            break;
        case 's':
            if(y < HEIGHT && map[x-1 + (y-1+1) * WIDTH] == ' ')
            {
                map[x-1 + (y-1) * WIDTH] = ' ';
                y += 1;
                score--;
            }
            else if(y < HEIGHT && map[x-1 + (y-1+1) * WIDTH] == 'a' && map[x-1 + (y-1+2) * WIDTH] == ' ')
            {
                map[x-1 + (y-1+1) * WIDTH] = ' ';
                y += 1;
                score--;
                for(int i = 0; i < boxnum; i++)
                {
                    if(boxx[i] == x && boxy[i] == y)
                    {
                        boxy[i] += 1;
                    }
                }
            }
            break;
        case 'd':
            if(x < WIDTH-1 && map[x-1+1 + (y-1) * WIDTH] == ' ')
            {
                map[x-1 + (y-1) * WIDTH] = ' ';
                x += 1;
                score--;
            }
            else if(x < WIDTH-1 && map[x-1+1 + (y-1) * WIDTH] == 'a' && map[x-1+2 + (y-1) * WIDTH] == ' ')
            {
                map[x-1+1 + (y-1) * WIDTH] = ' ';
                x += 1;
                score--;
                for(int i = 0; i < boxnum; i++)
                {
                    if(boxx[i] == x && boxy[i] == y)
                    {
                        boxx[i] += 1;
                    }
                }
            }
            break;
    }
}
int main()
{
    start();
    printf("%s",map);
    while(iswin == 0)
    {
        loop();
        Sleep(5);
    }
    return 0;
}