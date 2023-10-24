#include <stdio.h>
#include <stdlib.h>

int main() {
    char c1 = '$';
    char c2 = ' ';

    while (1) {
        for (int i = 0; i < 200; i++) {
            for (int a = 0; a < i; a++) {
                printf("%c", c2);
            }
            printf("%c", c1);
            system("cls");
        }

        for (int i = 199; i >= 0; i--) {
            for (int a = i; a >= 0; a--) {
                printf("%c", c2);
            }
            printf("%c", c1);
            system("cls");

        }
    }
    return 0;
}