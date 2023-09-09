#include<stdio.h>
#include<time.h>
#define MAX 1010
int num[MAX];
int main()
{
    int begin = clock();
    int nownum = 2;
    for(; nownum <= 1000; nownum++)
    {
        if(num[nownum] == 0)
        {
            printf("%d\n",nownum);
            int i = nownum;
            while(nownum * i <= 1000)
            {
                num[nownum * i] = 1;
                i++;
            }
        }
    }
    int end = clock();
    printf("%dms",end - begin);
    return 0;
}
