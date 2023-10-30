#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include"game.h"
void start()
{
    memset(is,0,sizeof(is));
    score = 100;
    x = 1;
    y = 2;
    winnum = 0;
    FILE* f;
    char name[100] = "";
    memset(name,0,sizeof(name));
    strcat(name,".\\..\\..\\level1\\p08_push_boxes\\level");
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