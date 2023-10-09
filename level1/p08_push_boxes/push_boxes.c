#include "push_boxes.h"
void Print_map(FILE* map,int level,Player* pi)
{
    if(level == 1)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level1", "r");
    }
    if(level == 2)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level2", "r");
    }
    if(level == 3)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level3", "r");
    }
    if(level == 4)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level4", "r");
    }
    if(level == 5)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level5", "r");
    }
    if(map==NULL)
    {
        printf("Fail to open the file");
    }
    int ch;
    int i=1,j=1;
    while(1)
    {
        ch=fgetc(map);
        if(ch=='&')
        {
            (*pi).y=i;
            (*pi).x=j;
        }
        if(ch!='\n')
            j++;
        else
        {
            i++;
            j=1;
        }
        printf(" ");
        if(ch==EOF)
            break;
        if(ch=='&')
            Color(4);
        else if(ch=='#')
            Color(9);
        else if(ch=='*')
            Color(2);
        else if(ch=='O')
            Color(6);
        putchar(ch);
    }
    fclose(map);
}
void Form_arr(FILE* map,int level,int arr1[20][20],int arr2[20][20])
{
    if(level == 1)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level1", "r");
    }
    if(level == 2)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level2", "r");
    }
    if(level == 3)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level3", "r");
    }
    if(level == 4)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level4", "r");
    }
    if(level == 5)
    {
        map = fopen("C:\\c2023-a\\level1\\p08_push_boxes\\map\\level5", "r");
    }
    if(map==NULL)
    {
        printf("Fail to open the file");
    }
    int ch,i=1,j=1;
    while(1)
    {
        ch=fgetc(map);
        if(ch==EOF)
            break;
        if(ch=='#')
        {
            arr1[i][j]=1;
            j++;
        }
        if(ch==' ')
        {
            arr1[i][j]=2;
            j++;
        }
        if(ch=='*')
        {
            arr1[i][j]=2;
            arr2[i][j]=3;
            j++;
        }
        if(ch=='O')
        {
            arr1[i][j]=4;
            j++;
        }
        if(ch=='&')
        {
            arr1[i][j]=2;
            j++;
        }
        if(ch=='@')
        {
            arr1[i][j]=4;
            arr2[i][j]=3;
            j++;
        }
        if(ch=='\n')
        {
            i++;
            j=1;
        }
    }
    fclose(map);
}
void Move(int arr1[20][20],int arr2[20][20], Player* pi,int* pc)
{
    int ch2 = _getch();
    int dx = 0, dy = 0;
    switch (ch2)
    {
        case UP:
            dy = -1;
            break;
        case DOWN:
            dy = 1;
            break;
        case LEFT:
            dx = -1;
            break;
        case RIGHT:
            dx = 1;
            break;
    }
    if((arr1[(*pi).y+dy][(*pi).x+dx]==2||
            arr1[(*pi).y+dy][(*pi).x+dx]==4)&&
            arr2[(*pi).y+dy][(*pi).x+dx]!=3)
    {
        gotoxy(2*(*pi).x-1,(*pi).y);
        printf("  ");
        (*pi).y=(*pi).y+dy;
        (*pi).x=(*pi).x+dx;
        (*pc)++;
        gotoxy(2*(*pi).x-1,(*pi).y);
        Color(4);
        printf("& ");
        if(arr1[(*pi).y-dy][(*pi).x-dx]==4)
        {
            gotoxy(2*(*pi).x-2*dx-1,(*pi).y-dy);
            Color(6);
            printf("O ");
        }
    }
    else if(arr2[(*pi).y+dy][(*pi).x+dx]==3&&
            (arr1[(*pi).y+2*dy][(*pi).x+2*dx]==2||
                    arr1[(*pi).y+2*dy][(*pi).x+2*dx]==4)&&
            arr2[(*pi).y+2*dy][(*pi).x+2*dx]!=3)
    {
        gotoxy(2*(*pi).x-1,(*pi).y);
        printf("  ");
        (*pi).y=(*pi).y+dy;
        (*pi).x=(*pi).x+dx;
        (*pc)++;
        gotoxy(2*(*pi).x-1,(*pi).y);
        Color(4);
        printf("& ");
        arr2[(*pi).y][(*pi).x]=0;
        gotoxy(2*(*pi).x+2*dx-1,(*pi).y+dy);
        if(arr1[(*pi).y+dy][(*pi).x+dx]==4)
        {
            Color(6);
            printf("@ ");
        }
        if(arr1[(*pi).y+dy][(*pi).x+dx]==2)
        {
            Color(2);
            printf("* ");
        }
        arr2[(*pi).y+dy][(*pi).x+dx]=3;
        if(arr1[(*pi).y-dy][(*pi).x-dx]==4)
        {
            gotoxy(2*(*pi).x-2*dx-1,(*pi).y-dy);
            Color(6);
            printf("O ");
        }
    }
}
int Is_win(int arr1[20][20],int arr2[20][20])
{
    int flag=1;
    for(int i=1;i<20;i++)
    {
        for(int j=1;j<20;j++)
        {
            if(arr1[i][j]==4)
            {
                if(arr2[i][j]!=3)
                {
                    flag=0;
                }
            }
        }
    }
    return flag;
}
void Color(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Game(int level)
{
    Color(7);
    gotoxy(40,0);
    printf("Welcome to 'push boxes' game!");
    gotoxy(40,1);
    printf("Please remember '&' is player,'#' is wall");
    gotoxy(40,2);
    printf("'*' is box,'O' is the designed point");
    gotoxy(40,3);
    printf("If the box is at the point,it will become'@'");
    FILE* map;
    int arr1[20][20]={0},arr2[20][20]={0};
    Player player;
    int count = 0;
    gotoxy(0,0);
    printf("Current level: %d",level);
    gotoxy(0,1);
    Print_map(map,level,&player);
    Form_arr(map,level,arr1,arr2);
    while (1)
    {
        if (_kbhit())
        {
            int ch1 = _getch();
            if (ch1 == 224)
            {
                Move(arr1,arr2, &player,&count);
                gotoxy(40,4);
                Color(7);
                printf("Your current number of steps is %d",count);
                if(Is_win(arr1,arr2))
                {
                    Color(7);
                    gotoxy(40,5);
                    printf("Congratulations!");
                    gotoxy(40,6);
                    printf("You pass the level %d",level);
                    gotoxy(40,7);
                    printf("Your final number of steps is %d",count);
                    break;
                }
            }
            else if(ch1==27)
                break;
        }
    }
}
