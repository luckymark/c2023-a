#include <stdlib.h>
#include <stdbool.h>
#include "Evaluate.h"
#include "Minimax_Search.h"
#include "Inspire_Search.h"
int Count_linkfive(int i,int j,int map[][15])
{
    int *vector = malloc(5*sizeof(int));
    int count=0;
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector[t]=map[i+t-k][j];
            }
            if(vector[0]==1 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1)
            {
                count--;
            }
            else if(vector[0]==-1 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector[t]=map[i][j+t-k];
            }
            if(vector[0]==1 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1)
            {
                count--;
            }
            else if(vector[0]==-1 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector[t]=map[i+t-k][j+t-k];
            }
            if(vector[0]==1 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1)
            {
                count--;
            }
            else if(vector[0]==-1 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<5;t++)
            {
                vector[t]=map[i+t-k][j-t+k];
            }
            if(vector[0]==1 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1)
            {
                count--;
            }
            else if(vector[0]==-1 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1)
            {
                count++;
            }
        }
    }
    free(vector);
    return count;
}
int Count_wakefour(int i,int j,int map[][15])
{
    int *vector = malloc(6*sizeof(int));
    int count=0;
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+9>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector[t]=map[i+t-k][j];
            }
            if(vector[0]==0 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1 && vector[5]==0)
            {
                count--;
            }
            else if(vector[0]==0 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1 && vector[5]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-j<=0 && k-j+9>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector[t]=map[i][j+t-k];
            }
            if(vector[0]==0 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1 && vector[5]==0)
            {
                count--;
            }
            else if(vector[0]==0 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1 && vector[5]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+9>=0 && k-j<=0 && k-j+9>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector[t]=map[i+t-k][j+t-k];
            }
            if(vector[0]==0 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1 && vector[5]==0)
            {
                count--;
            }
            else if(vector[0]==0 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1 && vector[5]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+9>=0 && k+j-5>=0 && k+j-14<=0)
        {
            for(int t=0;t<6;t++)
            {
                vector[t]=map[i+t-k][j-t+k];
            }
            if(vector[0]==0 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1 && vector[5]==0)
            {
                count--;
            }
            else if(vector[0]==0 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1 && vector[5]==0)
            {
                count++;
            }
        }
    }
    free(vector);
    return count;
}
int Count_rushfour(int i,int j,int map[][15])
{
    int *vector1 = malloc(5*sizeof(int));
    int *vector2 = malloc(6*sizeof(int));
    int count=0;
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i+t-k][j];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==1 && vector1[3]==0 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1 && vector1[4]==1)
               ||(i-k==0 && vector1[0]==1 && vector1[1]==1 && vector1[2]==1 && vector1[3]==1 && vector1[4]==0)
               ||(i+4-k==14 && vector1[0]==0 && vector1[1]==1 && vector1[2]==1 && vector1[3]==1 && vector1[4]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==0 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1 && vector1[4]==-1)
                    ||(i-k==0 && vector1[0]==-1 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==0)
                    ||(i+4-k==14 && vector1[0]==0 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i][j+t-k];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==1 && vector1[3]==0 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1 && vector1[4]==1)
               ||(j-k==0 && vector1[0]==1 && vector1[1]==1 && vector1[2]==1 && vector1[3]==1 && vector1[4]==0)
               ||(j+4-k==14 && vector1[0]==0 && vector1[1]==1 && vector1[2]==1 && vector1[3]==1 && vector1[4]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==0 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1 && vector1[4]==-1)
                    ||(j-k==0 && vector1[0]==-1 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==0)
                    ||(j+4-k==14 && vector1[0]==0 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i+t-k][j+t-k];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==1 && vector1[3]==0 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1 && vector1[4]==1)
               ||((i-k==0 || j-k==0) && vector1[0]==1 && vector1[1]==1 && vector1[2]==1 && vector1[3]==1 && vector1[4]==0)
               ||((i+4-k==14 || j+4-k==14) && vector1[0]==0 && vector1[1]==1 && vector1[2]==1 && vector1[3]==1 && vector1[4]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==0 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1 && vector1[4]==-1)
                    ||((i-k==0 || j-k==0) && vector1[0]==-1 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==0)
                    ||((i+4-k==14 || j+4-k==14) && vector1[0]==0 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i+t-k][j-t+k];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==1 && vector1[3]==0 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1 && vector1[4]==1)
               ||((i-k==0 || j+4-k==14) && vector1[0]==1 && vector1[1]==1 && vector1[2]==1 && vector1[3]==1 && vector1[4]==0)
               ||((i+4-k==14 || j-k==0) && vector1[0]==0 && vector1[1]==1 && vector1[2]==1 && vector1[3]==1 && vector1[4]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==0 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1 && vector1[4]==-1)
                    ||((i-k==0 || j+4-k==14) && vector1[0]==-1 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==0)
                    ||((i+4-k==14 || j-k==0) && vector1[0]==0 && vector1[1]==-1 && vector1[2]==-1 && vector1[3]==-1 && vector1[4]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+9>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i+t-k][j];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-j<=0 && k-j+9>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i][j+t-k];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+9>=0 && k-j<=0 && k-j+9>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i+t-k][j+t-k];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+9>=0 && k+j-5>=0 && k+j-14<=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i+t-k][j-t+k];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    free(vector1);
    free(vector2);
    return count;
}
int Count_wakethree(int i,int j,int map[][15])
{
    int *vector1 = malloc(4*sizeof(int));
    int *vector2 = malloc(5*sizeof(int));
    int count=0;
    for(int k=0;k<4;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<4;t++)
            {
                vector1[t]=map[i+t-k][j];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<4;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<4;t++)
            {
                vector1[t]=map[i][j+t-k];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<4;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<4;t++)
            {
                vector1[t]=map[i+t-k][j+t-k];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<4;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<4;t++)
            {
                vector1[t]=map[i+t-k][j-t+k];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector2[t]=map[i+t-k][j];
            }
            if(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0)
            {
                count--;
            }
            else if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector2[t]=map[i][j+t-k];
            }
            if(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0)
            {
                count--;
            }
            else if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector2[t]=map[i+t-k][j+t-k];
            }
            if(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0)
            {
                count--;
            }
            else if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<5;t++)
            {
                vector2[t]=map[i+t-k][j-t+k];
            }
            if(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0)
            {
                count--;
            }
            else if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0)
            {
                count++;
            }
        }
    }
    free(vector1);
    free(vector2);
    return count;
}
int Count_sleepthree(int i,int j,int map[][15])
{
    int *vector1 = malloc(5*sizeof(int));
    int *vector2 = malloc(6*sizeof(int));
    int *vector3 = malloc(7*sizeof(int));
    int count=0;
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i+t-k][j];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==0 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==1 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==0 && vector1[4]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==0 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==-1 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==0 && vector1[4]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i][j+t-k];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==0 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==1 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==0 && vector1[4]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==0 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==-1 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==0 && vector1[4]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i+t-k][j+t-k];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==0 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==1 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==0 && vector1[4]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==0 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==-1 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==0 && vector1[4]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i+t-k][j-t+k];
            }
            if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==0 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==1 && vector1[4]==1)
               ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==0 && vector1[4]==1))
            {
                count--;
            }
            else if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==0 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==-1 && vector1[4]==-1)
                    ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==0 && vector1[4]==-1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i+t-k][j];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i][j+t-k];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i+t-k][j+t-k];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i+t-k][j-t+k];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==1 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<7;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<7;t++)
            {
                vector3[t]=map[i+t-k][j];
            }
            if(vector3[0]==-1 && vector3[1]==0 && vector3[2]==1 && vector3[3]==1 && vector3[4]==1 && vector3[5]==0 && vector3[6]==-1)
            {
                count--;
            }
            else if(vector3[0]==1 && vector3[1]==0 && vector3[2]==-1 && vector3[3]==-1 && vector3[4]==-1 && vector3[5]==0 && vector3[6]==1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<7;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<7;t++)
            {
                vector3[t]=map[i][j+t-k];
            }
            if(vector3[0]==-1 && vector3[1]==0 && vector3[2]==1 && vector3[3]==1 && vector3[4]==1 && vector3[5]==0 && vector3[6]==-1)
            {
                count--;
            }
            else if(vector3[0]==1 && vector3[1]==0 && vector3[2]==-1 && vector3[3]==-1 && vector3[4]==-1 && vector3[5]==0 && vector3[6]==1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<7;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<7;t++)
            {
                vector3[t]=map[i+t-k][j+t-k];
            }
            if(vector3[0]==-1 && vector3[1]==0 && vector3[2]==1 && vector3[3]==1 && vector3[4]==1 && vector3[5]==0 && vector3[6]==-1)
            {
                count--;
            }
            else if(vector3[0]==1 && vector3[1]==0 && vector3[2]==-1 && vector3[3]==-1 && vector3[4]==-1 && vector3[5]==0 && vector3[6]==1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<7;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<7;t++)
            {
                vector3[t]=map[i+t-k][j-t+k];
            }
            if(vector3[0]==-1 && vector3[1]==0 && vector3[2]==1 && vector3[3]==1 && vector3[4]==1 && vector3[5]==0 && vector3[6]==-1)
            {
                count--;
            }
            else if(vector3[0]==1 && vector3[1]==0 && vector3[2]==-1 && vector3[3]==-1 && vector3[4]==-1 && vector3[5]==0 && vector3[6]==1)
            {
                count++;
            }
        }
    }
    free(vector1);
    free(vector2);
    free(vector3);
    return count;
}
int Count_waketwo(int i,int j,int map[][15])
{
    int *vector1 = malloc(4*sizeof(int));
    int *vector2 = malloc(5*sizeof(int));
    int *vector3 = malloc(6*sizeof(int));
    int count=0;
    for(int k=0;k<4;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<4;t++)
            {
                vector1[t]=map[i+t-k][j];
            }
            if(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==1)
            {
                count--;
            }
            else if(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<4;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<4;t++)
            {
                vector1[t]=map[i][j+t-k];
            }
            if(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==1)
            {
                count--;
            }
            else if(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<4;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<4;t++)
            {
                vector1[t]=map[i+t-k][j+t-k];
            }
            if(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==1)
            {
                count--;
            }
            else if(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<4;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<4;t++)
            {
                vector1[t]=map[i+t-k][j-t+k];
            }
            if(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==1)
            {
                count--;
            }
            else if(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector2[t]=map[i+t-k][j];
            }
            if(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==0)
            {
                count--;
            }
            else if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector2[t]=map[i][j+t-k];
            }
            if(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==0)
            {
                count--;
            }
            else if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector2[t]=map[i+t-k][j+t-k];
            }
            if(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==0)
            {
                count--;
            }
            else if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<5;t++)
            {
                vector2[t]=map[i+t-k][j-t+k];
            }
            if(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==0)
            {
                count--;
            }
            else if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector3[t]=map[i+t-k][j];
            }
            if(vector3[0]==0 && vector3[1]==0 && vector3[2]==1 && vector3[3]==1 && vector3[4]==0 && vector3[5]==0)
            {
                count--;
            }
            else if(vector3[0]==0 && vector3[1]==0 && vector3[2]==-1 && vector3[3]==-1 && vector3[4]==0 && vector3[5]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector3[t]=map[i][j+t-k];
            }
            if(vector3[0]==0 && vector3[1]==0 && vector3[2]==1 && vector3[3]==1 && vector3[4]==0 && vector3[5]==0)
            {
                count--;
            }
            else if(vector3[0]==0 && vector3[1]==0 && vector3[2]==-1 && vector3[3]==-1 && vector3[4]==0 && vector3[5]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector3[t]=map[i+t-k][j+t-k];
            }
            if(vector3[0]==0 && vector3[1]==0 && vector3[2]==1 && vector3[3]==1 && vector3[4]==0 && vector3[5]==0)
            {
                count--;
            }
            else if(vector3[0]==0 && vector3[1]==0 && vector3[2]==-1 && vector3[3]==-1 && vector3[4]==0 && vector3[5]==0)
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<6;t++)
            {
                vector3[t]=map[i+t-k][j-t+k];
            }
            if(vector3[0]==0 && vector3[1]==0 && vector3[2]==1 && vector3[3]==1 && vector3[4]==0 && vector3[5]==0)
            {
                count--;
            }
            else if(vector3[0]==0 && vector3[1]==0 && vector3[2]==-1 && vector3[3]==-1 && vector3[4]==0 && vector3[5]==0)
            {
                count++;
            }
        }
    }
    free(vector1);
    free(vector2);
    free(vector3);
    return count;
}
int Count_sleeptwo(int i,int j,int map[][15])
{
    int *vector1 = malloc(5*sizeof(int));
    int *vector2 = malloc(6*sizeof(int));
    int count=0;
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i+t-k][j];
            }
            if(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==0 && vector1[4]==1)
            {
                count--;
            }
            else if(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==0 && vector1[4]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i][j+t-k];
            }
            if(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==0 && vector1[4]==1)
            {
                count--;
            }
            else if(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==0 && vector1[4]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i+t-k][j+t-k];
            }
            if(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==0 && vector1[4]==1)
            {
                count--;
            }
            else if(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==0 && vector1[4]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<5;t++)
            {
                vector1[t]=map[i+t-k][j-t+k];
            }
            if(vector1[0]==1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==0 && vector1[4]==1)
            {
                count--;
            }
            else if(vector1[0]==-1 && vector1[1]==0 && vector1[2]==0 && vector1[3]==0 && vector1[4]==-1)
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+10>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i+t-k][j];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i][j+t-k];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k-j<=0 && k-j+10>=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i+t-k][j+t-k];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    for(int k=0;k<6;k++)
    {
        if(k-i<=0 && k-i+10>=0 && k+j-4>=0 && k+j-14<=0)
        {
            for(int t=0;t<6;t++)
            {
                vector2[t]=map[i+t-k][j-t+k];
            }
            if((vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==1 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==0 && vector2[3]==1 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==1 && vector2[3]==0 && vector2[4]==1 && vector2[5]==-1)
               ||(vector2[0]==-1 && vector2[1]==1 && vector2[2]==1 && vector2[3]==0 && vector2[4]==0 && vector2[5]==0)
               ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==0 && vector2[3]==1 && vector2[4]==1 && vector2[5]==-1))
            {
                count--;
            }
            else if((vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==-1 && vector2[5]==1)
                    ||(vector2[0]==1 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==0 && vector2[4]==0 && vector2[5]==0)
                    ||(vector2[0]==0 && vector2[1]==0 && vector2[2]==0 && vector2[3]==-1 && vector2[4]==-1 && vector2[5]==1))
            {
                count++;
            }
        }
    }
    free(vector1);
    free(vector2);
    return count;
}
//给某一点赋值
int GiveValue(int i,int j,int map[][15])
{
    int value;
    value=10000 * Count_linkfive(i,j,map)
            +1000 * Count_wakefour(i,j,map)
             +100 * Count_rushfour(i,j,map)
              +300 * Count_wakethree(i,j,map)
               +10 * Count_sleepthree(i,j,map)
                +5 * Count_waketwo(i,j,map)
                 +1 * Count_sleeptwo(i,j,map);
    return value;
}
//判断某一点是否需要赋值
bool Is_GiveValue(int x,int y,int map[][15])
{
    if((x<2 || x>12 || y<2 || y>12) || (map[x-2][y]==0 && map[x-1][y]==0 && map[x+1][y]==0 && map[x+2][y]==0
                                        && map[x][y-2]==0 && map[x][y-1]==0 && map[x][y+1]==0 && map[x][y+2]==0
                                        && map[x-2][y-2]==0 && map[x-1][y-1]==0 && map[x+1][y+1]==0 && map[x+2][y+2]==0
                                        && map[x-2][y+2]==0 && map[x-1][y+1]==0 && map[x+1][y-1]==0 && map[x+2][y-2]==0)
       )
    {
        return false;
    }
    else
    {
        return true;
    }
}
//评估当前局面总分数值
int Evaluate(int map[][15])
{
    int score=0;
    for(int i=2;i<13;i++)
    {
        for(int j=2;j<13;j++)
        {
            if(Is_GiveValue(i,j,map))
            {
                score+=GiveValue(i,j,map);
            }
        }
    }
    return score;
}
