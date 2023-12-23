#include <stdio.h>
#include <stdlib.h>
#include <minmax.h>
#include <stdbool.h>
#include <math.h>
#include "defination.h"
#include "evaluate_func.h"
#include "stack_point.h"
#include "hash_table.h"
#include "Zobrist.h"
Range limit(int (*b)[15]) {
    int Xmin, Xmax, Ymin, Ymax;
    Xmin = Ymin = 14;
    Xmax = Ymax = 0;//将最小值组Xmin，Ymin赋值最大初始化，最大值组相反处理，方便后续搜索时直接与i，j比较确定最终值。

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (*(b[i] + j) != Empty) {
                Xmin = min(Xmin, j);
                Ymin = min(Ymin, i);

                Xmax = max(Xmax, j);
                Ymax = max(Ymax, i);
            }
        }
    }

    //根据已有棋子范围，x和y轴方向均扩充5格，并确保最终range不越界。
    Range range;
    range.Xmin = Xmin - 4 >= 0 ? Xmin - 4 : 0;
    range.Xmax = Xmax + 4 <= 14 ? Xmax + 4 : 14;
    range.Ymin = Ymin - 4 >= 0 ? Ymin - 4 : 0;
    range.Ymax = Ymax + 4 <= 14 ? Ymax + 4 : 14;
    return range;
}

Range re_limit(Range range,Point *step){
    int p_Xmax = step->x + 4 <= 14? step->x+4:14;
    int p_Ymax = step->y + 4 <= 14? step->y+4:14;
    int p_Xmin = step->x - 4 >= 0? step->x - 4:0;
    int p_Ymin = step->y - 4 >= 0? step->y - 4:0;

    range.Xmin = min(p_Xmin,range.Xmin);
    range.Xmax = max(p_Xmax,range.Xmax);
    range.Ymin = min(p_Ymin,range.Ymin);
    range.Ymax = max(p_Ymax,range.Ymax);

    return (Range){range.Xmin,range.Xmax,range.Ymin,range.Ymax};
}

bool isPointInfluenced(Point point,Point step){
    int Xmin = max(step.x-4,0);
    int Xmax = min(step.x+4,14);
    int Ymin = max(step.y-4,0);
    int Ymax = min(step.y+4,14);
    //不在新点周边范围内
    if(point.x<Xmin || point.x > Xmax){
        return false;
    }

    if(point.y<Ymin || point.y > Ymax){
        return false;
    }
    //不在新点米子方向上
    if(point.x != step.x && point.y != step.y && point.y != point.x - step.x + step.y && point.y != -point.x +step.x +step.y){
        return false;
    }

    return true;
}

Stack* generate_old(int (*b)[15], Range range,enum piece side){

    Point_Value *values[15 * 15] = {NULL};
    int count = 0;

    for(int i = range.Ymin; i <= range.Ymax; i++){
        for(int j = range.Xmin;j <= range.Xmax; j++){

            if(*(b[i]+j) == Empty){
                Point step = {j,i};
                Point_Value *temp = NULL;

                values[count] = temp = (Point_Value*)malloc(sizeof(Point_Value));
                temp->point.x = j;
                temp->point.y = i;
                temp->value = evaluate_point(b,&step,side);

                //由小至大插入排序各个V_Point*
                int target = 0;
                for(; target < count; target++){
                    if(values[target]->value > values[count]->value){
                        break;
                    }
                }

                for(int n = count;n>target;n--){
                    values[n] = values[n-1];
                }

                values[target] = temp;

                count ++;
            }

        }
    }

    Stack *stack = create_stack(count);
    for(int i = 0; i < count; i ++){
        stack_push(stack,values[i]->point);
        free(values[i]);
    }

    return stack;
}

float generateRoughScore(int (*board)[15],enum piece side,enum piece sideMax,Point *step,HashTable *hashTable,unsigned long long (*randomSet)[15][2],unsigned long long *hashKey,int depthRequired){
    changeHash(hashKey,randomSet,step,side);
    if(HashMatch(hashTable,*hashKey)){
        Hash_value *p = hashTableGetAddress(hashTable,*hashKey);
        if(p->depth >= depthRequired){
            return side == sideMax?p->value:-p->value;
        }
    }else{
        return evaluate_point(board,step,side);
    }
    changeHash(hashKey,randomSet,step,side);
}

