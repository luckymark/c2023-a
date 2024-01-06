#include "raylib.h"
#include <stdio.h>
#include "stack.h"
#include <limits.h>
#include <stdbool.h>
enum chessboard{
    Space=0,black=-1,white=1
};
void drawChessboard(int n,double len,int **map) {
    for(int i=1;i<=n;i++) {
        DrawLine(len*i, len, len*i, n*len, BLACK);
    }
    for(int j=1;j<=n;j++){
        DrawLine(len, len*j, n*len, len*j, BLACK);
    }
    DrawCircle(len*(n+1)/2,len*(n+1)/2,len/8,BLACK);
    DrawCircle(len*(n+5)/4,len*(n+5)/4,len/8,BLACK);
    DrawCircle(len*((n+5)/4+6),len*((n+5)/4+6),len/8,BLACK);
    DrawCircle(len*(n+5)/4,len*((n+5)/4+6),len/8,BLACK);
    DrawCircle(len*((n+5)/4+6),len*(n+5)/4,len/8,BLACK);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(map[i][j]==white)DrawCircle(len*(i+1),len*(j+1),len/5*2,WHITE);
            if(map[i][j]==black)DrawCircle(len*(i+1),len*(j+1),len/5*2,BLACK);
        }
    }
}
void init(int **map,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            map[i][j]=Space;
        }
    }
}//对数组进行初始化
_Bool Regret2(int **map,int n,ArrayStack stack) {
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 pos = popStack(stack);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (pos.x > 25 + i * 50 && pos.x < 75 + i * 50 && pos.y > 25 + j * 50 && pos.y < 75 + j *
                                                                                                      50) {
                    map[i][j] = Space;
                    return 1;//
                }
            }
        }
    }
    return 0;
}
_Bool isWiningwhite(int **map,int n) {
    int map2[n+1][n+1];
    int gameover=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            map2[i][j]=map[i][j];
            if(map[i][j]==0) {
                gameover=0;
            }
        }
    }
    if(!gameover) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (map2[i][j] == white && map2[i][j + 1] == white && map2[i][j + 2] == white && map2[i][j + 3] == white &&
                    map2[i][j + 4] == white) {
                    return true;
                }else if (map2[i][j] == white && map2[i + 1][j] == white&& map2[i + 2][j] == white &&
                          map2[i + 3][j] == white &&
                          map2[i + 4][j] == white) {
                    return true;
                }  else if (map2[i][j] == white && map2[i + 1][j + 1] == white && map2[i + 2][j + 2] == white&&
                            map2[i + 3][j + 3] == white &&
                            map2[i + 4][j + 4] == white) {
                    return true;
                } else if (map2[i][j] ==white && map2[i - 1][j + 1] == white && map2[i - 2][j + 2] == white &&
                           map2[i - 3][j + 3] == white &&
                           map2[i - 4][j + 4] == white) {
                    return true;
                }
            }
        }
    }
    return  false;
}
_Bool isWiningblack(int **map,int n) {
    int map2[n+1][n+1];
    int gameover=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            map2[i][j]=map[i][j];
            if(map[i][j]==0) {
                gameover=0;
            }
        }
    }
    if(!gameover) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (map2[i][j] == black&& map2[i][j + 1] == black && map2[i][j + 2] == black &&
                    map2[i][j + 3] == black &&
                    map2[i][j + 4] == black) {
                    return true;
                }  else if (map2[i][j] == black && map2[i + 1][j] == black&& map2[i + 2][j] ==black &&
                            map2[i + 3][j] == black &&
                            map2[i + 4][j] == black) {
                    return true;
                } else if (map2[i][j] == black && map2[i + 1][j + 1] == black && map2[i + 2][j + 2] ==black &&
                           map2[i + 3][j + 3] == black && map2[i + 4][j + 4] == black) {
                    return true;
                }  else if (map2[i][j] == black && map2[i - 1][j + 1] == black && map2[i - 2][j + 2] == black &&
                            map2[i - 3][j + 3] == black && map2[i - 4][j + 4] == black) {
                    return true;
                }
            }
        }
        //DrawText("black wins!",300,300,100,GREEN);
    }
    return  false;
}
_Bool gameOver(int**map,int n){
    if(isWiningblack(map,n)|| isWiningwhite(map,n)){
        return true;
    }else return false;
}
int goBang_scoreTable(int self, int enemy){
    if(self>5) return 20000;
    if(self==5&&enemy==0) return 20000;
    if(self==5&&enemy==1) return 20000;
    if(self==5&&enemy==2) return 20000;
    if(self==4&&enemy==0) return 5000;
    if(self==4&&enemy==1) return 300;
    if(self==4&&enemy==2) return 100;
    if(self==3&&enemy==0) return 300;
    if(self==3&&enemy==1) return 100;
    if(self==3&&enemy==2) return 50;
    if(self==2&&enemy==0) return 50;
    if(self==2&&enemy==1) return 20;
    if(self==2&&enemy==2) return 10;
    if(self==1&&enemy==0) return 10;
    if(self==1&&enemy==1) return 5;
    if(self==1&&enemy==2) return 3;
}//分数表
int goBang_getHorizontalScore(int **map,int r,int c,int color){
    //从c向左遍历直到遇到空白，或者其他棋子
    int self=1;
    int enemy=0;
    for(int i=c-1;i>=0;i--){
        if(c==0){
            enemy++;
        }else if(map[r][i]==color){
            self++;
        } else if(map[r][i]==0){
            break;
        } else{
            enemy++;
            break;
        }
    }
    for(int i=c+1;i<15;i++){
        if(c==14){
            enemy++;
        }if(map[r][i]==color){
            self++;
        } else if(map[r][i]==0){
            break;
        } else{
            enemy++;
            break;
        }
    }//右遍历
    return goBang_scoreTable(self, enemy);
}//水平得分情况
int goBang_getVerticalScore(int **map,int r,int c,int color){
    int self=1;
    int enemy=0;
    for(int i=r-1;i>=0;i--){
        if(r==0){
         enemy++;
        }else if(map[i][c]==color){
            self++;
        } else if(map[i][c]==0){
            break;
        } else{
            enemy++;
            break;
        }
    }
    for(int i=r+1;i<15;i++){
        if(r==14){
            enemy++;
        }else if(map[i][c]==color){
            self++;
        } else if(map[i][c]==0){
            break;
        } else{
            enemy++;
            break;
        }
    }
    return goBang_scoreTable(self, enemy);
}//竖直得分情况
int goBang_getLhtScore(int **map,int r,int c,int color){
    int self=1;
    int enemy=0;
    for(int i=r+1,k=c-1;i<15&&k>=0;i++,k--){
        if(r==14||c==0){
         enemy++;
        }else if(map[i][k]==color){
            self++;
        } else if(map[i][k]==0){
            break;
        } else{
            enemy++;
            break;
        }
    }
    for(int i=r-1,k=c+1;i>=0&&k<15;i--,k++){
        if(r==0||c==14){
         enemy++;
        }else if(map[i][k]==color){
            self++;
        } else if(map[i][k]==0){
            break;
        } else{
            enemy++;
            break;
        }
    }
    return goBang_scoreTable(self, enemy);
}//左斜得分情况
int goBang_getRhtScore(int **map,int r,int c,int color){
    int self=1;
    int enemy=0;
    for(int i=r+1,k=c+1;i<15&&k<15;i++,k++){
        if(c==14||r==14) {
            enemy++;
        }else if(map[i][k]==color){
            self++;
        } else if(map[i][k]==0){
            break;
        } else{
            enemy++;
            break;
        }
    }
    for(int i=r-1,k=c-1;i>=0&&k>=0;i--,k--){
        if(c==0||c==0){
            enemy++;
        }else if(map[i][k]==color){
            self++;
        } else if(map[i][k]==0){
            break;
        } else{
            enemy++;
            break;
        }
    }
    return goBang_scoreTable(self, enemy);
}//右斜得分情况
int goBang_getScore(int **map,int r,int c,int color){
    int numH1= goBang_getHorizontalScore(map,r,c,color);
    int numV1= goBang_getVerticalScore(map,r,c,color);
    int numL1= goBang_getLhtScore(map,r,c,color);
    int numR1= goBang_getRhtScore(map,r,c,color);
    int xScore=numH1;
    int yScore=numV1;
    int IScore=numL1;
    int RScore=numR1;
    return xScore+yScore+IScore+RScore;
}//初版模型，之后会分别计算人和ai的分数
typedef struct Zuobiao{
    int row;
    int col;
}Zuobiao;
typedef struct Chess{
    struct Zuobiao zuobiao;
    int score;
};
struct Chess goBang_CalculateBest(int **map,int color){
    int max=0;
    struct Chess zuobiao;
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            if(map[i][j]!=0) continue;
            zuobiao.score= goBang_getScore(map,i,j,color);
            if(zuobiao.score>=20000) {
                zuobiao.zuobiao.row=i;
                zuobiao.zuobiao.col=j;
                return zuobiao;
            }
            if(zuobiao.score>max){
                max=zuobiao.score;
                zuobiao.zuobiao.row=i;
                zuobiao.zuobiao.col=j;
            }
        }
    }
    return zuobiao;
}

