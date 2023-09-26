#include<stdio.h>
int main()
{int x;
    printf("请任意输入一个偶数：");
    scanf("%d",&x);
    if(x>2&&x<=100){
        if(x%2==0)
        {int i;
            int prime[24]={2,3,5,7,11,13,17,19,
                           23,29,31,37,41,43,47,
                           53,59,61,67,71,79,83,89,97};
            for(i=0;i<24;i++)
            {
                int k=x-prime[i];
                int l;
                for(l=2;l<k;l++)
                {
                    if(k%l==0)
                        break;
                }
                if(k==l)
                {
                    printf("%d=%d+%d\n",x,prime[i],k);
                }
            }
        }else{
            printf("这不是一个偶数！");
        }


    }else if(x>100)
    {
        printf("你的数据太大了!");
    }else{
        printf("你的数据太小了");
    }

    return 0;
}
