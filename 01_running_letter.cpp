//做一个滚动的字符
#include<iostream>
#include<unistd.h>
using namespace std;

void movement(char letter, float speed);

int main()
{
    movement('6',0.1);
    return 0;
}

void movement(char letter, float speed)
{
int length = 30;
int position = 0;
int direction = 1;

while (true)
{
if(direction==1 && position>=length) direction = -1;
if(direction==-1 && position<=0) direction = 1;

for(int i=1;i<=length;i++)
{
system("cls");
    for (int i = 0; i<=position; i++)
    {
    cout << " ";
    }
    cout<<letter;
    position += direction;
    usleep(speed * 1000000);
    }
    }
}



