#include "Gobang.h"

int dir[4][2] = {1, 0, 0, 1, 1, 1, -1, 1};
int sign = 1;

void init_board(int **b) {
    for (int i = 0; i < SIDE; i++) {
        b[i] = (int *) calloc(SIDE, sizeof(int));
        for (int j = 0; j < SIDE; j++)
            b[i][j] = EMPTY;
    }
}

int out_range(int x, int y) {
    if (x < 0 || x >= SIDE || y < 0 || y >= SIDE)
        return 1;
    else
        return 0;
}

int is_live(int **b, int x, int y, int player, int n) {
    if (b[x][y] == EMPTY && judge(b, x, y)) {
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = x - i; j < x - i + n; j++) {
                if (!out_range(j, y)) {
                    if (b[j][y] == player)
                        count++;
                }
            }
            if (count == n - 1) {
                if (!out_range(x - i - 1, y) && !out_range(x - i + n, y)) {
                    if (b[x - i - 1][y] == EMPTY && b[x - i + n][y] == EMPTY)
                        return 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = y - i; j < y - i + n; j++) {
                if (!out_range(x, j)) {
                    if (b[x][j] == player)
                        count++;
                }
            }
            if (count == n - 1) {
                if (!out_range(x, y - i - 1) && !out_range(x, y - i + n)) {
                    if (b[x][y - i - 1] == EMPTY && b[x][y - i + n] == EMPTY)
                        return 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = x - i, k = y - i; j < x - i + n && k < y - i + n; j++, k++) {
                if (!out_range(j, k)) {
                    if (b[j][k] == player)
                        count++;
                }
            }
            if (count == n - 1) {
                if (!out_range(x - i - 1, y - i - 1) && !out_range(x - i + n, y - i + n)) {
                    if (b[x - i - 1][y - i - 1] == EMPTY && b[x - i + n][y - i + n] == EMPTY)
                        return 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = x - i, k = y + i; j < x - i + n && k > y + i - n; j++, k--) {
                if (!out_range(j, k)) {
                    if (b[j][k] == player)
                        count++;
                }
            }
            if (count == n - 1) {
                if (!out_range(x - i - 1, y + i + 1) && !out_range(x - i + n, y + i - n)) {
                    if (b[x - i - 1][y + i + 1] == EMPTY && b[x - i + n][y + i - n] == EMPTY)
                        return 1;
                }
            }
        }
    }
    return 0;
}

int is_dead(int **b, int x, int y, int player, int n) {
    if (b[x][y] == EMPTY && judge(b, x, y)) {
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = x - i; j < x - i + n; j++) {
                if (!out_range(j, y)) {
                    if (b[j][y] == player)
                        count++;
                }
            }
            if (count == n - 1) {
                if (!out_range(x - i - 1, y) && out_range(x - i + n, y)) {
                    if (b[x - i - 1][y] == EMPTY)
                        return 1;
                }
                if (out_range(x - i - 1, y) && !out_range(x - i + n, y)) {
                    if (b[x - i + n][y] == EMPTY)
                        return 1;
                }
                if (!out_range(x - i - 1, y) && !out_range(x - i + n, y)) {
                    if (b[x - i - 1][y] + b[x - i + n][y] == -player)
                        return 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = y - i; j < y - i + n; j++) {
                if (!out_range(x, j)) {
                    if (b[x][j] == player)
                        count++;
                }
            }
            if (count == n - 1) {
                if (!out_range(x, y - i - 1) && out_range(x, y - i + n)) {
                    if (b[x][y - i - 1] == EMPTY)
                        return 1;
                }
                if (out_range(x, y - i - 1) && !out_range(x, y - i + n)) {
                    if (b[x][y - i + n] == EMPTY)
                        return 1;
                }
                if (!out_range(x, y - i - 1) && !out_range(x, y - i + n)) {
                    if (b[x][y - i - 1] + b[x][y - i + n] == -player)
                        return 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = x - i, k = y - i; j < x - i + n && k < y - i + n; j++, k++) {
                if (!out_range(j, k)) {
                    if (b[j][k] == player)
                        count++;
                }
            }
            if (count == n - 1) {
                if (!out_range(x - i - 1, y - i - 1) && out_range(x - i + n, y - i + n)) {
                    if (b[x - i - 1][y - i - 1] == EMPTY)
                        return 1;
                }
                if (out_range(x - i - 1, y - i - 1) && !out_range(x - i + n, y - i + n)) {
                    if (b[x - i + n][y - i + n] == EMPTY)
                        return 1;
                }
                if (!out_range(x - i - 1, y - i - 1) && !out_range(x - i + n, y - i + n)) {
                    if (b[x - i - 1][y - i - 1] + b[x - i + n][y - i + n] == -player)
                        return 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = x - i, k = y + i; j < x - i + n && k > y + i - n; j++, k--) {
                if (!out_range(j, k)) {
                    if (b[j][k] == player)
                        count++;
                }
            }
            if (count == n - 1) {
                if (!out_range(x - i - 1, y + i + 1) && out_range(x - i + n, y + i - n)) {
                    if (b[x - i - 1][y + i + 1] == EMPTY)
                        return 1;
                }
                if (out_range(x - i - 1, y + i + 1) && !out_range(x - i + n, y + i - n)) {
                    if (b[x - i + n][y + i - n] == EMPTY)
                        return 1;
                }
                if (!out_range(x - i - 1, y + i + 1) && !out_range(x - i + n, y + i - n)) {
                    if (b[x - i - 1][y + i + 1] + b[x - i + n][y + i - n] == -player)
                        return 1;
                }
            }
        }
    }
    return 0;
}

int is_four(int **b, int x, int y, int player) {
    if (b[x][y] == EMPTY && judge(b, x, y)) {
        for (int i = 0; i < 5; i++) {
            int count = 0;
            for (int j = x - i; j < x - i + 5; j++) {
                if (!out_range(j, y)) {
                    if (b[j][y] == player)
                        count++;
                }
            }
            if (count == 4)
                return 1;
        }
        for (int i = 0; i < 5; i++) {
            int count = 0;
            for (int j = y - i; j < y - i + 5; j++) {
                if (!out_range(x, j)) {
                    if (b[x][j] == player)
                        count++;
                }
            }
            if (count == 4)
                return 1;
        }
        for (int i = 0; i < 5; i++) {
            int count = 0;
            for (int j = x - i, k = y - i; j < x - i + 5 && k < y - i + 5; j++, k++) {
                if (!out_range(j, k)) {
                    if (b[j][k] == player)
                        count++;
                }
            }
            if (count == 4)
                return 1;
        }
        for (int i = 0; i < 5; i++) {
            int count = 0;
            for (int j = x - i, k = y + i; j < x - i + 5 && k > y + i - 5; j++, k--) {
                if (!out_range(j, k)) {
                    if (b[j][k] == player)
                        count++;
                }
            }
            if (count == 4)
                return 1;
        }
    }
    return 0;
}

int is_five(int **board, int x, int y, int player) {
    if (board[x][y] == player) {
        for (auto &i: dir) {
            int count = 1;
            for (int j = 1; j <= 4; j++) {
                int dx = i[0] * j;
                int dy = i[1] * j;
                if (out_range(x + dx, y + dy) || board[x + dx][y + dy] != player)
                    break;
                count++;
            }
            if (count == 5)
                return 1;
        }
    }
    return 0;
}

int is_win(int **board, int player) {
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (is_five(board, i, j, player))
                return 1;
        }
    }
    return 0;
}

