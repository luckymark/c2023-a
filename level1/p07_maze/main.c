#include <stdbool.h>
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#define SIZE_X 29
#define SIZE_Y 115
#define PLAYER 0
#define ENTRY 1
#define EXIT 2
#define PATH 3
#define WALL 4
#define ARRIVED (-1)
#define IN_STACK (-2)
int place_x = 2;
int place_y = 0;
int** map;//[SIZE_X][SIZE_Y];

struct QNode{
    int x;
    int y;
    struct QNode *next;
    int value;
};

void draw_map();
char move(int delta_x, int delta_y);
void init_map(int x, int y);
bool create_map(char* type, int x, int y);
void create_map_DF(int x, int y);
void create_map_Prim(int x, int y);
int search_exit(int x, int y);

int main() {
    char input[100] = {0};
    printf("select method to create map(df, prim):");
    scanf("%s", input);
    while(!create_map(input, SIZE_X, SIZE_Y))scanf("%s", input);
    draw_map();
    int ch;
    while ((ch = getch()) != 0x1B) /* ESC to quit, up-72 down-80 left-75 right-77 */
    {
        if (ch == 224||ch==0) {
            ch = getch();
            char tmp = 0;
            if (ch == 72)tmp = move(-1, 0);
            else if (ch == 80)tmp = move(1, 0);
            else if (ch == 75)tmp = move(0, -1);
            else if (ch == 77)tmp = move(0, 1);
            if (tmp == 2) {
                printf("\x1b[%d;%dHYou win!\n", SIZE_X + 1, 0);
                break;
            }
        }
    }
    system("pause");
}

void init_map(int X, int Y) {
    map = (int**)malloc(X*Y*sizeof(int));
    for(int x=0; x<X; x++)map[x] = (int*)malloc(Y*sizeof(int));
    for (int x = 0; x < X; x++)
        for (int y = 0; y < Y; y++)
            map[x][y] = (int) (x % 2 && y % 2 ? PATH : WALL);
}

void draw_map() {
    system("cls");
    printf("\x1b[?25l");//隐藏光标
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            if (map[x][y] == PLAYER) {
                printf("\x1b[36m*\x1b[0m");//ANSI转义序列,下同
                continue;
            } else if (map[x][y] == PATH || map[x][y] == ENTRY) {
                printf("\x20");
                continue;
            } else if (map[x][y] == EXIT) {
                printf("\x1b[32m?\x1b[0m");
                continue;
            } else {

                //打印边框
                if ((x == 0 || x == SIZE_X - 1) && (y == 0 || y == SIZE_Y - 1)) {
                    printf("+");
                    continue;
                } else if (x == 0 || x == SIZE_X - 1) {
                    printf("-");
                    continue;
                } else if (y == 0 || y == SIZE_Y - 1) {
                    printf("|");
                    continue;
                }

                char l_wall = (char) (map[x][y - 1] == WALL);
                char r_wall = (char) (map[x][y + 1] == WALL);
                char u_wall = (char) (map[x - 1][y] == WALL);
                char d_wall = (char) (map[x + 1][y] == WALL);
                if (l_wall && r_wall && !u_wall && !d_wall) {
                    printf("-");
                    continue;
                } else if (u_wall && d_wall && !l_wall && !r_wall) {
                    printf("|");
                    continue;
                } else {
                    printf("+");
                    continue;
                }
            }
        }
        printf("\n");
    }
}

char move(int delta_x, int delta_y) {
    int new_x = place_x + delta_x;
    int new_y = place_y + delta_y;
    if ((new_x < 0) || (new_y < 0) || (new_x >= SIZE_X) || (new_y >= SIZE_Y) || map[new_x][new_y] == WALL)return '\x00';
    char win = (char) (map[new_x][new_y] == EXIT);
    map[place_x][place_y] = PATH;
    printf("\x1b[%d;%dH\x20", place_x + 1, place_y + 1);//ANSI控制字符,移动光标
    map[new_x][new_y] = PLAYER;
    printf("\x1b[%d;%dH\x1b[36m*\x1b[0m", new_x + 1, new_y + 1);//ANSI控制字符,移动光标
    place_x = new_x;
    place_y = new_y;
    return ++win;
}

