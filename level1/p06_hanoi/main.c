#include <stdio.h>
int main()
{
    void hanoi(int n,char first,char second,char third);
    int i;
    printf("Input the number of disks\n");
    scanf("%d",&i);
    hanoi(i,'A','B','C');
    return 0;
}
void hanoi(int n,char first,char second,char third)
{
    void move(char x,char y);
    if (n==1)
        move(first,third);
    else
    {
        hanoi(n-1,first,third,second);
        move(first,third);
        hanoi(n-1,second,first,third);
    }
}
void move(char x,char y)
{
    printf("%c-->%c\n",x,y);
}