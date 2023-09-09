#include<stdio.h>
//#include<time.h>
#define MAX 110
int num[MAX];
int main()
{
    //int begin = clock();
    int nownum = 2;
    for(; nownum <= 100; nownum++)
    {
        if(num[nownum] == 0)
        {
            //printf("%d\n",nownum);
            int i = nownum;
            while(nownum * i <= 1000)
            {
                num[nownum * i] = 1;
                i++;
            }
        }
    }
    //int end = clock();
    //printf("%dms",end - begin);
    for(int i = 4; i <= 100; i+=2)
    {
        int istrue = 0;
        int b = 2;
        while(istrue == 0)
        {
            if(num[b] == 1)
            {
                b++;
                continue;
            }
            if(i - b >= 1 && num[i - b] == 0) 
            {
                istrue = 1;
                printf("%d = %d + %d\n",i,b,i-b);
            }
            b++;
        }
    }
    return 0;
}
