#include <stdio.h>
#include <windows.h>
#include <conio.h>
void draw(char **map, int m, int n){
    for(int i=0;i<m;i++){
        printf("\n");
        for(int j=0;j<n;j++){
            switch (map[i][j]) {
                case '0':
                    printf(" ");
                    break;
                case '1':printf("#");
                    break;
                case '3':printf("&");
                    break;
                case '2':printf("@");
                    break;
                case '4':printf("O");
                default:
                    break;
            }
        }
    }
    printf("\n");
}
//0空白1墙2人3箱子4洞
void run(char **map,int m,int n,int x,int y) {
    char c;
    c = getch();
    switch (c) {
        case 'd':
            if (map[x][y + 1] == '0' ) {
                map[x][y + 1] ='2' ;
                map[x][y] = '0';
            }else if(map[x][y+1]=='3'&&map[x][y+2]!='1'){
                map[x][y]='0';
                map[x][y+1]='2';
                        map[x][y+2]='3';
            }else if(map[x][y+1]=='3'&&map[x][y+2]=='4'){
                map[x][y]='0';
                map[x][y+1]='2';
                map[x][y+2]='4';
            }else if(map[x][y+1]=='4'){
                printf("it is a hole!");
            }
            else {
                printf("It is a wall");
            }
            break;
        case 'a':
            if (map[x][y - 1] == '0' ) {
                map[x][y - 1] ='2' ;
                map[x][y] = '0';
            }else if(map[x][y-1]=='3'&&map[x][y-2]!='1'){
                map[x][y]='0';
                map[x][y-1]='2';
                map[x][y-2]='3';
            } else if(map[x][y-1]=='3'&&map[x][y-2]=='4'){
                map[x][y]='0';
                map[x][y-1]='2';
                map[x][y-2]='4';
            }else if(map[x][y-1]=='4'){
                printf("it is a hole!");
            }else {
                printf("It is a wall");
            }
            break;
        case 's':
            if (map[x+1][y] == '0' ) {
                map[x+1][y] ='2' ;
                map[x][y] = '0';
            }else if(map[x+1][y]=='3'&&map[x+2][y]!='1'){
                map[x][y]='0';
                map[x+1][y]='2';
                map[x+2][y]='3';
            }else if(map[x+1][y]=='3'&&map[x+2][y]=='4'){
                map[x][y]='0';
                map[x+1][y]='2';
                map[x+2][y]='4';
            }
            else if(map[x+1][y]=='4'){
                printf("it is a hole!");
            }else {
                printf("It is a wall");
            }
            break;
        case 'w':
            if (map[x-1][y ] == '0' ) {
                map[x-1][y ] ='2' ;
                map[x][y] = '0';
            }else if(map[x-1][y]=='3'&&map[x-2][y]!='1'){
                map[x][y]='0';
                map[x-1][y]='2';
                map[x-2][y]='3';
            } else if(map[x-1][y]=='3'&&map[x-2][y]=='4'){
                map[x][y]='0';
                map[x-1][y]='2';
                map[x-2][y]='4';
            }else if(map[x-1][y]=='4'){
                printf("it is a hole!");
            }else {
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
struct Zuobiao Findperson(char **map,int m,int n,char target){
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
int main() {
    printf("Choose your difficulty:1or2?\n");
       char w;
       w=getchar();
       if(w=='1'){
           FILE *file = fopen("D:\\c2023-a\\level1\\p08_push_boxes\\map1.txt", "r");
           if(file!=NULL) {
               char arr[10][15];
               char c;
               for(int i=0;i<10;i++){
                   for(int j=0;j<15;j++){
                       c=getc(file);

                       arr[i][j]=c;
                   }
               }
               char *p[15]={arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],
                            arr[7],arr[8],arr[9],arr[10],arr[11],arr[12],arr[13],arr[14]};
               char *q[15]={arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],
                            arr[7],arr[8],arr[9],arr[10],arr[11],arr[12],arr[13],arr[14]};
               char *o[15]={arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],
                            arr[7],arr[8],arr[9],arr[10],arr[11],arr[12],arr[13],arr[14]};
               struct Zuobiao zuobiao;
               for(int i=0;i>=0;i++){
                   int conti=0;
                   for(int m=0;m<10;m++){
                       for(int n=0;n<15;n++){
                           if(arr[m][n]=='4')
                               conti=1;
                       }
                   }
                   draw(p,10,15);
                   zuobiao=Findperson(o,10,15,'2');
                   run(q,10,15,zuobiao.x,zuobiao.y);
                   Sleep(50);
                   system("cls");
                   if(conti==0)
                       break;
               }
               printf("You win!");
           }
           else{
               printf("error!");
           }
           Sleep(300);
           fclose(file);
       }else if(w=='2'){
           FILE *file = fopen("D:\\c2023-a\\level1\\p08_push_boxes\\map2.txt", "r");
           if(file!=NULL) {
               char arr[8][21];
               char c;
               for(int i=0;i<8;i++){
                   for(int j=0;j<21;j++){
                       c=getc(file);

                       arr[i][j]=c;
                   }
               }
               char *p[21]={arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],
                            arr[7],arr[8],arr[9],arr[10],arr[11],arr[12],arr[13],arr[14],
                            arr[15],arr[16],arr[17],arr[18],arr[19],arr[20]};
               char *q[21]={arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],
                            arr[7],arr[8],arr[9],arr[10],arr[11],arr[12],arr[13],arr[14],
                            arr[15],arr[16],arr[17],arr[18],arr[19],arr[20]};
                       char *o[21]={arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],
                                    arr[7],arr[8],arr[9],arr[10],arr[11],arr[12],arr[13],arr[14],
                                    arr[15],arr[16],arr[17],arr[18],arr[19],arr[20]};
               struct Zuobiao zuobiao;
               for(int i=0;i>=0;i++){
                   int conti=0;
                   for(int m=0;m<8;m++){
                       for(int n=0;n<21;n++){
                           if(arr[m][n]=='4')
                               conti=1;
                       }
                   }
                   draw(p,8,21);
                   zuobiao=Findperson(o,8,21,'2');
                   run(q,8,21,zuobiao.x,zuobiao.y);
                   Sleep(50);
                   system("cls");
                   if(conti==0)
                       break;
               }
               printf("You win!");
           }
           else{
               printf("error!");
           }
           Sleep(300);
           fclose(file);
       }
}
