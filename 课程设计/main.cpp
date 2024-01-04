#include "Gobang.h"

ExMessage msg = {0};
int count = 0;
extern int sign;

int main() {
    //play_music("C:\\vs code\\Gobang\\BGM.mp3",30, true);
    menu1();
    int input;
    Button play1 = {200, 600, 220, 60};
    Button play2 = {600, 600, 220, 60};
    while (true) {
        if (peekmessage(&msg, EX_MOUSE)) {
            BeginBatchDraw();
            if (in_button_area(play1, msg))
                print_button(play1, "you first", LIGHTRED, RGB(50, 130, 253), 40, "楷体");
            else
                print_button(play1, "you first", RGB(255, 146, 59), RGB(50, 130, 253), 40, "楷体");
            if (in_button_area(play2, msg))
                print_button(play2, "cpu first", LIGHTRED, RGB(50, 130, 253), 40, "楷体");
            else
                print_button(play2, "cpu first", RGB(255, 146, 59), RGB(50, 130, 253), 40, "楷体");
            EndBatchDraw();
            if (is_press(play1, msg)) {
                input = 1;
                cleardevice();
                break;
            }
            if (is_press(play2, msg)) {
                input = 2;
                cleardevice();
                break;
            }
        }
    }
    print_board();
    int **board = (int **) calloc(SIDE, sizeof(int *));
    init_board(board);
    Stack *s = creat_stack(225);
    if (input == 1) {
        srand((unsigned int) time(NULL));
        while (true) {
            move(msg, board, &count, Black, s);
            //play_music("C:\\vs code\\Gobang\\chess.mp3", 800, false);
            if (is_win(board, Black)) {
                Button win = {400, 400, 0, 0};
                print_button(win, "You are winning", CYAN, LIGHTRED, 70, "黑体");
                break;
            }
            if (rand() % 2) {
                sign = 1;
                ai_move(board, 4, White, 2, &count, s);
            } else {
                sign = -1;
                ai_move(board, 3, White, 6, &count, s);
            }
            //play_music("C:\\vs code\\Gobang\\chess.mp3", 800, false);
            if (is_win(board, White)) {
                Button lose = {400, 400, 0, 0};
                print_button(lose, "You are losing", CYAN, LIGHTRED, 70, "黑体");
                break;
            }
        }
    } else {
        int x = 8, y = 8;
        count++;
        Button num = {50 * x, 50 * y, 0, 0};
        setfillcolor(BLACK);
        setlinecolor(BLACK);
        fillcircle(50 * x, 50 * y, 20);
        char str[4];
        sprintf(str, "%d", count);
        print_button(num, str, LIGHTRED, LIGHTRED, 30, "楷体");
        board[x - 1][y - 1] = Black;
        Step step = {x - 1, y - 1};
        stack_push(s, &step);
        srand((unsigned int) time(NULL));
        while (true) {
            move(msg, board, &count, White, s);
            //play_music("C:\\vs code\\Gobang\\chess.mp3", 800, false);
            if (is_win(board, White)) {
                Button win = {400, 400, 0, 0};
                print_button(win, "You are winning", CYAN, LIGHTRED, 70, "黑体");
                break;
            }
            if (rand() % 2) {
                sign = 1;
                ai_move(board, 4, Black, 2, &count, s);
            } else {
                sign = -1;
                ai_move(board, 3, Black, 6, &count, s);
            }
            //play_music("C:\\vs code\\Gobang\\chess.mp3", 800, false);
            if (is_win(board, Black)) {
                Button lose = {400, 400, 0, 0};
                print_button(lose, "You are losing", CYAN, LIGHTRED, 70, "黑体");
                break;
            }
        }
    }
    while (true) {
        if (peekmessage(&msg, EX_KEY) && msg.message == WM_KEYDOWN)
            break;
    }
    return 0;
}
