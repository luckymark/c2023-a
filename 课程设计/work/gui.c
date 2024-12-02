#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defination.h"
#include "raylib.h"
#include "stack_point.h"
#include "test.h"
#include "hash_table.h"

int Monitor;
int MonitorWidth;
int MonitorHeight;

int count_nodes = 0;
int count_match = 0;
int count_conflict[7] = {0};
int count_gen[7] = {0};
clock_t total[5] = {0};
clock_t start_t[5] = {0};
clock_t end_t[5] = {0};

void drawBoard(float sizeWidth, float sizeHeight, int (*b)[15],Stack* sequence){

    float ratio = sizeWidth/MonitorWidth*2;//全屏则比例为2；相对窗口化大小的比例。
    Color ColorBoard = {230,170,90,100};
    Rectangle BoardRec = {(sizeWidth - sizeHeight) / 2 + 10, 10, sizeHeight - 20, sizeHeight - 20};
    DrawRectangleRec(BoardRec, ColorBoard);

    float BoardLineThick = 5*ratio;
    float SubLineThick = 2*ratio;
    DrawRectangleLinesEx(BoardRec, BoardLineThick, BLACK);

    //各竖线位置的间隔距离
    float DeltaLine = (BoardRec.height-BoardLineThick*2)/16;

    //Note:线的位置不是中心位置，实际绘制有偏差，待后续调整。
    //竖线
    for(float i = 1; i <= 15 ;i++){
        Vector2 LineStartPos= {BoardRec.x +BoardLineThick + i * DeltaLine,BoardRec.y + BoardLineThick + DeltaLine};
        Vector2 LineEndtPos= {BoardRec.x +BoardLineThick + i * DeltaLine,BoardRec.y+BoardRec.height - BoardLineThick - DeltaLine};
        DrawLineEx(LineStartPos,LineEndtPos,SubLineThick,BLACK);
    }

    //横线
    for(float i = 1; i <= 15 ;i++){
        Vector2 LineStartPos= {BoardRec.x + BoardLineThick + DeltaLine,BoardRec.y +BoardLineThick + i * DeltaLine};
        Vector2 LineEndtPos= {BoardRec.x + BoardRec.width - BoardLineThick - DeltaLine,BoardRec.y +BoardLineThick + i * DeltaLine};
        DrawLineEx(LineStartPos,LineEndtPos,SubLineThick,BLACK);
    }


    //画棋子
    Vector2 PiecePosition;
    //标出最新棋子
    Point LatestPiece = stack_pop(sequence);
    Color colorMark = (Color) {0, 121, 241, 100};
    PiecePosition.x = BoardRec.x +BoardLineThick + (LatestPiece.x+1) * DeltaLine;
    PiecePosition.y = BoardRec.y +BoardLineThick + (LatestPiece.y+1) * DeltaLine;
    DrawCircleV(PiecePosition,DeltaLine/10*11/2,colorMark);
    stack_push(sequence,LatestPiece);
    //画棋子
    for(int i = 0;i<15;i++){
        for(int j = 0 ;j < 15; j++){
            Color color;
            switch (*(b[j]+i)) {
                case Black:
                    color = BLACK;
                    break;
                case White:
                    color = WHITE;
                    break;
                default:
                    continue;
            }
            PiecePosition.x = BoardRec.x +BoardLineThick + (i+1) * DeltaLine;
            PiecePosition.y = BoardRec.y +BoardLineThick + (j+1) * DeltaLine;

            DrawCircleV(PiecePosition,DeltaLine/10*9/2,color);

            //DrawCircleGradient(PiecePosition.x, PiecePosition.y, DeltaLine/10*9/2, WHITE, color);
        }
    }
}

