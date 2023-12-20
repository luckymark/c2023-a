//验证两千以内哥德巴赫猜想正确性

#include<iostream>
#include <cmath>
using namespace std;

int N=2000;int prime[500]={2};int num = 1;int s;

bool judge (int n)
{
    if (n <= 1) return true;
    if (n == 2) {cout<<"2=1+1";return false;}
    else
    {
        float root = sqrt(float(n));
        for(int i=2;i<=root;i++)
        {
            if (n%i == 0) return false;
        }
    }
    return true;
}

void all_prime (int n)
{
    if(n==N) return;
    float sqrt_n = sqrt(float(n));
    for(int i=0;i<=num-1 && prime[i]<=sqrt_n;i++)
    {
        if (n % prime[i] == 0)
        {
            all_prime(n+1);
            return;
        }
    }
    prime[num] = n;
    num += 1;
    all_prime(n + 1);
}

void search (int arr[],int num_prime,int S)
{
    for(int i=num_prime-1;i>0;i--)
    {
        for(int j=i-1;j>=0;j--)
        {
            if(arr[i]+arr[j]==S) cout<<S<<"="<<arr[i]<<"+"<<arr[j]<<"\t";
        }
    }
}

int main(){
    cin>>s;
    all_prime(3);
    while(judge(s))
    {
        system("cls");
        cout<<"input a composite number (2~2000) :";
        cin>>s;
    }
    search(prime,num,s);
    return 0;
}