#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include"game.h"

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
    iswin = 0;
    level = 1;
    start();
    printf("%s",map);
    while(iswin == 0)
    {
        loop();
        Sleep(5);
    }
    return 0;
}