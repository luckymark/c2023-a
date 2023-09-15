#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

CONSOLE_SCREEN_BUFFER_INFO csbi;
const int LOOP_NUM=100000;
int windowsWidth;
const char *words = "hello world";
const int wordsWidth = 11;

void init();

//init the width for the crash detect
int initWindowsInfo();

void core();

void moveCur(int x);

void inVisCursor();


int main() {
    init();
    for (int i = 0; i < LOOP_NUM; ++i)
        core();

    system("pause");
    return 0;
}

void core() {
    for (int i = 0; i < windowsWidth - wordsWidth; ++i) {
        moveCur(i);
        putchar(' ');
        printf("%s", words);
        Sleep(50);
    }
    for (int i = windowsWidth - wordsWidth - 1; i >= 0; --i) {
        moveCur(i);
        printf("%s", words);
        putchar(' ');
        Sleep(50);
    }
}


void moveCur(int x) {
    COORD pos = {(short)x,0};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}


void init() {
    windowsWidth = initWindowsInfo();
    inVisCursor();

}



void inVisCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);

}


int initWindowsInfo() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    //try to get the number of the character in row
    if (GetConsoleScreenBufferInfo(console, &csbi)) {
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        return width;
    }

    fprintf(stderr, "获取控制台信息失败\n");
    system("pause");
    exit(1);
}