void create_map_DF(int X, int Y) {
    srand((unsigned) time(NULL));
    init_map(X, Y);
    long *stack = malloc((X / 2) * (Y / 2) * sizeof(long));
    int *s_depth = malloc((X / 2) * (Y / 2) * sizeof(short));
    for (int i = 0; i < (X / 2) * (Y / 2); i++)stack[i] = -1L;
    int p = 1, start_x = 2 * (rand() % ((X - 1) / 2)) + 1, start_y = 1, px, py, pd;// NOLINT(cert-msc30-c, cert-msc50-cpp)
    map[start_x][start_y - 1] = PLAYER;
    place_x = start_x;place_y = start_y - 1;// 初始化位置信息
    stack[0] = start_x << 16 | start_y;
    s_depth[0] = 1;//初始化栈
    while (p-- > 0) {
        px = stack[p] >> 16;py = stack[p] % (1 << 16);pd = s_depth[p];
        map[px][py] = -pd;
        unsigned char arrow = rand() & 0b11;// NOLINT(cert-msc30-c, cert-msc50-cpp)
        signed char direction = rand() & 1 ? 1 : -1;// NOLINT(cert-msc30-c, cert-msc50-cpp)
        for (int cnt = 0; cnt < 4; cnt++) {
            int dx = (arrow%2-1)*(arrow-1), dy = (arrow%2)*(arrow-2);//(1, 0)(0, -1)(-1, 0)(0, 1)

            if (px*(arrow==2)!=1&&px*(arrow==0)!=X-2&&py*(arrow==1)!=1&&py*(arrow==3)!=Y-2&&map[px + 2*dx][py + 2*dy]>=0){
                stack[p] = (px + 2*dx) << 16 | (py + 2*dy);
                s_depth[p++] = (pd + 1);
                map[px+2*dx][py+2*dy] = (int) (-pd-1);
                map[px+dx][py+dy] = PATH;
            }
            arrow = (arrow + direction) & 0b11;
            if ((rand() & 0b111) == 0)break;// NOLINT(cert-msc30-c, cert-msc50-cpp)
        }
    }
    free(stack);free(s_depth);//释放栈动态获取的内存
    int max_depth = -1, exit_x = -1;

    for (px = 1; px < X; px += 2)
        if (map[px][Y-2] <= max_depth) {
            max_depth = map[px][Y-2];
            exit_x = px;
        }

    map[exit_x][Y - 1] = EXIT;
    for (px = 1; px < X-1; px++)for (py = 1; py < Y-1; py++)if (map[px][py] < 0)map[px][py] = PATH;

}

