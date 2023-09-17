#include "stdio.h"
#include "conio.h"
#include "stdlib.h"

#define SIZE_X 8
#define SIZE_Y 8
#define PLAYER 0
#define GATE 1
#define EXIT 2
#define PATH 3
#define WALL 4
int place_x = 2;
int place_y = 0;
char map[SIZE_X][SIZE_Y]={
        {4,4,4,4,4,4,4,4},
        {4,3,4,3,3,3,3,4},
        {0,3,4,4,3,4,3,4},
        {4,3,3,3,3,3,4,4},
        {4,4,3,4,4,4,3,2},
        {4,4,3,4,3,4,3,4},
        {4,3,3,3,3,3,3,4},
        {4,4,4,4,4,4,4,4}
};

void draw_map();
char move(int delta_x, int delta_y);

int main() {
    draw_map();
    int ch;
    while((ch=getch())!=0x1B) /* ESC to quit, up-72 down-80 left-75 right-77 */
    {
        if(ch==224){
            ch=getch();
            char tmp=0;
            if(ch==72)tmp=move(-1,0);
            else if(ch==80)tmp=move(1, 0);
            else if(ch==75)tmp=move(0,-1);
            else if(ch==77)tmp=move(0,1);
            if (tmp)draw_map();
            if (tmp==2) { printf("\nYou win!\n"); break; }
        }
    }
    system("pause");
}

void draw_map(){
    system("cls");
    for(int x=0;x<SIZE_X;x++){
        for(int y=0;y<SIZE_Y;y++){
            if(map[x][y]==PLAYER){printf("*");
                continue;}
            else if(map[x][y]==PATH||map[x][y]==GATE){ printf("\x20");
                continue;}
            else if(map[x][y]==EXIT){ printf("!");
                continue;}
            else{

                //打印边框
                if((x==0||x==SIZE_X-1)&&(y==0||y==SIZE_Y-1)) { printf("+");
                    continue; }
                else if(x==0||x==SIZE_X-1){printf("-");
                    continue;}
                else if(y==0||y==SIZE_Y-1){ printf("|");
                    continue;}

                char l_wall = (char)(map[x][y-1]==WALL);
                char r_wall = (char)(map[x][y+1]==WALL);
                char u_wall = (char)(map[x-1][y]==WALL);
                char d_wall = (char)(map[x+1][y]==WALL);
                if (l_wall&&r_wall&&!u_wall&&!d_wall){ printf("-");
                    continue;}
                else if(u_wall&&d_wall&&!l_wall&&!r_wall){ printf("|");
                    continue;}
                else { printf("+");
                    continue;}
            }
        }
        printf("\n");
    }
}

char move(int delta_x, int delta_y){
    int new_x = place_x+delta_x;
    int new_y = place_y+delta_y;
    if((new_x<0)||(new_y<0)||(new_x>=SIZE_X)||(new_y>=SIZE_Y)||map[new_x][new_y]==WALL)return(char)0;
    char win = (char)(map[new_x][new_y]==EXIT);
    map[place_x][place_y] = PATH;
    map[new_x][new_y] = PLAYER;
    place_x = new_x;
    place_y = new_y;
    return ++win;
}