#include <stdio.h>
#include <minmax.h>
#include <math.h>
#include "raylib.h"

typedef struct {
    int x;
    int y;
} Point;

//每一个局面的下一步搜索范围如何确定？
typedef struct {
    int Xmin;
    int Xmax;
    int Ymin;
    int Ymax;
} Range;

enum piece {
    Empty = 0, Black = 1, White = -1
};
enum type {
    Max, Min
};

int evaluate(int (*b)[15],enum piece sideMax);
int evaluate_line(int (*b)[15], Point point, int dx, int dy, enum piece sideMax);
Point traverse(int (*b)[15], enum piece sideMax, enum type type, Point *step, int *pSuperiorLimit, int layer, int layerLimit);
Range limit(int (*b)[15]);//4位range数组用于储存矩形搜索范围Ymin,Ymax,Xmin,Xmax。
void changePiece(int (*b)[15], Point *point, enum piece piece);
void getInput(Point *input);
int pow_int(int x, int y);

int main() {
    int board[15][15] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    };
    Range range = {0, 14, 0, 14};
    enum piece sideMax, sideMin;
    sideMax = sideMin = Empty;

    //双方选择棋子
    sideMax = Black;
    sideMin = White;

    Point input = {7, 9};//后续应检查/确保输入坐标有效性。

    //第一步的决定,并将两种情况都由第一步推进至输入方下完棋，方便后续统一开始遍历博弈树。
    if (sideMax == Black) {//机器先手
        *(board[7] + 7) = Black;

        void getInput(Point *input);
        *(board[input.y] + input.x) = White;
    } else {//输入方先手
        *(board[input.y] + input.x) = Black;
    }

    limit(board);


    return 0;
}

int evaluate(int (*b)[15], enum piece sideMax) {
    //value在各方向的分值。行r，列c，左上->右下diag_1,右上->左下diag_2。
    int value;
    value = 0;

    Point start = {0, 0};
    for (start.x = 0, start.y = 0; start.x < 14; start.x++) {
        value += evaluate_line(b, start, 0, 1, sideMax);//纵向
    }
    for (start.x = 0, start.y = 0; start.y < 15; start.y++) {
        value += evaluate_line(b, start, 1, 0, sideMax);//横向
    }

    for(start.x = 0,start.y = 0; start.y<15;start.y++){
        if( start.y >= 4){//限制条件用于排除部分不可能形成五连的区域
            value += evaluate_line(b, start, 1, -1, sideMax);//右上
        }
        if(start.y <= 10){
            value += evaluate_line(b, start, 1, 1, sideMax);//右下
        }
    }
    for(start.x = 14,start.y = 0;start.y < 15;start.y++){
        if( start.y >= 4 && start.y != 14){//限制范围，并避免重复计算对角线的估值。
            value += evaluate_line(b, start, -1, -1, sideMax);//左上
        }
        if(start.y != 0 && start.y <=10 ){
            value += evaluate_line(b, start, -1, 1, sideMax);//左下
        }
    }
    return value;
}
int evaluate_line(int (*b)[15], Point point, int dx, int dy, enum piece sideMax) {
    enum piece temp_side = Empty;
    int empty_before = 0;
    int count = 0;
    int value = 0;
    //一条线上的推进和估值
    for (int i = point.x, j = point.y; 0 <= i && i <= 14 && 0 <= j && j <= 14; i += dx, j += dy) {
        //末位无法通过下一位是否相异触发结算，首先单列处理。
        if (i + dx < 0 || i + dx > 14 || j + dy < 0 || j + dy > 14) {
            //前一位为空
            if (temp_side == Empty) {
                int sideNumber = *(b[j] + i) == sideMax ? 1 : -1;//当前与sideMax相同棋子得分为正，不同为负。
                if (*(b[j] + i) != Empty) {
                    //结算 单侧空1个棋子。
                    value += pow_int(10, count - 1) * sideNumber * 1;
                    break;
                }
            } else if (*(b[j] + i) == temp_side) {//前一位不为空并且本位与前一位相同，需要算入本位时
                int sideNumber = temp_side == sideMax ? 1 : -1;//前一位与sideMax相同棋子得分为正，不同为负。
                count++;
                //结算估值 单侧空或无空
                if (empty_before) {
                    value += pow_int(10, count - 1) * sideNumber * 1;
                    break;
                }//双侧无空为0，r不增加。
            }
        }

        if (*(b[j] + i) == temp_side) {
            //相同棋子，无需估值，只需累计黑白棋子或者跳过空棋子。
            if (*(b[j] + i) == Empty) {
                empty_before = 1;//确保首个为空时empty_before正常更新为1
                continue;
            } else {
                count++;
            }

        } else {
            //遇到相异棋子，可能进行一次估值，并清空count。
            if (temp_side != Empty) {
                int sideNumber = temp_side == sideMax ? 1 : -1;//与sideMax相同棋子得分为正，不同为负。

                if (empty_before && *(b[j] + i) == Empty) {
                    //两侧有空
                    value += pow_int(10, count - 1) * sideNumber * 2;

                } else if (empty_before || *(b[j] + i) == Empty) {
                    //单侧有空
                    value += pow_int(10, count - 1) * sideNumber * 1;
                }//两侧不空 ，0值

                empty_before = 0;//前一位不为空，对当前位置更新empty_before
                count = 0;//相异且前一个不为空则最终清空原计数。
            }

            if (*(b[j] + i) == Empty) {
                empty_before = 1;
            } else {
                count++;
            }

            temp_side = *(b[j] + i);
        }

    }

    return value;
}//!缺少INFIITY的情况。
int pow_int(int x, int y){
    int result = 1;
    for(int i = 0; i < y;i++){
        result *= x;
    }
    return result;
}

