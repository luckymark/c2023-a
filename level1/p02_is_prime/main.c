#include <stdio.h>
int main() {
    int num;
    printf("Enter a num:");
    scanf("%d",&num);
    if (num <= 1) {
        printf("It's not a prime.");
    } else {
        if (num == 2) {
            printf("It's a prime!");
        } else {
            for(int i = 2;i < num;i++) {
                if (num%i == 0) {
                    printf("It's not a prime.");
                    return 0;
                }
            }
            printf("It's a prime!");
            return 0;
        }
    }
    return 0;
}