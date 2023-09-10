#include <stdio.h>

enum {
    FLOOR = 3
};

void mv(char now, char to, char by, int floor);

int main() {
    mv('A', 'B', 'C', FLOOR);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

void mv(char now, char to, char by, int floor) {
    if (floor == 1) {
        printf("%c -> %c\n", now, to);
        return;
    }
    mv(now, by, to, floor - 1);
    mv(now, to, by, 1);
    mv(by, to, now, floor - 1);
}

#pragma clang diagnostic pop
