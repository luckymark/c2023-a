#include <stdio.h>
#include<windows.h>
int main() {
    setbuf(stdout,NULL);
    printf("A");
    int i,j;
    for(i=0;i<262;i++)
    {
        Sleep(50);
        printf("\b A");

    }
    for(j=0;j<262;j++)
    {
        Sleep(50);
        printf("\b\bA");
    }

    return 0;
}
