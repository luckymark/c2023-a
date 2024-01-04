#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int map[8][8]={{1,1,1,1,1,1,1,1},
               {1,3,0,1,1,0,0,1},
               {1,0,2,0,0,0,0,1},
               {1,1,0,1,1,0,0,1},
               {1,1,0,1,1,0,1,1},
               {1,0,0,0,0,0,0,4},
               {1,0,0,1,1,1,1,1},
               {1,1,1,1,0,0,0,0}};
char block='#';
char space=' ';
char spot='$';
char box='@';
char person='!';
void printmap();
int a=1,b=1;
int A=2,B=2;
int main()
{
    while(A!=5||B!=7)
    {
        printmap();
        switch (getch())
        {
            case 'w':
                if (map[a-1][b]==0)
                {
                    map[a][b]=0;
                    map[a-1][b]=3;
                    a-=1;
                    break;
                }
                else if (map[a-1][b]==2 && map[a-2][b]==0)
                {
                    map[a][b]=0;
                    map[a-1][b]=3;
                    map[a-2][b]=2;
                    a-=1;
                    A-=1;
                    break;
                }
                else if (map[a-1][b]==2 && map[a-2][b]==4)
                {
                    a-=1;
                    A-=1;
                    break;
                }
                else break;
            case 's':
                if (map[a+1][b]==0)
                {
                    map[a][b]=0;
                    map[a+1][b]=3;
                    a+=1;
                    break;
                }
                else if (map[a+1][b]==2 && map[a+2][b]==0)
                {
                    map[a][b]=0;
                    map[a+1][b]=3;
                    map[a+2][b]=2;
                    a+=1;
                    A+=1;
                    break;
                }
                else if (map[a+1][b]==2 && map[a+2][b]==4)
                {
                    a+=1;
                    A+=1;
                    break;
                }
                else break;
            case 'a':
                if (map[a][b-1]==0)
                {
                    map[a][b]=0;
                    map[a][b-1]=3;
                    b-=1;
                    break;
                }
                else if (map[a][b-1]==2 && map[a][b-2]==0)
                {
                    map[a][b]=0;
                    map[a][b-1]=3;
                    map[a][b-2]=2;
                    b-=1;
                    B-=1;
                    break;
                }
                else if (map[a][b-1]==2 && map[a][b-2]==4)
                {
                    b-=1;
                    B-=1;
                    break;
                }
                else break;
            case 'd':
                if (map[a][b+1]==0)
                {
                    map[a][b]=0;
                    map[a][b+1]=3;
                    b+=1;
                    break;
                }
                else if (map[a][b+1]==2 && map[a][b+2]==0)
                {
                    map[a][b]=0;
                    map[a][b+1]=3;
                    map[a][b+2]=2;
                    b+=1;
                    B+=1;
                    break;
                }
                else if (map[a][b+1]==2 && map[a][b+2]==4)
                {
                    b+=1;
                    B+=1;
                    break;
                }
                else break;
        }
    }
    system("cls");
    printf("Done!");
    getchar();
    return 0;
}
void printmap()
{
    system("cls");
    for(int i=0;i<=7;i++)
    {
        for(int j=0;j<=7;j++)
        {
            switch (map[i][j])
            {
                case 0:
                    printf("%2c",space);
                    break;
                case 1:
                    printf("%2c",block);
                    break;
                case 2:
                    printf("%2c", box);
                    break;
                case 3:
                    printf("%2c",person);
                    break;
                case 4:
                    printf("%2c",spot);
                default:
                    break;
            }
        }
        printf("\n");
    }
}