//输出n以内的所有素数
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

int N;int prime[100]={2};int num = 1;

void judge (int n)
{
    if(n==N)
    {
        cout<<endl<<"number of prime:"<<num;
        return;
    }
    float sqrt_n = sqrt(float(n));
    for(int i=0;i<=num-1 && prime[i]<=sqrt_n;i++)
    {
        if (n % prime[i] == 0)
        {
            judge(n+1);
            return;
        }
    }
    cout<<n<<" ";
    prime[num] = n;
    num += 1;
    judge(n + 1);
}

int main(){
    cin>>N;
    cout<<"2"<<" ";
    auto start_time = std::chrono::high_resolution_clock::now();
    judge(3);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time);
    cout<<endl<<"time:"<<float(duration.count())/1000000<<"s";
    return 0;
}