int score(int **b, int player, int w) {
    int sum = 0;
    for (auto &t: dir) {
        int dx = t[0];
        int dy = t[1];
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                int score = 0;
                if (b[i][j] == player) {
                    score = 100;
                    for (int k = 1; k < 3; k++) {
                        if (out_range(i + k * dx, j + k * dy) || b[i + k * dx][j + k * dy] == -player) {
                            score = score / 100 * k;
                            break;
                        } else if (b[i + k * dx][j + k * dy] == player)
                            score = score * 10;
                    }
                    for (int k = 1; k < 3; k++) {
                        if (out_range(i - k * dx, j - k * dy) || b[i - k * dx][j - k * dy] == -player) {
                            score = score / 100 * k;
                            break;
                        } else if (b[i - k * dx][j - k * dy] == player)
                            score = score * 10;
                    }
                }
                sum += score;
            }
        }
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                int score = 0;
                if (b[i][j] == -player) {
                    score = 100;
                    for (int k = 1; k < 3; k++) {
                        if (out_range(i + k * dx, j + k * dy) || b[i + k * dx][j + k * dy] == player) {
                            score = score / 100 * k;
                            break;
                        } else if (b[i + k * dx][j + k * dy] == -player)
                            score = score * 10;
                    }
                    for (int k = 1; k < 3; k++) {
                        if (out_range(i - k * dx, j - k * dy) || b[i - k * dx][j - k * dy] == player) {
                            score = score / 100 * k;
                            break;
                        } else if (b[i - k * dx][j - k * dy] == -player)
                            score = score * 10;
                    }
                }
                sum -= w * score;
            }
        }
    }
    return sum;
}