Point getNewPiece(float sizeWidth, float sizeHeight, int (*b)[15],enum piece *side,Stack *sequence,unsigned long long *hashKey,unsigned long long (*randomSet)[15][2]){

    Rectangle BoardRec = {(sizeWidth - sizeHeight) / 2 + 10, 10, sizeHeight - 20, sizeHeight - 20};

    float ratio = sizeWidth/MonitorWidth*2;//全屏则比例为2；相对窗口化大小的比例。
    float BoardLineThick = 5*ratio;
    float SubLineThick = 2*ratio;

    int DeltaLine = BoardRec.height/16;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

        int x,y;
        x = y = -1; //默认值-1，无效的数组坐标。

        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        for(int i = 0; i <16; i++){
            //从边界起，如果在第 i 条竖线的右边，i+1的左边
            if(BoardRec.x +BoardLineThick + (i + 1) * DeltaLine > mouseX){
                if(BoardRec.x +BoardLineThick + (i + 0.5) * DeltaLine > mouseX){
                    x = i - 1;// -1 换算为数组的下标
                } else{
                    x = i+1 - 1;// -1 换算为数组的下标
                }
                //检验合法性
                if(x<0 || x>14){
                    x = -1;
                }
                break;
            }
        }

        for(int j = 0; j < 16; j++){
            //从边界起，如果在第 j 条竖线的右边，j+1的左边
            if(BoardRec.y +BoardLineThick + (j + 1) * DeltaLine > mouseY){
                if(BoardRec.y +BoardLineThick + (j + 0.5) * DeltaLine > mouseY){
                    y = j - 1;// -1 换算为数组的下标
                } else{
                    y = j + 1 - 1;// -1 换算为数组的下标
                }
                //检验合法性
                if(y<0 || y>14){
                    y = -1;
                }
                break;
            }
        }

        if( x == -1 || y == -1){
            return (Point){x,y};
        } else{
            Point step = {-1,-1};//用于放入棋子后记录本步到次序栈sequence。
            switch ( *(b[y]+x) ){
                case Empty:
                    *(b[y]+x) = *side;//放入棋子

                    step.x = x;
                    step.y = y;
                    stack_push(sequence,step);//添加到所放入棋子的顺序栈

                    changeHash(hashKey,randomSet,&step,*side);

                    *side *= -1;
                    break;
                default:
                    break;
            }
            return step;
        }
    }
}

void retract(int (*b)[15],Stack *sequence,unsigned long long hashKey,unsigned long long(*randomSet)[15][2],enum piece side){
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){

        if(!is_empty(sequence)) {
            Point retract = stack_pop(sequence);
            *(b[retract.y] + retract.x) = Empty;
            changeHash(&hashKey,randomSet,&retract,side);

            retract = stack_pop(sequence);
            *(b[retract.y] + retract.x) = Empty;
            changeHash(&hashKey,randomSet,&retract,-side);
        }

    }
}

