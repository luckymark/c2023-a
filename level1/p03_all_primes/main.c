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
    for(int i = 0;i<1001;i++)
    {   
        if(Exam(i))
            printf("%3d ",i);
    }
    return 0;
}
