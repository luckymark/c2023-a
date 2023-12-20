//汉诺塔
#include<iostream>
using namespace std;

void move (char a,char b)
{
    cout<<a<<"-->"<<b<<endl;
}

void hanoi (int n,char a,char b,char c)
{
    if(n==1)
    {
        move(a,c);
        return;
    }
    else
    {
        hanoi (n-1,a,c,b);
        move(a,c);
        hanoi (n-1,b,a,c);
    }
}
int main(){
    hanoi (64,'A','B','C');
    return 0;
}