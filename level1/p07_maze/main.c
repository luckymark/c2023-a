#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int map[12][12]={{1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1},
               {1, 0, 0, 0, 0, 1, 0, 0, 1,1,0,2},
               {1, 0, 1, 1, 0, 0, 0, 1, 0,0,0,1},
               {1, 0, 0, 1, 1, 1, 0, 1, 0,1,1,1},
               {1, 1, 0, 0, 1, 0, 0, 1, 0,0,0,1},
               {1, 0, 0, 1, 0, 1, 0, 0, 0,1,0,1},
               {1, 0, 1, 1, 0, 1, 0, 1, 1,1,0,1},
               {1, 0, 0, 0, 0, 1, 1, 0, 0,0,1,1},
               {1, 1, 0, 1, 0, 0, 1, 0, 1,0,0,1},
               {1, 0, 0, 1, 1, 0, 0, 0, 1,1,0,1},
               {1, 0, 1, 0, 0, 0, 1, 0, 0,0,3,1},
               {1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1}};
char block='#';
char space=' ';
char door='$';
char person='!';
int a=10;
int b=10;
void printmap();
int main()
{
    while (a!=1||b!=11)
    {
        printmap();
        switch (getch())
        {
            case 'w':
                if (map[a-1][b]!=1)
                {
                    map[a][b]=0;
                    map[a-1][b]=3;
                    a-=1;
                    break;
                }
                break;
            case 's':
                if (map[a+1][b]!=1)
                {
                    map[a][b]=0;
                    map[a+1][b]=3;
                    a+=1;
                    break;
                }
                break;
            case 'a':
                if (map[a][b-1]!=1)
                {
                    map[a][b]=0;
                    map[a][b-1]=3;
                    b-=1;
                    break;
                }
                break;
            case 'd':
                if (map[a][b+1]!=1)
                {
                    map[a][b]=0;
                    map[a][b+1]=3;
                    b+=1;
                    break;
                }
                break;
            default:
                break;
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
    for(int i=0;i<=11;i++)
    {
        for(int j=0;j<=11;j++)
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
                    printf("%2c", door);
                    break;
                case 3:
                    printf("%2c",person);
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}