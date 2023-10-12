#include <stdio.h>
int yd(char x,char y,char z,int len){
    len--;
    if(len==1)
    {
        printf("%c->%c\n",x,y);
    }
    else
    {
        yd(x,z,y,len);
        printf("%c->%c\n",x,y);
        yd(z,y,x,len);
    }
    len++;
}
int main(){
    int n;
    scanf("%d",&n);
    char x='A',y='B',z='C';
    yd(x,z,y,n+1);
    return 0;
}