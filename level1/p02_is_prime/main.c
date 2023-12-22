#include <stdio.h>
#include <math.h>
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
{   setbuf(stdout,NULL);
    int num = 0;
    printf("Please input a number:");
    scanf("%d", &num);
    if (Exam(num))
        printf("The number is prime number\n");
    else
        printf("The number is not prime number\n");
    return 0;
}
