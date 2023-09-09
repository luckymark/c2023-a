#include<stdio.h>
void move(int id,  char a, char b, char c)//编号，从a经过b移到c
{
    if(id == 0) return;
    move(id-1,a,c,b);//上面的块的移位
    //自己的移位
    printf("%c -> %c\n",a,c);
    move(id-1,b,a,c);//上面的块的移回
}
int main()
{//从上往下编号为1至64
    int num;
    printf("输入层数\n");
    scanf("%d",&num);
    move(num,'A','B','C');
    return 0;
}
