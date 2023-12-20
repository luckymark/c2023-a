//编写“加密”、“解密”函数，输入为任意长度的字符串
#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<conio.h>
#include<string>
#include <iomanip>
using namespace std;

int random_1,random_2,random_3,key;//随机生成n => 随机质数组
vector<int> random_prime_list = {2};int random_prime_num = 1;//随机质数组初定义
bool judge;

void random_prime (int n) //赋值随机质数数组，为生成key做条件
{
    if(n==random_1) return;
    float sqrt_n = sqrt(float(n));
    for(int i=0;i<=random_prime_num-1 && random_prime_list[i]<=sqrt_n;i++)
    {
        if (n % random_prime_list[i] == 0)
        {
            random_prime(n+1);
            return;
        }
    }
    random_prime_list.push_back(n);
    random_prime_num += 1;
    random_prime(n + 1);
}

int key_generate() //生成key
{
    srand(time(0));
    random_1 = rand();
    random_prime(3);
    random_2 = rand() % (random_prime_num-1);
    random_3 = random_prime_list[random_2];
    random_3 %= 128;
    return random_3;
}

vector<int> encrypt_input()
{
    cout<<"the key is :"<<key<<endl;
    cout<<"please input the text you want to encrypt :";
    vector<int> arr;
    while(true)
    {
        int n = int(getche());
        if(n==13) break;
        arr.push_back(n);
    }
    return arr;
}

int encrypt(int n) //n为一个ASCII码，将其加密为另一个ASCII码（若为两位数则待转化）
{
    return n*key % 128;
}



void encrypt_output(vector<int> str_1)
{
    cout<<endl<<"the output is:";
    for(int element : str_1)
    {
        std::cout<<std::setw(3)<<setfill('0')<<encrypt(element);
    }
}

vector<int> decrypt_input() //输入一个数组 如：121081073
{
    cout<<"please input :";
    vector<int> arr;
    while(true)
    {
        char s = char(getche());
        int n = s-'0';
        if(s=='q') break;
        arr.push_back(n);
    }
    return arr;
}

vector<int> decrypt_transform (vector<int> arr) //转换成一个存ascii码的数组
{
    vector<int> list;
    int count = 1;
    int num = 0;
    for( int element : arr)
    {
        num += element * int(pow(10,3-count));
        if(count % 3 == 0)
        {
            list.push_back(num);
            num = 0;
            count = 0;
        }
        count++;
    }
    return list;
}

char decrypt(int n)//n为一个ASCII码，将其解密为一个字符等待输出
{
    int t = 0;
    while (n%key != 0)
    {
        t++;
        n = n +128*t;
    }
    return char(n / key);
}

void decrypt_output(vector<int> str_2)
{
    cout<<endl<<"the output is:";
    for(int element : decrypt_transform(str_2))
    {
        cout<<decrypt(element);
    }
}


int main(){

    cout<<"encrypt(1) or decrypt(0):";
    cin>>judge;

    if(judge)
    {
        key = key_generate();
        encrypt_output(encrypt_input());
    }
    else
    {
        cout<<"please input the key for decrypt :";
        cin>>key;
        decrypt_output(decrypt_input());
    }

    return 0;
}