Stack* generate(int (*b)[15], Range range, enum piece side,enum piece sideMax, GenData *result,HashTable *hashTable,unsigned long long (*randomSet)[15][2],unsigned long long *hashKey,int depthRequired){
    result->data = (Point_Value*) malloc(225 * sizeof(Point_Value));
    int count = 0;
    int existInfinity = 0;

    for(int i = range.Ymin; i <= range.Ymax; i++){
        for(int j = range.Xmin;j <= range.Xmax; j++){

            if(*(b[i]+j) == Empty){
                Point step = {j,i};
                Point_Value *temp = NULL;

                result->sequence[count] = temp = result->data + count;
                temp->point = step;
                temp->value = evaluate_point(b,&step,side);
//                changeHash(hashKey,randomSet,&step,side);
//                if(HashMatch(hashTable,*hashKey)){
//                    Hash_value *p = hashTableGetAddress(hashTable,*hashKey);
//                    if(p->depth >= depthRequired){
//                        temp->value = p->value;
//                    }
//                }else{
//                    temp->value = evaluate_point(b,&step,side);
//                }
//                changeHash(hashKey,randomSet,&step,side);
//                generateRoughScore(b,side,sideMax,&step,hashTable,randomSet,hashKey,depthRequired);

                if(temp->value == INFINITY){
                    existInfinity = 1;
                }

                //由小至大插入排序各个V_Point*
                //!插入排序
                int target = 0;
                for(; target < count; target++){
                    if(result->sequence[target]->value > result->sequence[count]->value){
                        break;
                    }
                }

                for(int n = count;n>target;n--){
                    result->sequence[n] = result->sequence[n-1];
                }

                result->sequence[target] = temp;

                count ++;
            }

        }
    }

    Stack *stack = create_stack(count);
    if(existInfinity){
        for(int i = 0; i < count; i ++){
            if(result->sequence[i]->value == INFINITY){//某些位置被下子后会决定局面，则只搜索这些位置
                stack_push(stack,result->sequence[i]->point);
            }
        }
    }else{
        for(int i = 0; i < count; i ++){
            stack_push(stack,result->sequence[i]->point);
        }
    }

    return stack;
}

