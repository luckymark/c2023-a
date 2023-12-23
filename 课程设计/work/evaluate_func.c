#include <math.h>
#include <minmax.h>
#include "defination.h"
#include "board_control.h"
#include <stdio.h>

float pow_float(int x, int y);
float evaluate_line(int (*b)[15], Point point, int dx, int dy, enum piece sideMax);
float evaluate_point(int (*b)[15],Point *step,enum piece side);
float evaluate(int (*b)[15], enum piece sideMax);
float re_evaluate(int (*b)[15],enum piece sideMax,Point *step,enum piece side,float score);
float isStepTerminate(int (*b)[15], Point *step, enum piece sideMax, enum piece side);

float pow_float(int x, int y) {
    if(y < 0){//估值函数的设定
        return 0;
    }
    float result = 1;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

float evaluate(int (*b)[15], enum piece sideMax) {
    //value在各方向的分值。行r，列c，左上->右下diag_1,右上->左下diag_2。
    float value;
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

float evaluate_line(int (*b)[15], Point point, int dx, int dy, enum piece sideMax) {
    enum piece temp_side = Empty;
    int empty_before = 0;
    int count = 0;
    float value = 0;
    //一条线上的推进和估值
    for (int i = point.x, j = point.y; 0 <= i && i <= 14 && 0 <= j && j <= 14; i += dx, j += dy) {
        //末位不为空，无法通过下一位是否相异触发结算，首先单列处理。
        if (i + dx < 0 || i + dx > 14 || j + dy < 0 || j + dy > 14) {
            //前一位为空
            if (temp_side == Empty) {//前一位为空
                float sideNumber = *(b[j] + i) == sideMax ? 1 : -1;//当前与sideMax相同棋子得分为正，不同为负。
                if (*(b[j] + i) != Empty) {
                    //结算 单侧空1个棋子。
                    value += pow_float(10, count - 1) * sideNumber * 1;
                    break;
                }
            } else if (*(b[j] + i) == temp_side) {//前一位不为空并且本位与前一位相同，需要算入本位时
                float sideNumber = temp_side == sideMax ? 1 : -1;//前一位与sideMax相同棋子得分为正，不同为负。
                count++;
                //结算估值 单侧空或无空
                if (empty_before) {
                    if(count<5) {
                        value += pow_float(10, count - 1) * sideNumber * 1;
                    }else{//若5连估值无限
                        value = sideNumber == 1? INFINITY:-INFINITY;
                    }
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
                float sideNumber = temp_side == sideMax ? 1 : -1;//与sideMax相同棋子得分为正，不同为负。

                if (empty_before && *(b[j] + i) == Empty) {
                    //两侧有空
                    if(count < 4){
                        value += pow_float(10, count - 1) * sideNumber * 2;
                    }else{//活四与活五的估值
                        value = sideNumber == 1?INFINITY:-INFINITY;
                    }

                } else if (empty_before || *(b[j] + i) == Empty) {
                    //单侧有空
                    if (count < 5) {
                        value += pow_float(10, count - 1) * sideNumber * 1;
                    }else{
                        value = sideNumber == 1?INFINITY:-INFINITY;
                    }
                }else{
                    //两侧不空 ，0值或无限
                    if (count == 5){
                        value = sideNumber == 1?INFINITY:-INFINITY;
                    }
                }

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
}

float evaluate_line_range(int (*b)[15], Point point, int dx, int dy, Range range,enum piece sideMax) {
    enum piece temp_side = Empty;
    int empty_before = 0;
    int count = 0;
    float value = 0;
    //一条线上的推进和估值
    for (int i = point.x, j = point.y; range.Xmin <= i && i <= range.Xmax && range.Ymin <= j && j <= range.Ymax; i += dx, j += dy) {
        //末位不为空，无法通过下一位是否相异触发结算，首先单列处理。
        if (i + dx < range.Xmin || i + dx > range.Xmax || j + dy < range.Ymin || j + dy > range.Ymax) {
            //前一位为空
            if (temp_side == Empty) {//前一位为空
                float sideNumber = *(b[j] + i) == sideMax ? 1 : -1;//当前与sideMax相同棋子得分为正，不同为负。
                if (*(b[j] + i) != Empty) {
                    //结算 单侧空1个棋子。
                    value += pow_float(10, count - 1) * sideNumber * 1;
                    break;
                }
            } else if (*(b[j] + i) == temp_side) {//前一位不为空并且本位与前一位相同，需要算入本位时
                float sideNumber = temp_side == sideMax ? 1 : -1;//前一位与sideMax相同棋子得分为正，不同为负。
                count++;
                //结算估值 单侧空或无空
                if (empty_before) {
                    if(count<5) {
                        value += pow_float(10, count - 1) * sideNumber * 1;
                    }else{//若5连估值无限
                        value = sideNumber == 1? INFINITY:-INFINITY;
                    }
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
                float sideNumber = temp_side == sideMax ? 1 : -1;//与sideMax相同棋子得分为正，不同为负。

                if (empty_before && *(b[j] + i) == Empty) {
                    //两侧有空
                    if(count < 4){
                        value += pow_float(10, count - 1) * sideNumber * 2;
                    }else{//活四与活五的估值
                        value = sideNumber == 1?INFINITY:-INFINITY;
                    }

                } else if (empty_before || *(b[j] + i) == Empty) {
                    //单侧有空
                    if (count < 5) {
                        value += pow_float(10, count - 1) * sideNumber * 1;
                    }else{
                        value = sideNumber == 1?INFINITY:-INFINITY;
                    }
                }else{
                    //两侧不空 ，0值或无限
                    if (count == 5){
                        value = sideNumber == 1?INFINITY:-INFINITY;
                    }
                }

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
}

float isStepTerminate(int (*b)[15], Point *step, enum piece sideMax, enum piece side) {
    int Xmin, Xmax, Ymin, Ymax;
    Xmin = Xmax = step->x;
    Ymin = Ymax = step->y;//搜索范围初始为当次Step坐标。

    Xmin = Xmin - 4 >= 0 ? Xmin - 4 : 0;
    Ymin = Ymin - 4 >= 0 ? Ymin - 4 : 0;
    Xmax = Xmax + 4 <= 14 ? Xmax + 4 : 14;
    Ymax = Ymax + 4 <= 14 ? Ymax + 4 : 14;//确定上下左右搜索范围。

    for (int i = Xmin, j = step->y, count = 0; i <= Xmax; i++) {
        if (*(b[j] + i) == side) {
            count++;
        } else {
            count = 0;
        }
        if (count == 5) {
            return sideMax == side ? INFINITY : -INFINITY;//该步已终结对局。/sideMax*side*INFINITY
        }
    }

    for (int i = step->x, j = Ymin, count = 0; j <= Ymax; j++) {
        if (*(b[j] + i) == side) {
            count++;
        } else {
            count = 0;
        }
        if (count == 5) {
            return sideMax == side ? INFINITY : -INFINITY;//该步已终结对局。/sideMax*side*INFINITY
        }
    }

    //计算斜线搜索的2个起点。左上到右下：l1:y=x-step->x+step->y  右上到左下：l2:y=-x+step->x+step->y  注意：棋盘坐标系与常规坐标系y轴方向不同。
    Point p1, p2;
    p2.x = min(Xmax, -Ymin + step->x + step->y);
    p2.y = -p2.x + step->x + step->y;

    p1.x = max(Xmin, Ymin + step->x - step->y);
    p1.y = p1.x - step->x + step->y;

    for (int i = p1.x, j = p1.y, count = 0; i <= Xmax && j <= Ymax; i++, j++) {
        if (*(b[j] + i) == side) {
            count++;
        } else {
            count = 0;
        }
        if (count == 5) {
            return sideMax == side ? INFINITY : -INFINITY;//该步已终结对局。/sideMax*side*INFINITY
        }
    }

    for (int i = p2.x, j = p2.y, count = 0; i >= Xmin && j <= Ymax; i--, j++) {
        if (*(b[j] + i) == side) {
            count++;
        } else {
            count = 0;
        }
        if (count == 5) {
            return sideMax == side ? INFINITY : -INFINITY;//该步已终结对局。/sideMax*side*INFINITY
        }
    }

    return 0;
}

float evaluate_point(int (*b)[15],Point *step,enum piece side){
    int Xmin, Xmax, Ymin, Ymax;
    //确定上下左右搜索范围。
    Xmin = step->x - 4 >= 0 ? step->x - 4 : 0;
    Ymin = step->y - 4 >= 0 ? step->y - 4 : 0;
    Xmax = step->x + 4 <= 14 ? step->x + 4 : 14;
    Ymax = step->y + 4 <= 14 ? step->y + 4 : 14;
    Range range = {Xmin,Xmax,Ymin,Ymax};

    Point left = {Xmin,step->y};
    Point up = {step->x,Ymin};

    //计算斜线搜索的2个起点。左上到右下：l1:y=x-step->x+step->y  右上到左下：l2:y=-x+step->x+step->y  注意：棋盘坐标系与常规坐标系y轴方向不同。
    Point left_up, right_up;
    right_up.x = min(Xmax, -Ymin + step->x + step->y);
    right_up.y = -right_up.x + step->x + step->y;

    left_up.x = max(Xmin, Ymin + step->x - step->y);
    left_up.y = left_up.x - step->x + step->y;


    //若下己方棋子，正值收益
    changePiece(b,step,side);
    float value_self = 0;
    if(left_up.x <= 10) {
        value_self += evaluate_line_range(b, left_up, 1, 1, range, side);
    }
    if(right_up.x >= 4) {
        value_self += evaluate_line_range(b, right_up, -1, 1, range, side);
    }
    value_self += evaluate_line_range(b,left,1,0,range,side);
    value_self += evaluate_line_range(b,up,0,1,range,side);

    //若下敌方棋子，负值损失
    changePiece(b,step,-side);
    float value_rival = 0;
    if(left_up.x <= 10) {
        value_rival += evaluate_line_range(b, left_up, 1, 1, range, -side);
    }
    if(right_up.x >= 4) {
        value_rival += evaluate_line_range(b, right_up, -1, 1, range, -side);
    }
    value_rival += evaluate_line_range(b,left,1,0,range,-side);
    value_rival += evaluate_line_range(b,up,0,1,range,-side);

    changePiece(b,step,Empty);

    return value_self>value_rival? value_self:value_rival;
}

float re_evaluate(int (*b)[15],enum piece sideMax,Point *step,enum piece side,float score){
    //默认前提为传入的b已经下入新步Step
    Point left = {0,step->y};
    Point up = {step->x,0};

    Point left_up, right_up;

    right_up.x = min(14, step->x + step->y);
    right_up.y = -right_up.x + step->x + step->y;

    left_up.x = max(0, step->x - step->y);
    left_up.y = left_up.x - step->x + step->y;

    changePiece(b,step,Empty);
    float temp_old_score;
    //evaluate 4lines = score_old
    temp_old_score = evaluate_line(b,left,1,0,sideMax);
    if(temp_old_score == INFINITY || temp_old_score == -INFINITY){
        changePiece(b,step,side);
        return evaluate(b,sideMax);
    }
    score -= temp_old_score;

    temp_old_score = evaluate_line(b,up,0,1,sideMax);
    if(temp_old_score == INFINITY || temp_old_score == -INFINITY){
        changePiece(b,step,side);
        return evaluate(b,sideMax);
    }
    score -= temp_old_score;

    if(left_up.x <= 10){
        temp_old_score = evaluate_line(b,left_up,1,1,sideMax);
        if(temp_old_score == INFINITY || temp_old_score == -INFINITY){
            changePiece(b,step,side);
            return evaluate(b,sideMax);
        }
        score -= temp_old_score;
    }

    if(right_up.x >=4){
        temp_old_score = evaluate_line(b,right_up,-1,1,sideMax);
        if(temp_old_score == INFINITY || temp_old_score == -INFINITY){
            changePiece(b,step,side);
            return evaluate(b,sideMax);
        }
        score -= temp_old_score;
    }

    changePiece(b,step,side);
    //evaluate 4lines = score_new
    score += evaluate_line(b,left,1,0,sideMax);
    score += evaluate_line(b,up,0,1,sideMax);
    if(left_up.x <= 10){
        score += evaluate_line(b,left_up,1,1,sideMax);
    }
    if(right_up.x >=4){
        score += evaluate_line(b,right_up,-1,1,sideMax);
    }
    return score;
}