int isStepTerminate(int (*b)[15], Point *step,enum piece sideMax,enum piece side){
    int Xmin, Xmax, Ymin, Ymax;
    Xmin = Xmax = step->x;
    Ymin = Ymax = step->y;//搜索范围初始为当次Step坐标。

    Xmin = Xmin - 4 >= 0 ? Xmin - 4 : 0;
    Ymin = Ymin - 4 >= 0 ? Ymin - 4 : 0;
    Xmax = Xmax + 4 <= 14 ? Xmax + 4 : 14;
    Ymax = Ymax + 4 <= 14 ? Ymax + 4 : 14;//确定上下左右搜索范围。

    for(int i=Xmin,j = step->y,count = 0;i<=Xmax;i++){
        if(*(b[j]+i) == side){
            count++;
        }else{
            count = 0;
        }
        if(count == 5){
            return sideMax == side? INFINITY:-INFINITY;//该步已终结对局。/sideMax*side*INFINITY
        }
    }

    for(int i=step->x,j = Ymin,count = 0;j<=Ymax;j++){
        if(*(b[j]+i) == side){
            count++;
        }else{
            count = 0;
        }
        if(count == 5){
            return sideMax == side? INFINITY:-INFINITY;//该步已终结对局。/sideMax*side*INFINITY
        }
    }

    //计算斜线搜索的2个起点。左上到右下：l1:y=x-step->x+step->y  右上到左下：l2:y=-x+step->x+step->y  注意：棋盘坐标系与常规坐标系y轴方向不同。
    Point p1,p2;
    p2.x = max(Xmin,-Ymin+step->x+step->y);
    p2.y = -p2.x+step->x+step->y;

    p1.x = min(Xmax,Ymin+step->x-step->y);
    p1.y = p1.x-step->x+step->y;

    for (int i = p1.x, j = p1.y, count = 0; i <= Xmax && j <= Ymax; i++, j++) {
        if(*(b[j]+i) == side){
            count++;
        }else{
            count = 0;
        }
        if(count == 5){
            return sideMax == side? INFINITY:-INFINITY;//该步已终结对局。/sideMax*side*INFINITY
        }
    }

    for (int i = p2.x, j = p2.y, count = 0; i>=Xmin && j <= Ymax; i--, j++) {
        if(*(b[j]+i) == side){
            count++;
        }else{
            count = 0;
        }
        if(count == 5){
            return sideMax == side? INFINITY:-INFINITY;//该步已终结对局。/sideMax*side*INFINITY
        }
    }

    return 0;
}

