#include "stdio.h"
#define MAX_PLACE 3

void move(char, char, typeof (MAX_PLACE));
static typeof (MAX_PLACE) Hanoi[3] = {MAX_PLACE};

int main() {
    move(0, 1, MAX_PLACE);
    return 0;
}

void move(char from, char to, typeof (MAX_PLACE) num) {
    if (num<=1){
        printf("%c -> %c\n", from+'A', to+'A');
        Hanoi[from]--;Hanoi[to]++;
    }else {
        move(from, (char) (3 - from - to), num - 1);
        printf("%c -> %c\n", from + 'A', to + 'A');
        Hanoi[from]--;Hanoi[to]++;
        move((char) (3 - from - to), to, num - 1);
    }
}