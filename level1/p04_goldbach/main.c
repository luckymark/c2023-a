#include <stdio.h>
int primer(int);
int main()
{
    int n;
    printf("Please enter an even number between 4 and 100.\n");
    scanf("%d",&n);
    int i=2;
    while (i<=n-1)
    {
        if (primer(i) == 1 && primer(n - i) == 1)
        {
            printf("%d=%d+%d", n, i, n - i);
            break;
        }
        else i++;
    }
    return 0;
}
int primer(int n)
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
        n=0;
    else
        n=1;
    return n;
}