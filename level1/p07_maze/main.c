#include<stdio.h>
#include<stdlib.h>
#define Row 10
#define Col 10
#include <windows.h>
#include <conio.h>
enum SpiriteType{
    Space,Wall,export,Human
};
void draw(int **map,int m,int n){
    for(int i=0;i<m;i++){
        printf("\n");
        for(int j=0;j<n;j++){
            switch (map[i][j]) {
                case Space:
                    printf(" ");
                    break;
                case Wall:printf("#");
                    break;
                case export:printf("&");
                    break;
                case Human:printf("@");
                break;
                default:
                    break;
            }
        }
    }
    printf("\n");
}
void run(int **map,int m,int n,int x,int y) {
    char c;
    c = getch();
    switch (c) {
        case 'd':
            if (map[x][y + 1] == Space || map[x][y + 1] == export) {
                map[x][y + 1] = Human;
                map[x][y] = Space;
            } else {
                printf("It is a wall");
            }
            break;
        case 'a':
            if (map[x][y - 1] == Space || map[x][y - 1] == export) {
                map[x][y - 1] = Human;
                map[x][y] = Space;
            } else {
                printf("It is a wall");
            }
            break;
        case 's':
            if (map[x + 1][y] == Space || map[x + 1][y] == export) {
                map[x + 1][y] = Human;
                map[x][y] = Space;
            } else {
                printf("It is a wall");
            }
            break;
        case 'w':
            if (map[x - 1][y] == Space || map[x - 1][y] == export) {
                map[x - 1][y] = Human;
                map[x][y] = Space;
            } else {
                printf("It is a wall");
            }
            break;
        default:
            break;
    }
}
 struct Zuobiao{
    int x;
    int y;
};
struct Zuobiao Findperson(int **map,int m,int n,int target){
    struct Zuobiao zuobiao;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(map[i][j]==target){
                zuobiao.x = i;
                zuobiao.y = j;
            }
        }
    }
    return zuobiao;
}
int main()
{
    int map[Row][Col]={{1,1,1,1,1,1,1,1,1,1},
                       {1,3,0,0,1,1,1,0,0,1},
                       {1,0,1,0,0,0,1,0,0,1},
                       {1,0,1,1,0,0,1,1,0,1},
                       {1,0,0,1,0,0,0,0,1,1},
                       {1,0,0,1,1,1,1,0,1,1},
                       {1,0,0,0,1,0,1,0,0,1},
                       {1,1,1,1,1,0,1,1,0,1},
                       {1,1,0,0,0,0,1,0,0,2},
                       {1,1,1,1,1,1,1,1,1,1}};
    int *p[Col]={map[0],map[1],map[2],map[3],map[4],map[5],map[6],map[7],map[8],map[9]};
    int *q[Col]={map[0],map[1],map[2],map[3],map[4],map[5],map[6],map[7],map[8],map[9]};
    int *o[Col]={map[0],map[1],map[2],map[3],map[4],map[5],map[6],map[7],map[8],map[9]};
    struct Zuobiao zuobiao;
    for(int i=0;i>=0;i++){
       if(zuobiao.x=Row&&zuobiao.y==Col-1){
           printf("You win!");
           Sleep(750);
           break;
       }
       draw(p,Row,Col);
     zuobiao=Findperson(o,Row,Col,3);
       run(q, Row, Col, zuobiao.x, zuobiao.y);
       Sleep(50);
       system("cls");
   }
    return 0;
}
