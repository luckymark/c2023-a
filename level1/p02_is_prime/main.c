#include <stdio.h>
void primer(int);
int main()
{
    int n;
    printf("Enter a number.\n");
    scanf("%d", &n);
    primer(n);
    return 0;
}
void primer(int n)
{
    int k;
    for (int i=2;i<=n-1;i++)
    {
        if (n%i==0)
        {
            k=i;
            break;
        }
        else k=i;
    }
    if (k<n-1)
        printf("It is not a prime number.\n");
    else
        printf("It is a prime number.\n");
}