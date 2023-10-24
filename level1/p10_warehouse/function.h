#ifndef C2023_CHALLENGE_FUNCTION_H
#define C2023_CHALLENGE_FUNCTION_H
typedef struct {
    char category[32];
    char model[32];
    char quantity[32];
} Item;

void menu(int* choice);
void showlist();
void warehouse();
void ex_warehouse();
Item* creat_item();
#endif //C2023_CHALLENGE_FUNCTION_H
