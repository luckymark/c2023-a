#include <stdio.h>

int isPrime(int n);
int main() {
    //定义哥德巴赫猜想：在认为 1 也为素数的情况下，每个大于 2 的整数都可以写成 3 个素数之和。
    //在2-100内验证哥德巴赫猜想的正确性。
    int prime[26]={[0]=1};
    //为prime数组逐一赋值2-99内所有素数。
    int count = 1;
    for (int i = 2;i<100;i++){
        if(isPrime(i)){
            count ++;
            prime[count - 1] = i;
        }
    }

    int base[98]={0};//验证的范围数组，98个元素均初始化为0。
    //计算所有prime数组中任意3个素数和。有重复计算:D。
    for(int a = 0;a < 26;a++){
        for(int b = 0;b < 26;b++){
            for(int c = 0;c <26;c++){
                int result = prime[a]+prime[b]+prime[c];
                if(2<result && result <= 100){
                    base[result - 3] = result;//若任意3个素数和范围在验证范围内，则替换验证范围数组中的0为对应素数和。
                }
            }
        }
    }

    //判断验证是否成功。
    int judge = 1;
    for(int i=0; i<98; i++){
        if (base[i] == 0){
            printf("base[%d]=%d ",i,base[i]);
            judge = 0;
        }
    }

    //输出证明结果。
    if(judge){
        printf("Goldbach is true.");
    } else{
        printf("Goldbach is wrong.");
    }
    return 0;
}

//检验整数n是否为素数，若为素数则返回1，否则返回0。
int isPrime(int n){
    int isPrime = 1;
    for(int i=2;i<n;i++){
        int x = n%i;
        if(x == 0){
            isPrime = 0;
            break;
        }
    }
    return isPrime;
}