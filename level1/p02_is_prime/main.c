#include <stdio.h>
#include <math.h>
int main()
{
    int num;
    scanf("%d", &num);
    for(int i = 2; i <= sqrt(num); i++)
    {
        if(num % i == 0)
        {
            printf("1非素数");
            return 0;
        }
    }
    printf("2素数");
    return 0;
}
