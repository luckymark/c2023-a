#include "Gobang.h"

int i = 1;

void menu1() {
    IMAGE img;
    Button title = {400, 250, 290, 50};
    Button play1 = {200, 600, 220, 60};
    Button play2 = {600, 600, 220, 60};
    initgraph(800, 700, 1);
    setbkcolor(WHITE);
    cleardevice();
    print_button(title, "Gobang game", RGB(50, 160, 255), LIGHTRED, 50, "楷体");
    print_button(play1, "you first", RGB(255, 146, 59), RGB(50, 130, 253), 40, "楷体");
    print_button(play2, "cpu first", RGB(255, 146, 59), RGB(50, 130, 253), 40, "楷体");
}

void print_button(Button b, const char *text, int bk_color, int text_color, int text_size, const char *text_style) {
    setbkmode(TRANSPARENT);
    settextstyle(text_size, 0, text_style);
    setfillcolor(bk_color);
    settextcolor(text_color);
    fillroundrect(b.x - b.w / 2, b.y - b.h / 2, b.x + b.w / 2, b.y + b.h / 2, 0.8 * b.h, 0.8 * b.h);
    outtextxy(b.x - textwidth(text) / 2, b.y - textheight(text) / 2, text);
}

int in_button_area(Button b, ExMessage msg) {
    if (msg.x > b.x - b.w / 2 && msg.x < b.x + b.w / 2 && msg.y > b.y - b.h / 2 && msg.y < b.y + b.h / 2)
        return 1;
    else
        return 0;
}

int is_press(Button b, ExMessage msg) {
    if (in_button_area(b, msg) && msg.message == WM_LBUTTONUP)
        return 1;
    else
        return 0;
}

void print_board() {
    initgraph(800, 800);
    setbkcolor(WHITE);
    cleardevice();
    IMAGE board;
    loadimage(&board, "C:/vs code/Gobang/board.png", 800, 800);
    putimage(0, 0, &board);
}
//void play_music(const char* music, int volumn , bool is_re)
//{
//    char cmd1[100] = { 0 };
//    char cmd2[100] = { 0 };
//    char cmd3[100] = { 0 };
//    sprintf(cmd1, "open \"%s\" alias bgm%d", music,i);
//    if (is_re)
//        sprintf(cmd2, "play bgm%d repeat", i);
//    else
//        sprintf(cmd2, "play bgm%d", i);
//    sprintf(cmd3, "setaudio bgm%d volume to %d", i, volumn);
//    MCIERROR ret1, ret2, ret3;
//    ret1 = mciSendString(cmd1, NULL, 0, NULL);
//    if (ret1 != 0)
//    {
//        char err[100] = { 0 };
//        mciGetErrorString(ret1, err, sizeof(err));
//        printf("open:%s\n", err);
//    }
//    mciSendString(cmd2, NULL, 0, NULL);
//    ret2 = mciSendString(cmd2, NULL, 0, NULL);
//    if (ret2 != 0)
//    {
//        char err[100] = { 0 };
//        mciGetErrorString(ret2, err, sizeof(err));
//        printf("play:%s\n", err);
//    }
//    ret3 = mciSendString(cmd3, NULL, 0, NULL);
//    if (ret3 != 0)
//    {
//        char err[100] = { 0 };
//        mciGetErrorString(ret3, err, sizeof(err));
//        printf("volume:%s\n", err);
//    }
//    i++;
//}