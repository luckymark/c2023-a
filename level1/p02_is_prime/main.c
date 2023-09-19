#include <stdio.h>
int main()
{
    int n;
    int i=2;
    scanf("%d",&n);
    while(i<=n-1)
    {
        if (n % i == 0)
        {
            printf("%d is not a prime number", n);
            return 0;
        }
        i++;
    }
        printf("%d is a prime number",n);
    return 0;
}