Stack* regenerate(int (*b)[15], Range *pRangeBefore, Range *range, enum piece side, Point *step, GenData *result, GenData *GenDataBefore,HashTable *hashTable,unsigned long long (*randomSet)[15][2],unsigned long long *hashKey,int depthRequired){
    int SIZE_FORMER = 225;

    Point_Value *data = (Point_Value*) malloc(450*sizeof (Point_Value ));

    Point_Value *old_sequence_copy[15 * 15] = {NULL};//former中的地址还会传给上层的可能的其他待搜索节点，为防止破坏former，先对former中数据进行复制

    int count_old_sequence = 0;
    for(int i = 0; GenDataBefore->sequence[i]; i++){
        old_sequence_copy[i] = data + count_old_sequence;
        old_sequence_copy[i]->value = GenDataBefore->sequence[i]->value;
        old_sequence_copy[i]->point = GenDataBefore->sequence[i]->point;
        count_old_sequence++;
    }

    //将新步以及受到新步影响的空点的原值从old_sequence_copy中剔除
    int count_delete = 0;
    for(int i = 0; old_sequence_copy[i]; i++){
        //former_copy中只含空点和新步（即上层所有空点）的值，不需判断受影响点是否为空
        if(isPointInfluenced(old_sequence_copy[i]->point, *step)){
            old_sequence_copy[i]=NULL;
            count_delete++;
        }
    }

    //Range Comparing and evaluate the new points.
    //评估新增区域各点时限制条件为 > 或 < ，用于避免重复评估旧区域的边界点
    Point_Value *newPoints[15*15];
    int count_new = 0;

    int count_dif_boundary = 0;
    Range possibleDelta = {0};//当新range与旧RangeBefore存在2个不同边界时，额外有一部分范围需要搜索。

    if(pRangeBefore->Xmin != range->Xmin){
        possibleDelta.Xmin = range->Xmin;
        possibleDelta.Xmax = pRangeBefore->Xmin-1;
        count_dif_boundary++;

        for(int j = pRangeBefore->Ymin; j <= pRangeBefore ->Ymax ; j++){
            for(int i = range->Xmin; i < pRangeBefore->Xmin;i++){
                //判断用于排除当前步在新范围内的情况，避免错误的重复搜索
                if(b[j][i] == Empty) {
                    newPoints[count_new] = data + SIZE_FORMER + count_new;
                    newPoints[count_new]->point = (Point) {i, j};
                    newPoints[count_new]->value = evaluate_point(b, &(newPoints[count_new]->point), side);

                    count_new++;
                }
            }
        }
    }

    if(pRangeBefore->Xmax != range ->Xmax){
        possibleDelta.Xmin = pRangeBefore->Xmax+1;
        possibleDelta.Xmax = range->Xmax;
        count_dif_boundary++;
        for(int j = pRangeBefore->Ymin; j <= pRangeBefore ->Ymax ; j++){
            for(int i = pRangeBefore->Xmax + 1; i <= range->Xmax;i++){

                if(b[j][i] == Empty) {
                    newPoints[count_new] = data + SIZE_FORMER + count_new;
                    newPoints[count_new]->point = (Point) {i, j};
                    newPoints[count_new]->value = evaluate_point(b, &(newPoints[count_new]->point), side);

                    count_new++;
                }
            }
        }
    }

    if(pRangeBefore->Ymin != range ->Ymin){
        possibleDelta.Ymin = range->Ymin;
        possibleDelta.Ymax = pRangeBefore->Ymin - 1;
        count_dif_boundary++;
        for(int j = range->Ymin; j < pRangeBefore->Ymin; j++){
            for(int i = pRangeBefore->Xmin; i <= pRangeBefore->Xmax; i++){
                if(b[j][i] == Empty) {
                    newPoints[count_new] = data + SIZE_FORMER + count_new;
                    newPoints[count_new]->point = (Point) {i, j};
                    newPoints[count_new]->value = evaluate_point(b, &(newPoints[count_new]->point), side);

                    count_new++;
                }
            }
        }
    }

    if(pRangeBefore->Ymax != range ->Ymax){
        possibleDelta.Ymin = pRangeBefore->Ymax + 1;
        possibleDelta.Ymax = range->Ymax;
        count_dif_boundary++;
        for(int j = pRangeBefore->Ymax + 1; j<= range->Ymax; j++){
            for(int i = pRangeBefore->Xmin; i <= pRangeBefore->Xmax; i++){
                if(b[j][i] == Empty) {
                    newPoints[count_new] = data + SIZE_FORMER + count_new;
                    newPoints[count_new]->point = (Point) {i, j};
                    newPoints[count_new]->value = evaluate_point(b, &(newPoints[count_new]->point), side);

                    count_new++;
                }
            }
        }
    }

    if(count_dif_boundary == 2){
        for(int j = possibleDelta.Ymin; j <= possibleDelta.Ymax; j++){
            for(int i = possibleDelta.Xmin; i <= possibleDelta.Xmax; i++){
                if(b[j][i] == Empty) {
                    newPoints[count_new] = data + SIZE_FORMER + count_new;
                    newPoints[count_new]->point = (Point) {i, j};
                    newPoints[count_new]->value = evaluate_point(b, &(newPoints[count_new]->point), side);

                    count_new++;
                }
            }
        }
    }

    //重新评估原区域中受到新步影响的空点
    for(int j = pRangeBefore->Ymin; j <= pRangeBefore->Ymax; j++) {
        for (int i = pRangeBefore->Xmin; i <= pRangeBefore->Xmax; i++){
           if(b[j][i] == Empty && isPointInfluenced((Point){i,j},*step)){
               newPoints[count_new] = data + SIZE_FORMER + count_new;
               newPoints[count_new]->point = (Point) {i, j};
               newPoints[count_new]->value = evaluate_point(b, &(newPoints[count_new]->point), side);

               count_new++;
           }
        }
    }

    //对newPoints插入排序
    for(int i = 0; i < count_new;i++){
        Point_Value *temp = newPoints[i];
        int target = 0;
        for(; target < i; target++){
            if(newPoints[target]->value > newPoints[i]->value){
                break;
            }
        }

        for(int n = i;n>target;n--){
            newPoints[n] = newPoints[n-1];
        }

        newPoints[target] = temp;
    }

    //按值大小，各点在result中排序并合并
    int tag_former = 0, tag_new = 0,tag_result = 0;
    while (tag_former < count_old_sequence && tag_new < count_new) {
        if(old_sequence_copy[tag_former] == NULL){
            tag_former++;
            continue;
        }
        if(newPoints[tag_new]==NULL){
            tag_new++;
            continue;
        }

        if(old_sequence_copy[tag_former]->value < newPoints[tag_new]->value){
            result->sequence[tag_result++] = old_sequence_copy[tag_former++];
        } else if(old_sequence_copy[tag_former]->value == newPoints[tag_new]->value){
            result->sequence[tag_result++] = old_sequence_copy[tag_former++];
            result->sequence[tag_result++] = newPoints[tag_new++];
        }else{
            result->sequence[tag_result++] = newPoints[tag_new++];
        }
    }

    if(tag_former != count_old_sequence && tag_new == count_new){
        while (tag_former < count_old_sequence){
            if(old_sequence_copy[tag_former] == NULL){
                tag_former++;
                continue;
            }
            result->sequence[tag_result++] = old_sequence_copy[tag_former++];
        }
    }else if(tag_former == count_old_sequence && tag_new != count_new){
        while(tag_new<count_new){
            result->sequence[tag_result++] = newPoints[tag_new++];
        }
    }

    result->data = data;
    Stack *stack = create_stack(tag_result);

    if(result->sequence[tag_result-1]->value == INFINITY){
        for (int i = 0; i < tag_result; i++) {
            if(result->sequence[i]->value == INFINITY) {
                stack_push(stack, result->sequence[i]->point);
            }
        }
    }else {
        for (int i = 0; i < tag_result; i++) {
            stack_push(stack, result->sequence[i]->point);
        }
    }
    return stack;
}

