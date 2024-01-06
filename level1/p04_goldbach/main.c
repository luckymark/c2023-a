#include<stdio.h>
#include"isprime3.h"
int main()
{int j;
    int prime[1000]={2};
    int m=1;
    for(j=3;j<1000;j+=2)
    {
        if(isprime(j))
        {
            prime[m++]=j;
        }
    }
    int x;
    printf("请任意输入一个偶数：");
    scanf("%d",&x);
    if(x>2&&x<=1000){
        if(x%2==0)
        {
            int i;
            for(i=0;prime[i]!=0;i++) {
                int k = x - prime[i];
                int l;
                if (k <= prime[i]) {
                    for (l = 2; l < k; l++) {

                    }
                    if (k == l) {
                        printf("%d=%d+%d\n", x, prime[i], k);
                    }
                }
            }
        }else{
            printf("这不是一个偶数！");
        }


    }else if(x>1000)
    {
        printf("你的数据太大了!");
    }else{
        printf("你的数据太小了");
    }

    return 0;
}