Range limit(int (*b)[15]) {
    int Xmin, Xmax, Ymin, Ymax;
    Xmin = Ymin = 14;
    Xmax = Ymax = 0;//将最小值组Xmin，Ymin赋值最大初始化，最大值组相反处理，方便后续搜索时直接与i，j比较确定最终值。

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (*(b[i] + j) != Empty) {
                Xmin = min(Xmin, j);
                Ymin = min(Xmin, j);

                Xmax = max(Xmax, j);
                Ymax = max(Xmax, j);
            }
        }
    }

    //根据已有棋子范围，x和y轴方向均扩充5格，并确保最终range不越界。
    Range range;
    range.Xmin = Xmin - 5 >= 0 ? Xmin - 5 : 0;
    range.Xmax = Xmax + 5 <= 14 ? Xmax + 5 : 14;
    range.Ymin = Ymin - 5 >= 0 ? Ymin - 5 : 0;
    range.Ymax = Ymax + 5 <= 14 ? Ymax + 5 : 14;
    return range;
}

void changePiece(int (*b)[15], Point *point, enum piece piece) {
    *(b[point->y] + point->x) = piece;
}

Point traverse(int (*b)[15], enum piece sideMax, enum type type, Point *step, int *pSuperiorLimit, int layer, int layerLimit) {//layer 为上层层数
    enum piece side = type == Max ? sideMax : -sideMax;//根据当前层的类型,确定相应棋子类型。
    int superiorLimit;//复制指针的值，指针仅用于修改上层的最终值。
    //!可否不创建变量，直接使用指针并兼容第一层？

    //!:默认层数 > 2。

    if(layer  >= 2) {
        superiorLimit = *(pSuperiorLimit);
        changePiece(b, step, -side);//!:本节点结束需要还原，所有layer>=2的层return前必定先还原所下步。在上层指定的位置下入上一层的棋子-side。

        int value = isStepTerminate(b, step, sideMax, -side);//对上层指定的步进行评估，判断上层类型棋子所下步是否终结对局。
        if (value) {
            Point result = {step->x, step->y};//返回本层所下的棋子位置坐标。

            if (type == Max) {
                if (value < superiorLimit) {
                    *(pSuperiorLimit) = value;
                }
            } else {
                if (value > superiorLimit) {
                    *(pSuperiorLimit) = value;
                }
            }

            changePiece(b,step,Empty);
            return result;
        }

        //到达层限制，仅判断是否修改上层值，必定结束，不需判断是否剪枝。
        if(layer == layerLimit){
            value = evaluate(b,sideMax);
            if (type == Max) {
                if (value < superiorLimit) {
                    *(pSuperiorLimit) = value;
                }
            } else {
                if (value > superiorLimit) {
                    *(pSuperiorLimit) = value;
                }
            }
            changePiece(b,step,Empty);
            return *step;
        }

    }

    Range range = limit(b);

    int limit = type == Max ? -INFINITY : INFINITY;//遍历所有子节点后，limit的值为节点所下步的最终值。
    Point resultStep = {-1,-1};//仅有第一层需要用于返回最优下一步。
    //遍历子节点
    for (int i = range.Xmin; i <= range.Xmax; i++) {
        for (int j = range.Ymin; j <= range.Ymax; j++) {
            if (*(b[j] + i) == Empty) {
                int former_limit = limit;//仅用于第一层判断limit是否被下层改变，若改变则同步更改resultStep。
                Point nextStep = {i, j};

                //temp_step在2层以上不会被实际使用，在2层最终会参与选出最优步返回给第1层。
                Point temp_step = traverse(b, sideMax, type == Max ? Min : Max, &nextStep, &limit,layer+1,layerLimit);//不断确定当前层的值limit

                //对2层以上 alpha-beta剪枝 或 修改上层值limit 第二层 返回最优Step结果记录
                if(layer >= 2) {
                    if (type == Max) {
                        if (limit >= superiorLimit) {
                            changePiece(b,step,Empty);//
                            return *step;//返回任意值，目的为提前结束该节点。因为首个节点为Max,可能返回INFINITY时对应的步作为resultStep。
                        }
                    } else {
                        if (limit <= superiorLimit) {
                            changePiece(b,step,Empty);
                            return *step;
                        }
                    }
                }

                if(layer == 1 && limit != former_limit){
                    resultStep = temp_step;
                }
            }
        }
    }
    //对于完成全部可能搜索，搜索子节点完成过程中本节点未从上节点剪枝的情况，还原棋盘，结束。对上层limit的值的更新已经在搜索确定本层值地的过程中同步完成。
    if(layer >= 2){
        *(pSuperiorLimit) = limit;
        changePiece(b,step,Empty);
        return *step;
    }

    if(layer == 1){
        return resultStep;
    }

}

void getInput(Point *input) {
    scanf("%2d,%2d", input->x, input->y);//查重，查越界。
}