void create_map_Prim(int X, int Y) {
    srand((unsigned) time(NULL));
    init_map(X, Y);
    long *stack = malloc((X / 2) * (Y / 2) * sizeof(long));
    int p = 1;
    int px = rand() % ((X - 1) / 2) * 2 + 1, py = 1;// NOLINT(cert-msc30-c, cert-msc50-cpp)

    stack[0] = (px << 16) | py;
    map[px][py - 1] = PLAYER;
    map[px][py] = ARRIVED;
    place_x = px;place_y = py-1;

    while (p > 0) {
        int place = rand() % p;// NOLINT(cert-msc30-c, cert-msc50-cpp)
        px = stack[place] >> 16;
        py = stack[place] % (1 << 16);
        for (int i = place; i < p; i++) {
            stack[i] = stack[i + 1];
        }
        p--;

        map[px][py] = ARRIVED;
        int arrow = rand() % 4;// NOLINT(cert-msc30-c, cert-msc50-cpp)
        int direction = (rand() & 1) ? 1 : -1;// NOLINT(cert-msc30-c, cert-msc50-cpp)
        char flag = 0;

        for (int i = 0; i < 4; i++) {
            switch (arrow) {
                case 0:if(px==1)break;else;
                    if (map[px - 2][py] == ARRIVED && !flag) {
                        map[px - 1][py] = PATH;
                        flag = 1;
                    } else if (map[px - 2][py] == PATH) {
                        stack[p++] = ((px - 2) << 16) | py;
                        map[px - 2][py] = IN_STACK;
                    }
                    break;

                case 2:if(px==X-2)break;else;
                    if (map[px + 2][py] == ARRIVED && !flag) {
                        map[px + 1][py] = PATH;
                        flag = 1;
                    } else if (map[px + 2][py] == PATH) {
                        stack[p++] = ((px + 2) << 16) | py;
                        map[px + 2][py] = IN_STACK;
                    }
                    break;

                case 1:if(py==1)break;else;
                    if (map[px][py - 2] == ARRIVED && !flag) {
                        map[px][py - 1] = PATH;
                        flag = 1;
                    } else if (map[px][py - 2] == PATH) {
                        stack[p++] = (px << 16) | (py - 2);
                        map[px][py - 2] = IN_STACK;
                    }
                    break;

                case 3:if(py==Y-2)break;else;
                    if (map[px][py + 2] == ARRIVED && !flag) {
                        map[px][py + 1] = PATH;
                        flag = 1;
                    } else if (map[px][py + 2] == PATH) {
                        stack[p++] = (px << 16) | (py + 2);
                        map[px][py + 2] = IN_STACK;
                    }
                    break;

                default:
                    printf("I can't analyze arrow %d.", arrow);
                    break;
            }
            arrow = (arrow + direction) & 0b11;
        }
    }
    for (px = 1; px < X; px+=2)for (py = 1; py < Y; py+=2)if (map[px][py] < 0)map[px][py] = PATH;

    px = search_exit(X, Y);
    map[px][Y - 1] = EXIT;

}

int search_exit(int X, int Y){
    struct QNode* head = malloc(sizeof(struct QNode));
    head->next = malloc(sizeof(struct QNode));
    for(int sx=0;sx<X;sx++)if(map[sx][0]==PLAYER)head->next->x = sx;
    head->next->y = 1;
    head->next->next = NULL;
    head->next->value = 0;
    struct QNode* tail = head->next;
    int px, py, depth;
    while (head->next!=NULL){
        head = head->next;
        px = head->x;py = head->y;
        depth = head->value;
        map[px][py] = ARRIVED;
        for(char i=0;i<4;i++){
            int dx = (i%2-1)*(i-1), dy = i%2*(i-2); //(1, 0)(0, -1)(-1, 0)(0, 1)
            if (map[px+dx][py+dy]==PATH){
                tail->next = malloc(sizeof(struct QNode));
                tail = tail->next;
                tail->x = px+dx;tail->y = py+dy;tail->value = depth+1;
            }else if(py==Y-2)map[px][py+1] = (int)-depth;
        }
    }

    int max_place_x = 1;
    int max_depth = map[max_place_x][Y-1];
    for(px=max_place_x+2;px<X;px+=2){
        if (map[px][Y-1]<=max_depth){
            max_depth = map[px][Y-1];
            map[max_place_x][Y-1] = WALL;
            map[px][Y-1] = EXIT;
            max_place_x = px;
        }else map[px][Y-1] = WALL;
    }
    for(px=0;px<X;px++)for(py=0;py<Y;py++)if(map[px][py]==ARRIVED)map[px][py]=PATH;
    return max_place_x;
}

bool create_map(char* type, int x, int y){
    if(strcmp("df", type) == 0)create_map_DF(x, y);
    else if(strcmp("prim", type) == 0)create_map_Prim(x, y);
    else return false;
    return true;
}