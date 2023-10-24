#include <stdio.h>
#include <stdbool.h>

bool isPrime(int input);

int main() {
    int input;
    scanf_s("%d", &input);
    if (input == 1) {
        printf("It is one.");
        return 0;
    }
    if (isPrime(input)) {
        printf("It is prime!");
        return 0;
    }
    printf("It is not prime!");
    return 0;
}


