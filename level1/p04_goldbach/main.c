#include <stdio.h>
#include <math.h>
#define num 100
int Exam(int n)
{   int i = 0;
    for(i = 2;i<=floor(sqrt(n));i++)
    {
        if(n%i==0)
            break;
    }
    if(i==floor(sqrt(n)+1))
        return 1;
    else
        return 0;
}
int main()
{   int count = 0;
    for(int i = 2,j = 0;i<num + 1;i++)
    {if(Exam(i))
            count++;
    }
    int arr[count];
    for(int i = 2,j = 0;i<num + 1;i++)
    {   if(Exam(i))
        {
            arr[j]=i;
            j++;
        }
    }
    int test = 0;
    for(int i = 4;i<num + 1;i+=2)
    {
        for (int m = 0,n = 0; m < count; m++)
        {
            for (n = 0; n < count; n++)
            {
                if (arr[m] + arr[n] == i)
                {
                    printf("%d=%d+%d\n", i, arr[m], arr[n]);
                    test++;
                    break;
                }
            }
            if(arr[m]+arr[n]==i)
                break;
        }
    }
    if(test==(num - 2)/2)
        printf("Goldbach conjecture is right within 100");
    else
        printf("Goldbach conjecture is not right within 100");
    return 0;}

