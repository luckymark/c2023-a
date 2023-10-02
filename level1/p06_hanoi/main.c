#include <stdio.h>
void hanoi(int n,char A,char B,char C);
int main()
{
    int n;
    char A,B,C;
 printf("请输入黄金圆盘的个数：");
 scanf("%d",&n);
    hanoi( n, 'A', 'B', 'C');
    return 0;
}
void hanoi(int n,char A,char B,char C)
{
    if(n==1)
    {
        printf("%c->%c\n",A,C);

    }else{
        hanoi(n-1,A,C,B);
        printf("%c->%c\n",A,C);
        hanoi(n-1,B,A, C);
    }
}