int main(){
    int board[15][15] = {0};
//    int board[15][15] = {
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//
//    };
//    int board[15][15] = {
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0,
//            0, -1, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
//            0, 0, 1, -1, 1, 1, 0, -1, -1, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 1, 0, 1, -1, 1, -1, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 1, -1, 1, 1, -1, 1, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 1, -1, 1, 1, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, -1, 1, -1, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//
//    };
    Stack *sequence = create_stack(15*15);

    InitWindow(800,600,"Gobang");
    Image icon = LoadImage("icon.png");
    SetWindowIcon(icon);

    Monitor = GetCurrentMonitor();
    MonitorWidth = GetMonitorWidth(Monitor);
    MonitorHeight = GetMonitorHeight(Monitor);

    int sizeWidth = MonitorWidth/2;
    int sizeHeight = MonitorHeight/2;

    SetWindowSize(MonitorWidth/2,MonitorHeight/2);
    SetWindowPosition(MonitorWidth/4,MonitorHeight/4);

    /*//全屏
    ToggleFullscreen();
    SetWindowSize(MonitorWidth,MonitorHeight);
    sizeWidth = MonitorWidth;
    sizeHeight = MonitorHeight;*/


    SetTargetFPS(60);
    enum piece side = Black;
    enum piece sideMax = Black;
    enum piece win = Empty;

    unsigned long long randomSet[15][15][2] = {0};
    randomFill( randomSet);
    HashTable* hashTable = hashTableInit(1000*1000);
    unsigned long long hashKey = 0;

    while (!WindowShouldClose()){
        if(!win) {
            BeginDrawing();

            ClearBackground(WHITE);
            DrawFPS(10, 10);

            if (side == sideMax) {
                float value = 0;
                int layerLimit = 5;
                Point resultStep;

                //输出randomSet
//                for(int i = 0; i < 15; i++){
//                    for(int j = 0 ;j < 15 ;j ++){
//                        printf("(%d,%d) : %d,%d   ",j,i,randomSet[i][j][0],randomSet[i][j][1]);
//                    }
//                    printf("\n");
//                }

                //对整个棋盘先进行求hash,作为hashKey初始值。
//                for(int i = 0; i < 15; i++){
//                    for(int j = 0 ;j < 15 ;j ++){
//                        if(board[i][j] != Empty){
//                            Point step ={j,i};
//                            changeHash(&hashKey,randomSet,&step,board[i][j]);
//                        }
//                    }
//                }

                //resultStep = traverse3(board, sideMax, Max, NULL, &value, 1, 5, randomSet, &hashKey, hashTable,NULL);
                count_nodes = 0;
                count_match = 0;
                for(int i =0;i<7;i++){
                    count_conflict[i] = 0;
                    count_gen[i]=0;
                }
                for(int i =0;i<5;i++){
                    total[i] = 0;
                    start_t[i] = 0;
                    end_t[i] = 0;
                }

                start_t[0] = clock();
                resultStep = traverse_new(board, sideMax, Max, NULL, NULL, &value, 1, 7, randomSet, &hashKey, hashTable,NULL);

                end_t[0] = clock();
                total[0] += end_t[0] - start_t[0];

                for(int i =0;i<7;i++){
                    printf("Layer:%d %d times re_gen\n",i+1,count_gen[i]);
                }
                printf("Generate Time %lf\n",(double)total[2]/CLOCKS_PER_SEC);
                printf("Time: %lf s\nZobrist Replace Time:%lf\nTotal:%d nodes\nzobrist_match:%d times\n", (double)total[0]/CLOCKS_PER_SEC,(double)total[1]/CLOCKS_PER_SEC, count_nodes,count_match);
                for(int i =0;i<7;i++){
                    printf("Layer %d Hash Conflicts:%d\n",i+1,count_conflict[i]);
                }
                //迭代加深
//                for (int i = 3; i <= layerLimit; i += 2) {
//                    hashKey = 0;
//                    HashTable* hashTable = hashTableInit(1000*1000);
//                    resultStep = traverse3(board, sideMax, Max, NULL, &value, 1, i, randomSet, &hashKey, hashTable,NULL,NULL);
//                    if (value == INFINITY || value == -INFINITY) {
//                        break;
//                    }
//                    hashTableDelete(hashTable);
//                    printf("%d",i);
//                }

                //hashTableDelete(hashTable);
                changePiece(board, &resultStep, sideMax);
                stack_push(sequence, resultStep);
                side = -side;
            } else {
                //读取输入方的新棋子，并且压入栈中
                getNewPiece(sizeWidth, sizeHeight, board, &side, sequence,&hashKey,randomSet);

                retract(board, sequence,hashKey,randomSet,side);
            }

            Point lastStep = stack_pop(sequence);
            float w = isStepTerminate(board,&lastStep,-side,-side);
            if(w == INFINITY){
                win = -side;
            }
            stack_push(sequence,lastStep);

            drawBoard(sizeWidth, sizeHeight, board, sequence);

            EndDrawing();
        }else{
            BeginDrawing();

            ClearBackground(WHITE);

            drawBoard(sizeWidth, sizeHeight,board, sequence);

            char *EndWords = win == Black?"Black Wins":"White Wins";
            Color color = win == sideMax?(Color) {230, 41, 55, 200}:(Color) {0, 228, 48, 200};
            DrawText(EndWords,sizeWidth/2-265,sizeHeight/2-50,100,color);

            EndDrawing();
        }
    }

    CloseWindow();

    return 0;
}