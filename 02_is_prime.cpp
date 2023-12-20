//判断任意正整数是不是素数
#include<iostream>
#include<cmath>
using namespace std;

void judge (int n) {
    if (n <= 1) cout<<"not";
    if (n == 2) cout<<"yes";
    else
    {
        float root = sqrt(float(n));
        for(int i=2;i<=root;i++)
        {
            if (n%i == 0)
            {
                cout<<"no";
                return;
            }
        }
        cout<<"yes";
    }
}

int main(){
    int n;
    cin>>n;
    judge(n);
    return 0;
}