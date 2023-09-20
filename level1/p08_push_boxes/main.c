#include<stdio.h>
#include<conio.h>
#include<windows.h>
char gamemap[100][100];
int box[100][100];
HANDLE out;
typedef struct {
    COORD A;
}cursor;
cursor role[10];
int step[10]={0,0,0,0,0,0,0,0};
int goal[10]={0,4,3,4,4,3};
int score[10]={0,0,0,0,0,0,0,0};
int level=1;
COORD markcursor={};
void cursorset(COORD A){
    SetConsoleCursorPosition(out,A);
}
void explanation(){
    cursorset((COORD){20,10});
    printf("步数=0");
    cursorset( (COORD){20,4} );
    printf("推箱子游戏");
    cursorset( (COORD) {0,0} );
}
void clear(){
     score[level]=0;
     for(int i=0;i<=20;i++){
         for(int j=0;j<=20;j++){
             gamemap[i][j]='a';
             box[i][j]=0;
         }
     }
     system("cls");
}
void mapin(){
    switch(level){
        case 1 :
            freopen("C:\\Users\\scanffer\\CLionProjects\\c2023-a\\level1\\p08_push_boxes\\第一关.txt","r",stdin);
            break;
        case 2 :
            freopen("C:\\Users\\scanffer\\CLionProjects\\c2023-a\\level1\\p08_push_boxes\\第二关.txt","r",stdin);
            break;
        case 3 :
            freopen("C:\\Users\\scanffer\\CLionProjects\\c2023-a\\level1\\p08_push_boxes\\第三关.txt","r",stdin);
            break;
        case 4 :
            freopen("C:\\Users\\scanffer\\CLionProjects\\c2023-a\\level1\\p08_push_boxes\\第四关.txt","r",stdin);
            break;
        case 5 :
            freopen("C:\\Users\\scanffer\\CLionProjects\\c2023-a\\level1\\p08_push_boxes\\第五关.txt","r",stdin);
            break;
        default: break;
    }
    char ch;
    for(int j=0;;j++){
        for(int i=0;;i++){
            box[i][j]=0;
            ch=getchar();
            if(ch=='\n')break;
            if(ch=='1')box[i][j]=1;
            if(ch=='*')return;
            gamemap[i][j]=ch;
        }
    }
}
void mapout(){
    for(int j=0;j<=10;j++){
        for(int i=0;i<=10;i++){
            if(gamemap[i][j]=='*')return;
            if(gamemap[i][j]=='a')printf(" ");
            else printf("%c",gamemap[i][j]);
        }
        printf("\n");
    }
}
void move(COORD *A,int key){//左 75 上 72 右 77 下 80
    int x=A->X,y=A->Y;
    cursorset(*A);
    printf(" ");
    int flag=0;
    if(gamemap[A->X][A->Y]=='0')flag=1;
    if(key==75){
        A->X--;
        cursorset(*A);
        printf("A");
        if(box[A->X][A->Y]){
            box[A->X][A->Y]=0;
            box[A->X-1][A->Y]=1;
            cursorset( (COORD) {A->X-1,A->Y} );
            printf("1");
            if(gamemap[A->X][A->Y]=='0')score[level]--;
            if(gamemap[A->X-1][A->Y]=='0')score[level]++;
        }
    }
    if(key==72){
        A->Y--;
        cursorset(*A);
        printf("A");
        if(box[A->X][A->Y]){
            box[A->X][A->Y]=0;
            box[A->X][A->Y-1]=1;
            cursorset( (COORD) {A->X,A->Y-1} );
            printf("1");
            if(gamemap[A->X][A->Y]=='0')score[level]--;
            if(gamemap[A->X][A->Y-1]=='0')score[level]++;
        }
    }
    if(key==77){
        A->X++;
        cursorset(*A);
        printf("A");
        if(box[A->X][A->Y]){
            box[A->X][A->Y]=0;
            box[A->X+1][A->Y]=1;
            cursorset( (COORD) {A->X+1,A->Y} );
            printf("1");
            if(gamemap[A->X][A->Y]=='0')score[level]--;
            if(gamemap[A->X+1][A->Y]=='0')score[level]++;
        }
    }
    if(key==80){
        A->Y++;
        cursorset(*A);
        printf("A");
        if(box[A->X][A->Y]){
            box[A->X][A->Y]=0;
            box[A->X][A->Y+1]=1;
            cursorset( (COORD) {A->X,A->Y+1} );
            printf("1");
            if(gamemap[A->X][A->Y]=='0')score[level]--;
            if(gamemap[A->X][A->Y+1]=='0')score[level]++;
        }
    }
    if(flag){
        cursorset( (COORD){x,y} );
        printf("0");
    }
}
int movecheck(COORD A,int key){//左 75 上 72 右 77 下 80
    int x=A.X,y=A.Y;
    if(key==75){
        if(box[x-1][y])
            if(gamemap[x-2][y]=='#' || box[x-2][y])return 0;
        if(gamemap[x-1][y]=='#')return 0;
    }
    else if(key==72){
        if(box[x][y-1])
            if(gamemap[x][y-2]=='#' || box[x][y-2])return 0;
        if(gamemap[x][y-1]=='#')return 0;
    }
    else if(key==77){
        if(box[x+1][y])
            if(gamemap[x+2][y]=='#' || box[x+2][y])return 0;
        if(gamemap[x+1][y]=='#')return 0;
    }
    else if(key==80){
        if(box[x][y+1])
            if(gamemap[x][y+2]=='#' || box[x][y+2])return 0;
        if(gamemap[x][y+1]=='#')return 0;
    }
    if(key>80)return 0;
    return 1;
}
void gamerun(){
     clear();
     explanation();
     mapin();
     mapout();
     COORD A=role[level].A;
     cursorset(A);
     while(1){
         if(kbhit()){
             int key=getch();
             if(key==13){
                 gamerun();
                 return ;
             }
             if(movecheck(A,key)){
                 move(&A,key);
                 cursorset((COORD){20,10});
                 printf("步数=%d",++step[level]);
                 cursorset(A);
             }
         }
         if(score[level]==goal[level]){
             level++;
             if(level==6)return ;
             gamerun();
             return ;
         }
     }
}
int main(){
    out= GetStdHandle(STD_OUTPUT_HANDLE);
    role[1].A=(COORD){4,4},role[2].A=(COORD){1,1},role[3].A=(COORD){2,3};
    role[4].A=(COORD){1,2},role[5].A=(COORD){2,1};
    gamerun();
}