bool emptyCells(int**map,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(map[i][j]==Space) return true;
        }
    }
    return false;
}//判断棋盘是否有子可下

int MAX(int a,int b){
    return a>=b?a:b;
}
int MIN(int a,int b){
    return a<=b?a:b;
}
int evaLuate(int **map,int color){
    int levelself=-20000;
    int levelenemy=-20000;
    int score1;
    int score2;
    if(!emptyCells(map,15)){
        return 0;
    }else{
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                if(map[i][j]!=Space&&map[i][j]==color) {
                    score1 = goBang_getScore(map, i, j, color);
                    levelself += score1;
                }else if(map[i][j]!=Space&&map[i][j]==-color){
                    score2= goBang_getScore(map,i,j,-color);
                    levelenemy+=score2;
                }
            }
        }
    }
    return levelself-levelenemy;

}
int EMPTYCELLS(int**map){
    int empty=0;
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            if(map[i][j]==0)
                empty++;
        }
    }
    return empty;
}//获取棋盘中空位置的长度
typedef struct Zuobiao2{
    struct Zuobiao zuobiaoxy[225];
};
struct Zuobiao2 Findemptycells(int **map,int color){
    struct Zuobiao2 emptycells;
    int k=0;int exchange;struct Zuobiao exchangezuobiao;
    int empty= EMPTYCELLS(map);
    int score[empty];
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            if(map[i][j]==Space){
                emptycells.zuobiaoxy[k].row=i;
                emptycells.zuobiaoxy[k++].col=j;
            }
        }if(k==empty) break;
    }
    for(int m=0;m<empty;m++){
        map[emptycells.zuobiaoxy[m].row][emptycells.zuobiaoxy[m].col]=color;
        score[m]= evaLuate(map,color);
        map[emptycells.zuobiaoxy[m].row][emptycells.zuobiaoxy[m].col]=Space;
    }
    for(int n=0;n<empty-1;n++){
        for(int w=0;w<empty-1;w++){
            if(score[w]<score[w+1]){
                exchange=score[w];
                score[w]=score[w+1];
                score[w+1]=exchange;
                exchangezuobiao=emptycells.zuobiaoxy[w];
                emptycells.zuobiaoxy[w]=emptycells.zuobiaoxy[w+1];
                emptycells.zuobiaoxy[w+1]=exchangezuobiao;
            }
        }
    }
    return emptycells;
}//获取空位置的集合
struct Chess alphaBeta(int **map,int alpha,int beta,bool maxminiplayer,int depth,int color){
    struct Chess chess;
    struct Chess move;
    if(gameOver(map,15)|| !emptyCells(map,15)){
        chess.score= evaLuate(map,color);
        chess.zuobiao.row=-1;
        chess.zuobiao.col=-1;
        return chess;
    }
    if(depth==0){
        if(isWiningblack(map,15)) {
            if(color==black)move.score = 20000;
            else move.score=-20000;
        }else if(isWiningblack(map,15)) {
            if(color==white)move.score = 20000;
            else move.score=-20000;
        }
        move.score= evaLuate(map,color);
        move.zuobiao.row = -1;
        move.zuobiao.col = -1;
        return move;
    }
    struct Chess bestMove;
    if(maxminiplayer){
        bestMove.score=INT_MIN;
        struct Zuobiao2 emptycells= Findemptycells(map,color);
        for(int k=0;k<10;k++){
            map[emptycells.zuobiaoxy[k].row][emptycells.zuobiaoxy[k].col]=color;
            if(isWiningblack(map,15)) move.score=INT_MAX;
            move= alphaBeta(map,alpha,beta,false,depth-1,color);
            move.zuobiao.row=emptycells.zuobiaoxy[k].row;
            move.zuobiao.col=emptycells.zuobiaoxy[k].col;
            map[emptycells.zuobiaoxy[k].row][emptycells.zuobiaoxy[k].col]=Space;
            if(move.score>bestMove.score){
                bestMove=move;
            }
            //printf(" %d",bestMove.score);
            alpha= MAX(alpha,bestMove.score);
            if(alpha>=beta){
                //printf("cut");
                break;
            }
        }
    }else{
        bestMove.score=INT_MAX;
        struct Zuobiao2 emptycells= Findemptycells(map,-color);
        for(int k=0;k<10;k++){
            map[emptycells.zuobiaoxy[k].row][emptycells.zuobiaoxy[k].col]=-color;

            move= alphaBeta(map,alpha,beta,true,depth-1,color);

            map[emptycells.zuobiaoxy[k].row][emptycells.zuobiaoxy[k].col]=Space;
            if(move.score<bestMove.score){
                bestMove=move;
            }
            beta= MIN(beta,bestMove.score);
            if(alpha>=beta){
                //printf("cut");
                break;
            }
        }
    }
    return bestMove;
}
struct Zuobiao action(int **map,int color){
    struct Zuobiao Move;
    struct Chess bestMove;
    if(map[7][7]==Space) {
        Move.row = 7;
        Move.col = 7;
        return Move;
    }
    int empty= EMPTYCELLS(map);
    if(empty==224){
        Move.row=8;
        Move.col=7;
        return Move;
    }
     bestMove= alphaBeta(map,INT_MIN,INT_MAX,true,8,color);
    return bestMove.zuobiao;
}
struct Zuobiao Aigo(int **map, int *color) {
    struct Zuobiao zuobiao;
    zuobiao = action(map, *color);
    map[zuobiao.row][zuobiao.col] = *color;
    *color *= -1;
    return zuobiao;
}
int main() {
    Vector2 pos;
    Vector2 pos2;
    int color = black;
    int map[15][15];
    int *p[15] = {map[0], map[1], map[2], map[3], map[4], map[5], map[6], map[7],
                  map[8], map[9], map[10], map[11], map[12],
                  map[13], map[14]};
    init(p, 15);
    InitWindow(800, 800, "");
    SetTargetFPS(60);
    struct Stack stack;
    initStack(&stack);
    drawChessboard(15, 50, p);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BROWN);
        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
            struct Zuobiao zuobiao = Aigo(p, &color);
            pos2.x = (zuobiao.row + 1) * 50;
            pos2.y = (zuobiao.col + 1) * 50;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int down = 0;
            if (!gameOver(p, 15)) {
                pos.x = GetMouseX();
                pos.y = GetMouseY();
                for (int i = 0; i < 15; i++) {
                    for (int j = 0; j < 15; j++) {
                        if (map[i][j] == 0 && pos.x > 25 + i * 50 && pos.x < 75 + i * 50 && pos.y > 25 + j * 50 &&
                            pos.y < 75 + j * 50) {
                            map[i][j] = color;
                            down = 1;//假如确实下了子才变色
                        }
                    }
                }
                if (down && !gameOver(p, 15)) {
                    color *= -1;
                    struct Zuobiao zuobiao = Aigo(p, &color);
                    pos2.x = (zuobiao.row + 1) * 50;
                    pos2.y = (zuobiao.col + 1) * 50;
                }
            }
            if (down) {
                pushStack(&stack, pos);
                pushStack(&stack, pos2);
            }
        }
        Regret2(p, 15, &stack);
        Regret2(p, 15, &stack);
        drawChessboard(15, 50, p);
       if(gameOver(p,15)&&color==white){
          DrawText("Black wins",300,300,100,BLUE);
        }if(gameOver(p,15)&&color==black){
            DrawText("White wins",300,300,100,RED);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