Stack* generate_new(int (*b)[15],enum piece side, GenData *result,Point **influenced_empty) {
    result->data = (Point_Value *) malloc(225 * sizeof(Point_Value));
    int count = 0;
    int existInfinity = 0;

    for (int i = 0; influenced_empty[i]; i++) {
        Point step = *influenced_empty[i];
        Point_Value *temp = NULL;

        result->sequence[count] = temp = result->data + count;
        temp->point = step;
        temp->value = evaluate_point(b, &step, side);

        if (temp->value == INFINITY) {
            existInfinity = 1;
        }

        //由小至大插入排序各个V_Point*
        //!插入排序
        int target = 0;
        for (; target < count; target++) {
            if (result->sequence[target]->value > result->sequence[count]->value) {
                break;
            }
        }

        for (int n = count; n > target; n--) {
            result->sequence[n] = result->sequence[n - 1];
        }

        result->sequence[target] = temp;

        count++;
    }


    Stack *stack = create_stack(count);
    if(existInfinity){
        for(int i = 0; i < count; i ++){
            if(result->sequence[i]->value == INFINITY){//某些位置被下子后会决定局面，则只搜索这些位置
                stack_push(stack,result->sequence[i]->point);
            }
        }
    }else{
        for(int i = 0; i < count; i ++){
            stack_push(stack,result->sequence[i]->point);
        }
    }

    return stack;
}

