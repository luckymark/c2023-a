#include <iostream>
using namespace std;
string str = "A -> C  ";
string shift1(string str)
{
    for(int i = 0;i<str.length();i++)
    {
        if(str[i]=='B')
        {
            str[i] = 'C';
            continue;
        }
        if(str[i]=='C')
            str[i]='B';
    }
    return str;
}
string shift2(string str)
{
    for(int i = 0;i<str.length();i++)
    {
        if(str[i]=='A')
        {
            str[i] = 'B';
            continue;
        }
        if(str[i]=='B')
            str[i]='A';
    }
    return str;
}
string Hanoi(int n)
{   if(n==1)
        return str;
    if(n>1)
        return
                shift1(Hanoi(n-1))+
                str+
                shift2(Hanoi(n-1));
}
int main()
{
    int x = 0;
    cout<<"Please input the number of plate:";
    cin>>x;
    cout<<endl<<Hanoi(x);
    return 0;
}

