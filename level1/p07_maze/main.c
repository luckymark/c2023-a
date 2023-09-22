#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "time.h"

#define SIZE_X 21
#define SIZE_Y 35
#define PLAYER 0
#define GATE 1
#define EXIT 2
#define PATH 3
#define WALL 4
int place_x = 2;
int place_y = 0;
short map[SIZE_X][SIZE_Y];

void draw_map();
char move(int delta_x, int delta_y);
void init_map(int x, int y);
void create_map_DF(int x, int y);

int main() {
    create_map_DF(SIZE_X, SIZE_Y);
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
            if (tmp==2) { printf("\x1b[%d;%dHYou win!\n", SIZE_X+1, 0); break; }
        }
    }
    system("pause");
}

void init_map(int X, int Y){
//    for(int x=0;x<X;x++) { map[x] = (char *) malloc(Y * sizeof(char)); }
    for(int x=0;x<X;x++)for(int y=0;y<Y;y++){map[x][y] = (short)(x%2&&y%2?PATH:WALL);}
//    return MAP;
}

void draw_map(){
    system("cls");
    printf("\x1b[?25l");//隐藏光标
    for(int x=0;x<SIZE_X;x++){
        for(int y=0;y<SIZE_Y;y++){
            if(map[x][y]==PLAYER){printf("\x1b[36m*\x1b[0m");//ANSI转义序列,下同
                continue;}
            else if(map[x][y]==PATH||map[x][y]==GATE){ printf("\x20");
                continue;}
            else if(map[x][y]==EXIT){ printf("\x1b[32m?\x1b[0m");
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
    if((new_x<0)||(new_y<0)||(new_x>=SIZE_X)||(new_y>=SIZE_Y)||map[new_x][new_y]==WALL)return'\x00';
    char win = (char)(map[new_x][new_y]==EXIT);
    map[place_x][place_y] = PATH;printf("\x1b[%d;%dH\x20", place_x+1, place_y+1);//ANSI控制字符,移动光标
    map[new_x][new_y] = PLAYER;printf("\x1b[%d;%dH\x1b[36m*\x1b[0m", new_x+1, new_y+1);//ANSI控制字符,移动光标
    place_x = new_x;
    place_y = new_y;
    return ++win;
}

void create_map_DF(int X, int Y) {
    int exit_x = -1;
    do{
    srand((unsigned) time(NULL));
    init_map(X, Y);
    long *stack = malloc((X / 2) * (Y / 2) * sizeof(long));
    short *s_depth = malloc((X / 2) * (Y / 2) * sizeof(short));
    for (int i = 0; i < (X / 2) * (Y / 2); i++)stack[i] = -1L;
    int p = 1, start_x, start_y = 1;
    start_x = 2 * (rand() % ((X - 1) / 2)) + 1;// NOLINT(cert-msc30-c, cert-msc50-cpp)
    map[start_x][start_y - 1] = PLAYER;
    place_x = start_x;
    place_y = start_y - 1;// 初始化位置信息
    stack[0] = start_x << 16 | start_y;
    s_depth[0] = 1;//初始化栈
    int px, py;
    short pd;
    while (p > 0) {
        p--;
        px = stack[p] >> 16;
        py = stack[p] % (1 << 16);
        pd = s_depth[p];
        map[px][py] = (short) -pd;
        unsigned char arrow = rand() & 0b11;// NOLINT(cert-msc30-c, cert-msc50-cpp)
        signed char direction = rand() & 1 ? 1 : -1;// NOLINT(cert-msc30-c, cert-msc50-cpp)
        for (int cnt = 0; cnt < 4; cnt++) {
            switch (arrow) {
                case 0:
                    if (px != 1 && map[px - 2][py] >= 0) {
                        stack[p] = (px - 2) << 16 | py;
                        s_depth[p] = (short) (pd + 1);
                        p++;
                        map[px - 2][py] = (short) (-pd - 1);
                        map[px - 1][py] = PATH;
                    }
                    break;
                case 2:
                    if (px != X - 2 && map[px + 2][py] >= 0) {
                        stack[p] = (px + 2) << 16 | py;
                        s_depth[p] = (short) (pd + 1);
                        p++;
                        map[px + 2][py] = (short) (-pd - 1);
                        map[px + 1][py] = PATH;
                    }
                    break;
                case 1:
                    if (py != 1 && map[px][py - 2] >= 0) {
                        stack[p] = px << 16 | (py - 2);
                        s_depth[p] = (short) (pd + 1);
                        p++;
                        map[px][py - 2] = (short) (-pd - 1);
                        map[px][py - 1] = PATH;
                    }
                    break;
                case 3:
                    if (py != Y - 2 && map[px][py + 2] >= 0) {
                        stack[p] = px << 16 | (py + 2);
                        s_depth[p] = (short) (pd + 1);
                        p++;
                        map[px][py + 2] = (short) (-pd - 1);
                        map[px][py + 1] = PATH;
                    }
                    break;
                default: {
                    printf("HELP!!!I can't analyze %d", arrow);
                    break;
                }
            }
            arrow = (arrow + direction) & 0b11;
            if ((rand() & 0b1111) == 0)break;// NOLINT(cert-msc30-c, cert-msc50-cpp)
        }
    }
    free(stack);free(s_depth);//释放栈动态获取的内存
    short max_depth = -1;
    exit_x = -1;
    py = Y - 2;
    for (px = 1; px < X; px += 2)
        if (map[px][py] <= max_depth) {
            max_depth = map[px][py];
            exit_x = px;
        }
}
    while(exit_x==-1);
    map[exit_x][Y-1] = EXIT;
    for(int px=0;px<X;px++)for(int py=0;py<Y;py++)if(map[px][py]<0)map[px][py]=PATH;

}