Stack* regenerate_new(int (*b)[15],Point **influenced_empty, enum piece side, Point *step, GenData *result, GenData *GenDataBefore){
    int SIZE_FORMER = 225;

    Point_Value *data = (Point_Value*) malloc(450*sizeof (Point_Value ));

    Point_Value *old_sequence_copy[15*15] = {NULL};//former中的地址还会传给上层的可能的其他待搜索节点，为防止破坏former，先对former中数据进行复制
    Point_Value *old_sequence_influenced[15*15] = {NULL};
    int count_copy = 0;
    int count_old_sequence = 0;
    int count_old_influenced = 0;
    for(int i = 0; GenDataBefore->sequence[i]; i++){
        if(!isPointInfluenced(GenDataBefore->sequence[i]->point, *step)){//旧空点中未受影响的部分
            data[count_copy] = *GenDataBefore->sequence[i];

            old_sequence_copy[count_old_sequence] = data + count_copy;
            count_copy++;
            count_old_sequence++;
        }else if(GenDataBefore->sequence[i]->point.x != step->x || GenDataBefore->sequence[i]->point.y != step->y) {//旧空点中受影响且不为所下新步的部分
            data[count_copy] = *GenDataBefore->sequence[i];

            old_sequence_influenced[count_old_influenced] = data + count_copy;//同时额外记录到受影响的序列中
            count_copy++;
            count_old_influenced++;
        }
    }

    //重新评估原区域中受到新步影响的空点
    for(int i = 0; i < count_old_influenced; i++){
        old_sequence_influenced[i]->value = evaluate_point(b,&(old_sequence_influenced[i]->point),side);
    }

    //评估新增的空点 利用新空点序列只是在原序列后增添空点的特性，确定新增的部分 新空点序列的原序列部分为前count_old_sequence个
    Point_Value *newPoints[15*15] = {NULL};
    int count_new = 0;
    for(int i = count_copy; influenced_empty[i]; i++){
        newPoints[count_new] = data + count_copy + count_new;
        newPoints[count_new]->point = *influenced_empty[i];
        newPoints[count_new]->value = evaluate_point(b,influenced_empty[i],side);
        count_new++;
    }

    //将old_sequence_influenced与newPoints序列合并
    for(int i = 0; i < count_old_influenced;i++){
        newPoints[count_new + i] = old_sequence_influenced[i];
    }
    count_new += count_old_influenced;

    //对合并后的newPoints插入排序
    for(int i = 0; i < count_new;i++){
        Point_Value *temp = newPoints[i];
        int target = 0;
        for(; target < i; target++){
            if(newPoints[target]->value > newPoints[i]->value){
                break;
            }
        }

        for(int n = i;n>target;n--){
            newPoints[n] = newPoints[n-1];
        }

        newPoints[target] = temp;
    }

//    printf("New Points:\n");
//    for(int i = 0;i <count_new; i++){
//        printf("%d:(%d,%d)\n",i,newPoints[i]->point.x,newPoints[i]->point.y);
//    }
//    printf("Copy_old Points:\n");
//    for(int i = 0;i <count_old_sequence; i++){
//        printf("%d:(%d,%d)\n",i,old_sequence_copy[i]->point.x,old_sequence_copy[i]->point.y);
//    }

    //按值大小，各点在result中排序并合并
    int tag_former = 0, tag_new = 0,tag_result = 0;
    while (tag_former < count_old_sequence && tag_new < count_new) {
        if(old_sequence_copy[tag_former] == NULL){
            tag_former++;
            continue;
        }
        if(newPoints[tag_new]==NULL){
            tag_new++;
            continue;
        }

        if(old_sequence_copy[tag_former]->value < newPoints[tag_new]->value){
            result->sequence[tag_result++] = old_sequence_copy[tag_former++];
        } else if(old_sequence_copy[tag_former]->value == newPoints[tag_new]->value){
            result->sequence[tag_result++] = old_sequence_copy[tag_former++];
            result->sequence[tag_result++] = newPoints[tag_new++];
        }else{
            result->sequence[tag_result++] = newPoints[tag_new++];
        }
    }

    if(tag_former != count_old_sequence && tag_new == count_new){
        while (tag_former < count_old_sequence){
            if(old_sequence_copy[tag_former] == NULL){
                tag_former++;
                continue;
            }
            result->sequence[tag_result++] = old_sequence_copy[tag_former++];
        }
    }else if(tag_former == count_old_sequence && tag_new != count_new){
        while(tag_new<count_new){
            result->sequence[tag_result++] = newPoints[tag_new++];
        }
    }

    result->data = data;
    Stack *stack = create_stack(tag_result);

    if(result->sequence[tag_result-1]->value == INFINITY){
        for (int i = 0; i < tag_result; i++) {
            if(result->sequence[i]->value == INFINITY) {
                stack_push(stack, result->sequence[i]->point);
            }
        }
    }else {
        for (int i = 0; i < tag_result; i++) {
            stack_push(stack, result->sequence[i]->point);
        }
    }
    return stack;
}

