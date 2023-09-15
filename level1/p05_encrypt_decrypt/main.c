#include <stdio.h>

enum {OFFSET=1};

void encode();

void decode();

int main() {
    encode();
    decode();
}

void decode() {
    char input[100];
    gets(input);
    for (int i = 0; i < 100 && input[i]!=0; ++i) {
        putchar(input[i] - OFFSET);
    }
    putchar('\n');

}

void encode() {
    char input[100];
    gets(input);
    for (int i = 0; i < 100 && input[i]!=0; ++i) {
        putchar(input[i] + OFFSET);
    }
    putchar('\n');
}
