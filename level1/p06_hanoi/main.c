#include <stdio.h>
void move(int num,char a,char b,char c) {
    if (num == 1) {
        printf("%c -> %c\n",a,c);
    } else {
        move(num-1,a,c,b);
        move(1,a,b,c);
        move(num-1,b,a,c);
    }
}
int main() {
    int count;
    printf("Enter the number of the plates:");
    scanf("%d",&count);
    printf("\nThe steps are:\n");
    move(count,'A','B','C');
    return 0;
}