#include <stdio.h>
int is_prime(int input_num) {
    if(input_num==2) {
        return 1;
    } else {
        for (int i = 2; i < input_num; ++i) {
            if (input_num % i == 0) {
                return 0;
            }
        }
        return 1;
    }
}
int main() {
    printf("Enter a num:");
    int number;
    scanf("%d",&number);
    for (int i = 2; i < number/2;++i) {
        if(is_prime(i)) {
            int j = number - i;
            if (is_prime(j)) {
                printf("%d = %d + %d,Goldbach's conjecture is correct.",number,i,j);
                break;
            }
        }
    }
    return 0;
}