void find_nearby_empty(int (*b)[15],Point step,Point **empty,Point **pData){
    int Xmin = max(step.x - 4, 0);
    int Xmax = min(step.x + 4, 14);
    int Ymin = max(step.y - 4, 0);
    int Ymax = min(step.y + 4, 14);

    Point left = {Xmin,step.y};
    Point up = {step.x,Ymin};

    //计算斜线搜索的2个起点。左上到右下：l1:y=x-step->x+step->y  右上到左下：l2:y=-x+step->x+step->y  注意：棋盘坐标系与常规坐标系y轴方向不同。
    Point left_up, right_up;
    right_up.x = min(Xmax, -Ymin + step.x + step.y);
    right_up.y = -right_up.x + step.x + step.y;

    left_up.x = max(Xmin, Ymin + step.x - step.y);
    left_up.y = left_up.x - step.x + step.y;

    *pData = (Point*) malloc(32 * sizeof (Point));
    Point *data = *pData;
    int count = 0;
    for(int i = left.y, j = left.x; j <= Xmax; j++){
        if(b[i][j] == Empty){
            data[count] = (Point){j, i};
            empty[count] = data + count;
            count ++;
        }
    }

    for(int i = up.y,j = up.x;i<= Ymax;i++){
        if(b[i][j] == Empty){
            data[count] = (Point){j, i};
            empty[count] = data + count;
            count++;
        }
    }

    for(int i = left_up.y, j = left_up.x;i<= Ymax && j <= Xmax; i++,j++){
        if(b[i][j] == Empty){
            data[count] = (Point){j, i};
            empty[count] = data + count;
            count++;
        }
    }

    for(int i = right_up.y, j = right_up.x;i<=Ymax && j>= Xmin; i++, j--){
        if(b[i][j] == Empty){
            data[count] = (Point){j, i};
            empty[count] = data + count;
            count++;
        }
    }
}

void find_influenced_empty(int (*b)[15], Point **influenced_empty, Point **pData_all){
    *pData_all = (Point*) malloc(225*sizeof (Point));
    Point *data_all = *pData_all;
    int count_empty = 0;
    int count_step = 0;
    for(int i = 0; i< 15; i++){
        for(int j = 0; j<15; j++){
            if(b[i][j] != Empty){
                count_step++;
                Point step = {j,i};
                Point *data = NULL;
                Point *empty[32] = {NULL};
                find_nearby_empty(b,step,empty,&data);
                for(int k = 0; k < 32; k++){
                    if(empty[k]){
                        if(count_empty == 0){
                            data_all[count_empty] = *empty[k];
                            influenced_empty[count_empty] = data_all + count_empty;
                            count_empty++;
                        }else {
                            int duplicate = 0;
                            for (int q = 0; q < count_empty; q++) {
                                if (influenced_empty[q]->x == empty[k]->x && influenced_empty[q]->y == empty[k]->y) {
                                    duplicate = 1;
                                    break;
                                }
                            }
                            if(!duplicate) {
                                data_all[count_empty] = *empty[k];
                                influenced_empty[count_empty] = data_all + count_empty;
                                count_empty++;
                            }
                        }
                    }
                }
                free(data);
            }
        }
    }
}

void re_find_influenced_empty(int (*b)[15],Point *new_step, Point **influenced_empty, Point **pData_all,Point **influenced_empty_old){
    *pData_all = (Point*) malloc(225*sizeof (Point));
    Point *data_all = *pData_all;
    int count_empty = 0;
    for(int i = 0;influenced_empty_old[i];i++){//influenced_empty_old不可能满225个非NULL指针，不会越界
        if(influenced_empty_old[i]->x != new_step->x || influenced_empty_old[i]->y != new_step->y){
            data_all[count_empty] = *influenced_empty_old[i];
            influenced_empty[count_empty] = data_all + count_empty;
            count_empty++;
        }
    }

    Point *data = NULL;
    Point *new_empty[32] = {NULL};

    find_nearby_empty(b, *new_step, new_empty, &data);//要求寻找周边空位前new_step已不为Empty

    for(int k = 0; k < 32; k++){
        if(new_empty[k]){
            if(count_empty == 0){
                data_all[count_empty] = *new_empty[k];
                influenced_empty[count_empty] = data_all + count_empty;
                count_empty++;
            }else {
                int duplicate = 0;
                for (int q = 0; q < count_empty; q++) {
                    if (influenced_empty[q]->x == new_empty[k]->x && influenced_empty[q]->y == new_empty[k]->y) {
                        duplicate = 1;
                        break;
                    }
                }
                if(!duplicate) {
                    data_all[count_empty] = *new_empty[k];
                    influenced_empty[count_empty] = data_all + count_empty;
                    count_empty++;
                }
            }
        }
    }

    free(data);
}