int judge(int **board, int x, int y) {
    int flag = 0;
    for (auto &i: dir) {
        for (int j = -2; j < 3; j++) {
            int dx = i[0] * j;
            int dy = i[1] * j;
            if (out_range(x + dx, y + dy))
                continue;
            if (board[x + dx][y + dy] != EMPTY) {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

void move(ExMessage msg, int **board, int *count, int player, Stack *s) {
    while (true) {
        if (peekmessage(&msg, EX_MOUSE)) {
            if (msg.message == WM_LBUTTONDOWN) {
                int x = (msg.x + 25) / 50.0;
                int y = (msg.y + 25) / 50.0;
                int x1 = (msg.x + 25) / 50;
                int y1 = (msg.y + 25) / 50;
                int a = x - x1 - 0.5;
                int b = y - y1 - 0.5;
                if (a > -0.25 && a < 0.25 && b > -0.25 && b < 0.25 && board[x1 - 1][y1 - 1] == 0 && x1 > 0 && x1 < 16 &&
                    y1 > 0 && y1 < 16) {
                    (*count)++;
                    Button num = {50 * x1, 50 * y1, 0, 0};
                    setlinecolor(((BLACK + WHITE) + (BLACK - WHITE) * player) / 2);
                    setfillcolor(((BLACK + WHITE) + (BLACK - WHITE) * player) / 2);
                    fillcircle(50 * x1, 50 * y1, 20);
                    char str[4];
                    sprintf(str, "%d", *count);
                    print_button(num, str, LIGHTRED, ((WHITE + BLACK) + (WHITE - BLACK) * player) / 2, 30, "楷体");
                    board[x1 - 1][y1 - 1] = player;
                    Step step = {x1 - 1, y1 - 1};
                    stack_push(s, &step);
                    break;
                }
            }
            if (msg.message == WM_RBUTTONDOWN) {
                back_move(board, s, count, player);
                back_move(board, s, count, player);
            }
        }
    }
}

int minimax(int **b, int depth, int player, int alpha, int beta, int *Row, int *Col, int w) {
    if (depth == 0)
        return sign * score(b, player, w);
    int x = 0, y = 0;
    int flag1 = 0, flag2 = 0;
    Step st1 = {0, 0}, st2 = {0, 0};
    int glag1 = 0;
    Step t1 = {0, 0};
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (is_four(b, i, j, sign * (1 - 2 * (depth % 2)) * player)) {
                flag1++;
                st1.x = i;
                st1.y = j;
            }
            if (is_four(b, i, j, -sign * (1 - 2 * (depth % 2)) * player)) {
                glag1++;
                t1.x = i;
                t1.y = j;
            }
            if (is_live(b, i, j, sign * (1 - 2 * (depth % 2)) * player, 4)) {
                flag2++;
                st2.x = i;
                st2.y = j;
            }
        }
    }
    if (flag1) {
        x = st1.x;
        y = st1.y;
    } else if (glag1) {
        x = t1.x;
        y = t1.y;
    } else if (flag2) {
        x = st2.x;
        y = st2.y;
    } else {
        int best = MAX;
        int score;
        Stack *s1 = creat_stack(225);
        Stack *s2 = creat_stack(225);
        Stack *s3 = creat_stack(225);
        Stack *s4 = creat_stack(225);
        for (int i = SIDE - 1; i >= 0; i--) {
            for (int j = SIDE - 1; j >= 0; j--) {
                if (b[i][j] == EMPTY && judge(b, i, j)) {
                    Step temp = {i, j};
                    if (is_four(b, i, j, player) || is_four(b, i, j, -player))
                        stack_push(s1, &temp);
                    else if (is_live(b, i, j, player, 4) || is_live(b, i, j, -player, 4))
                        stack_push(s1, &temp);
                    else if (is_dead(b, i, j, player, 4) || is_dead(b, i, j, -player, 4))
                        stack_push(s2, &temp);
                    else if (is_live(b, i, j, player, 3) || is_live(b, i, j, -player, 3))
                        stack_push(s2, &temp);
                    else if (is_dead(b, i, j, player, 3) || is_dead(b, i, j, -player, 3))
                        stack_push(s3, &temp);
                    else
                        stack_push(s4, &temp);
                }
            }
        }
        int i = 0, j = 0;
        while (true) {
            if (!is_empty(s1)) {
                Step *step = stack_pop(s1);
                i = step->x;
                j = step->y;
            } else if (!is_empty(s2)) {
                Step *step = stack_pop(s2);
                i = step->x;
                j = step->y;
            } else if (!is_empty(s3)) {
                Step *step = stack_pop(s3);
                i = step->x;
                j = step->y;
            } else if (!is_empty(s4)) {
                Step *step = stack_pop(s4);
                i = step->x;
                j = step->y;
            } else
                break;
            b[i][j] = sign * (1 - 2 * (depth % 2)) * player;
            score = minimax(b, depth - 1, player, alpha, beta, nullptr, nullptr, w);
            b[i][j] = 0;
            if (score < best) {
                best = score;
                if (Row != nullptr && Col != nullptr) {
                    *Row = i + 1;
                    *Col = j + 1;
                }
                if (depth % 2 == 0 && best < beta)
                    beta = best;
                if (depth % 2 == 1 && -best > alpha)
                    alpha = -best;
            }
            if (alpha >= beta) {
                free(s1->data);
                free(s1);
                free(s2->data);
                free(s2);
                free(s3->data);
                free(s3);
                free(s4->data);
                free(s4);
                return -best;
            }
        }
        free(s1->data);
        free(s1);
        free(s2->data);
        free(s2);
        free(s3->data);
        free(s3);
        free(s4->data);
        free(s4);
        return -best;
    }
    b[x][y] = sign * (1 - 2 * (depth % 2)) * player;
    int score = minimax(b, depth - 1, player, alpha, beta, nullptr, nullptr, w);
    b[x][y] = 0;
    if (Row != nullptr && Col != nullptr) {
        *Row = x + 1;
        *Col = y + 1;
    }
    return -score;
}

void ai_move(int **b, int depth, int player, int w, int *c, Stack *s) {
    Button num1 = {50 * s->data[s->count - 2].x + 50, 50 * s->data[s->count - 2].y + 50, 0, 0};
    char str1[4];
    sprintf(str1, "%d", *c - 1);
    print_button(num1, str1, LIGHTRED, ((WHITE + BLACK) + (WHITE - BLACK) * player) / 2, 30, "楷体");
    int x = 0, y = 0;
    minimax(b, depth, player, -MAX, MAX, &x, &y, w);
    (*c)++;
    Button num = {50 * x, 50 * y, 0, 0};
    setfillcolor(((BLACK + WHITE) + (BLACK - WHITE) * player) / 2);
    setlinecolor(((BLACK + WHITE) + (BLACK - WHITE) * player) / 2);
    fillcircle(50 * x, 50 * y, 20);
    char str[4];
    sprintf(str, "%d", *c);
    print_button(num, str, LIGHTRED, LIGHTRED, 30, "楷体");
    b[x - 1][y - 1] = player;
    Step step = {x - 1, y - 1};
    stack_push(s, &step);
}

void clear_chess(int x, int y, Stack *s, int player, int *c) {
    IMAGE board;
    loadimage(&board, "C:/vs code/Gobang/board.png", 800, 800);
    putimage(50 * x - 25, 50 * y - 25, 50, 50, &board, 50 * x - 25, 50 * y - 25);
    Button num1 = {50 * s->data[s->count - 1].x + 50, 50 * s->data[s->count - 1].y + 50, 0, 0};
    char str1[4];
    sprintf(str1, "%d", *c - 1);
    print_button(num1, str1, LIGHTRED, LIGHTRED, 30, "楷体");
}

void back_move(int **board, Stack *s, int *c, int player) {
    Step *step;
    step = stack_pop(s);
    int x = step->x;
    int y = step->y;
    board[x][y] = EMPTY;
    clear_chess(x + 1, y + 1, s, player, c);
    (*c)--;
}
