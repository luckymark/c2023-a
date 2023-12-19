#include <stdlib.h>
#include <stdbool.h>
#include "Evaluate.h"
#include "Minimax_Search.h"
#include "Inspire_Search.h"
pos* Search_list_black(int map[][15])
{
    pos* list=(pos*) malloc(225*sizeof(pos));
    int n=0;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(Is_drop(i,j,map) && Is_linkfive_black(i,j,map))
            {
                list[n].x=i;
                list[n].y=j;
                n++;
            }
            else if(Is_drop(i,j,map) && Is_wakefour_black(i,j,map))
            {
                list[n].x=i;
                list[n].y=j;
                n++;
            }
            else if(Is_drop(i,j,map) && Is_wakethree_black(i,j,map))
            {
                list[n].x=i;
                list[n].y=j;
                n++;
            }
        }
    }
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(Is_drop(i,j,map) && !Is_linkfive_black(i,j,map) && !Is_wakefour_black(i,j,map) && !Is_wakethree_black(i,j,map))
            {
                list[n].x=i;
                list[n].y=j;
                n++;
            }
        }
    }
    for(int k=n;k<225;k++)
    {
        list[k].x=0;
        list[k].y=0;
    }
    return list;
}
pos* Search_list_white(int map[][15])
{
    pos* list=(pos*) malloc(225*sizeof(pos));
    int n=0;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(Is_drop(i,j,map) && Is_linkfive_white(i,j,map))
            {
                list[n].x=i;
                list[n].y=j;
                n++;
            }
            else if(Is_drop(i,j,map) && Is_wakefour_white(i,j,map))
            {
                list[n].x=i;
                list[n].y=j;
                n++;
            }
            else if(Is_drop(i,j,map) && Is_wakethree_white(i,j,map))
            {
                list[n].x=i;
                list[n].y=j;
                n++;
            }
        }
    }
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(Is_drop(i,j,map) && !Is_linkfive_white(i,j,map) && !Is_wakefour_white(i,j,map) && !Is_wakethree_white(i,j,map))
            {
                list[n].x=i;
                list[n].y=j;
                n++;
            }
        }
    }
    for(int k=n;k<225;k++)
    {
        list[k].x=0;
        list[k].y=0;
    }
    return list;
}
//搜索成五落点
bool Is_linkfive_black(int i,int j,int map[][15])
{
    int *vector = malloc(5*sizeof(int));
    map[i][j]=1;
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector[t]=map[i+t-k][j];
        }
        if(vector[0]==1 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector[t]=map[i][j+t-k];
        }
        if(vector[0]==1 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector[t]=map[i+t-k][j+t-k];
        }
        if(vector[0]==1 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector[t]=map[i+t-k][j-t+k];
        }
        if(vector[0]==1 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1)
        {
            map[i][j]=0;
            return true;
        }
    }
    map[i][j]=0;
    free(vector);
    return false;
}
bool Is_linkfive_white(int i,int j,int map[][15])
{
    int *vector = malloc(5*sizeof(int));
    map[i][j]=-1;
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector[t]=map[i+t-k][j];
        }
        if(vector[0]==-1 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector[t]=map[i][j+t-k];
        }
        if(vector[0]==-1 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector[t]=map[i+t-k][j+t-k];
        }
        if(vector[0]==-1 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector[t]=map[i+t-k][j-t+k];
        }
        if(vector[0]==-1 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1)
        {
            map[i][j]=0;
            return true;
        }
    }
    map[i][j]=0;
    free(vector);
    return false;
}
//搜索活四落点
bool Is_wakefour_black(int i,int j,int map[][15])
{
    int *vector = malloc(6*sizeof(int));
    map[i][j]=1;
    for(int k=0;k<6;k++)
    {
        for(int t=0;t<6;t++)
        {
            vector[t]=map[i+t-k][j];
        }
        if(vector[0]==0 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1 && vector[5]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<6;k++)
    {
        for(int t=0;t<6;t++)
        {
            vector[t]=map[i][j+t-k];
        }
        if(vector[0]==0 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1 && vector[5]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<6;k++)
    {
        for(int t=0;t<6;t++)
        {
            vector[t]=map[i+t-k][j+t-k];
        }
        if(vector[0]==0 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1 && vector[5]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<6;k++)
    {
        for(int t=0;t<6;t++)
        {
            vector[t]=map[i+t-k][j-t+k];
        }
        if(vector[0]==0 && vector[1]==1 && vector[2]==1 && vector[3]==1 && vector[4]==1 && vector[5]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    map[i][j]=0;
    free(vector);
    return false;
}
bool Is_wakefour_white(int i,int j,int map[][15])
{
    int *vector = malloc(6*sizeof(int));
    map[i][j]=-1;
    for(int k=0;k<6;k++)
    {
        for(int t=0;t<6;t++)
        {
            vector[t]=map[i+t-k][j];
        }
        if(vector[0]==0 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1 && vector[5]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<6;k++)
    {
        for(int t=0;t<6;t++)
        {
            vector[t]=map[i][j+t-k];
        }
        if(vector[0]==0 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1 && vector[5]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<6;k++)
    {
        for(int t=0;t<6;t++)
        {
            vector[t]=map[i+t-k][j+t-k];
        }
        if(vector[0]==0 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1 && vector[5]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<6;k++)
    {
        for(int t=0;t<6;t++)
        {
            vector[t]=map[i+t-k][j-t+k];
        }
        if(vector[0]==0 && vector[1]==-1 && vector[2]==-1 && vector[3]==-1 && vector[4]==-1 && vector[5]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    map[i][j]=0;
    free(vector);
    return false;
}
//搜索双三落点
bool Is_doublethree_black(int i,int j,int map[][15])
{

}
//搜索活三落点
bool Is_wakethree_black(int i,int j,int map[][15])
{
    int *vector1 = malloc(4*sizeof(int));
    int *vector2 = malloc(5*sizeof(int));
    map[i][j]=1;
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            vector1[t]=map[i+t-k][j];
        }
        if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1)
           ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1))
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            vector1[t]=map[i][j+t-k];
        }
        if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1)
           ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1))
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            vector1[t]=map[i+t-k][j+t-k];
        }
        if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1)
           ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1))
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            vector1[t]=map[i+t-k][j-t+k];
        }
        if((vector1[0]==1 && vector1[1]==1 && vector1[2]==0 && vector1[3]==1)
           ||(vector1[0]==1 && vector1[1]==0 && vector1[2]==1 && vector1[3]==1))
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector2[t]=map[i+t-k][j];
        }
        if(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector2[t]=map[i][j+t-k];
        }
        if(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector2[t]=map[i+t-k][j+t-k];
        }
        if(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector2[t]=map[i+t-k][j-t+k];
        }
        if(vector2[0]==0 && vector2[1]==1 && vector2[2]==1 && vector2[3]==1 && vector2[4]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    map[i][j]=0;
    free(vector1);
    free(vector2);
    return false;
}
bool Is_wakethree_white(int i,int j,int map[][15])
{
    int *vector1 = malloc(4*sizeof(int));
    int *vector2 = malloc(5*sizeof(int));
    map[i][j]=-1;
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            vector1[t]=map[i+t-k][j];
        }
        if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1)
           ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1))
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            vector1[t]=map[i][j+t-k];
        }
        if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1)
           ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1))
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            vector1[t]=map[i+t-k][j+t-k];
        }
        if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1)
           ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1))
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            vector1[t]=map[i+t-k][j-t+k];
        }
        if((vector1[0]==-1 && vector1[1]==-1 && vector1[2]==0 && vector1[3]==-1)
           ||(vector1[0]==-1 && vector1[1]==0 && vector1[2]==-1 && vector1[3]==-1))
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector2[t]=map[i+t-k][j];
        }
        if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector2[t]=map[i][j+t-k];
        }
        if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector2[t]=map[i+t-k][j+t-k];
        }
        if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    for(int k=0;k<5;k++)
    {
        for(int t=0;t<5;t++)
        {
            vector2[t]=map[i+t-k][j-t+k];
        }
        if(vector2[0]==0 && vector2[1]==-1 && vector2[2]==-1 && vector2[3]==-1 && vector2[4]==0)
        {
            map[i][j]=0;
            return true;
        }
    }
    map[i][j]=0;
    free(vector1);
    free(vector2);
    return false;
}