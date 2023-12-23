#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <minmax.h>
#include <assert.h>
#include "defination.h"
#include "board_control.h"
#include "evaluate_func.h"
#include "generate.h"
#include "stack_point.h"
#include "hash_table.h"
#include "Zobrist.h"
#include "MT199937.h"

//extern int count_nodes;
//extern int count_match;
//extern int count_conflict[7];
//extern int count_gen[7];
//extern clock_t total[5];
//extern clock_t start_t[5],end_t[5];

int count_nodes;
int count_match;
int count_conflict[7];
int count_gen[7];
clock_t total[5];
clock_t start_t[5],end_t[5];

Point traverse_new(int (*b)[15], enum piece sideMax, enum type type, Point *step, int *pCount_step, float *pSuperiorLimit, int layer, int layerLimit, unsigned long long (*randomSet)[15][2], unsigned long long *hashKey, HashTable *hashTable, newData *dataBefore) {//layer 为上层层数
    enum piece side = type == Max ? sideMax : -sideMax;//根据当前层的类型,确定相应棋子类型。
    float superiorLimit;//复制指针的值，指针仅用于修改上层的最终值。
    //!可否不创建变量，直接使用指针并兼容第一层？
    //!:默认搜索2层以上，不含2层。

    Hash_value *unfinished = NULL;
    if(layer >= 2) {
        superiorLimit = *(pSuperiorLimit);
        changePiece(b, step, -side);//在上层指定的位置下入上一层的棋子-side。所有layer>=2的层return前必定先还原所下步。
        changeHash(hashKey, randomSet, step, -side);//下入棋子后，相应地更新hashKey

        float value;

        //!:考虑在上一层提前判断，避免多次判断
        //到达层限制，仅判断是否修改上层值，必定结束，不需判断是否剪枝。
        if(layer == layerLimit){
            value = re_evaluate(b,sideMax,step,-side,dataBefore->score);

            if (type == Max) {
                if (value <= superiorLimit) {
                    if(value == superiorLimit){
                        if( superiorLimit > 0 && layer - 1 > *pCount_step){
                            *pCount_step = layer - 1;
                        }else if (superiorLimit < 0 && layer - 1 <*pCount_step){
                            *pCount_step = layer - 1;
                        }
                    } else {
                        *(pSuperiorLimit) = value;
                        *pCount_step = layer - 1;
                    }
                }
            } else {
                if (value >= superiorLimit) {
                    if(value == superiorLimit){
                        if(superiorLimit > 0 && layer - 1 <*pCount_step){
                            *pCount_step = layer - 1;
                        }else if(superiorLimit < 0 && layer - 1 > *pCount_step){
                            *pCount_step = layer - 1;
                        }
                    }else{
                        *(pSuperiorLimit) = value;
                        *pCount_step = layer - 1;
                    }
                }
            }

            if(HashMatch(hashTable,*hashKey) && hashTableExtractValue(hashTable,*hashKey)!=value){
                count_conflict[layer-1]++;
            }
            hashTableStoreScore(hashTable, (Hash_value) {*hashKey, value},layerLimit - layer + 1,layer - 1);

            changePiece(b,step,Empty);
            changeHash(hashKey, randomSet, step, -side);
            return *step;
        }

        //首先尝试从Zobrist置换表中寻找可能的重复局面，若找到则直接带入值，判断是否修改上层值。
        start_t[1] = clock();
        if(HashMatch(hashTable,*hashKey)){
            Hash_value *p = hashTableGetAddress(hashTable,*hashKey);
            if(p->depth == layerLimit-layer+1) {
                if (p->isSearchFinished) {
                    value = p->value;
                    if (type == Max) {
                        if (value <= superiorLimit) {
                            if(value == superiorLimit){
                                if( superiorLimit > 0 && p->count_step > *pCount_step){
                                    *pCount_step = p->count_step;
                                }else if (superiorLimit < 0 && p->count_step <*pCount_step){
                                    *pCount_step = p->count_step;
                                }
                            } else {
                                *(pSuperiorLimit) = value;
                                *pCount_step = p->count_step;
                            }
                        }
                    } else {
                        if (value >= superiorLimit) {
                            if(value == superiorLimit){
                                if(superiorLimit > 0 && p->count_step <*pCount_step){
                                    *pCount_step = p->count_step;
                                }else if(superiorLimit < 0 && p->count_step > *pCount_step){
                                    *pCount_step = p->count_step;
                                }
                            }else{
                                *(pSuperiorLimit) = value;
                                *pCount_step = p->count_step;
                            }
                        }
                    }

                    changePiece(b, step, Empty);
                    changeHash(hashKey, randomSet, step, -side);
                    return *step;
                } else {
                    unfinished = p;
                    value = p->value;
                    if (type == Max) {
                        if (value > superiorLimit) {
                            changeHash(hashKey, randomSet, step, -side);
                            changePiece(b, step, Empty);
                            if (layer == 2) {
                                printf("V(%d,%d)=%f\n", step->x, step->y, value);
                            }
                            return *step;//返回任意值，目的为提前结束该节点。因为首个节点为Max,可能返回INFINITY时对应的步作为resultStep。
                        }
                    } else {
                        if (value < superiorLimit) {
                            changeHash(hashKey, randomSet, step, -side);
                            changePiece(b, step, Empty);
                            if (layer == 2) {
                                printf("V(%d,%d)=%f\n", step->x, step->y, value);
                            }
                            return *step;
                        }
                    }
                }
                end_t[1] = clock();
                total[1] += end_t[1] - start_t[1];
                count_match++;
            }
        }

        end_t[1] = clock();
        total[1] += end_t[1] - start_t[1];
        count_nodes ++;

        value = isStepTerminate(b, step, sideMax, -side);//对上层指定的位置进行评估，判断上层类型棋子所下位置是否终结对局。
        if (value) {

            if (type == Max) {
                if (value <= superiorLimit) {
                    if(value == superiorLimit){
                        if( superiorLimit > 0 && layer - 1 > *pCount_step){
                            *pCount_step = layer - 1;
                        }else if (superiorLimit < 0 && layer - 1 <*pCount_step){
                            *pCount_step = layer - 1;
                        }
                    } else {
                        *(pSuperiorLimit) = value;
                        *pCount_step = layer - 1;
                    }
                }
            } else {
                if (value >= superiorLimit) {
                    if(value == superiorLimit){
                        if(superiorLimit > 0 && layer - 1 <*pCount_step){
                            *pCount_step == layer - 1;
                        }else if(superiorLimit < 0 && layer - 1 > *pCount_step){
                            *pCount_step == layer - 1;
                        }
                    }else{
                        *(pSuperiorLimit) = value;
                        *pCount_step = layer - 1;
                    }
                }
            }

            if(HashMatch(hashTable,*hashKey) && hashTableExtractValue(hashTable,*hashKey)!=value){
                count_conflict[layer-1]++;
            }
            hashTableStoreScore(hashTable, (Hash_value) {*hashKey, value},layerLimit-layer+1,layer-1);

            changePiece(b,step,Empty);
            changeHash(hashKey, randomSet, step, -side);
            return *step;
        }

    }

    start_t[2] = clock();
    count_gen[layer - 1] += 1;

    newData data;

    if(dataBefore){
        data.score = re_evaluate(b,sideMax,step,-side,dataBefore->score);
    } else{
        data.score = evaluate(b,sideMax);
    }

    //确定搜索范围
    Point *empty[225] = {NULL};
    Point *data_empty = NULL;
    if(layer == 1) {
        find_influenced_empty(b,empty,&data_empty);
    }else{
        re_find_influenced_empty(b,step,empty,&data_empty,dataBefore->influenced_empty_old);
    }
    data.influenced_empty_old = empty;

    //着点生成与排序
    Stack *search_list=NULL;
    GenData result = {NULL, {NULL}};
    data.old_sequence = &result;
    if(layer == 1) {
        search_list = generate_new(b,side,&result,empty);
    }else{
        search_list = regenerate_new(b,empty,side,step,&result,dataBefore->old_sequence);
    }

    end_t[2] = clock();
    total[2] += end_t[2] - start_t[2];

    //遍历子节点
    float limit = type == Max ? -INFINITY : INFINITY;//遍历所有子节点后，limit的值为节点所下步的最终值。
    int count_step = 0;
    Point resultStep = {7,7};//仅有第一层需要用于返回最优下一步。
    while(search_list->count){
        Point nextStep = stack_pop(search_list);
        if(unfinished) {
            if (unfinished->nextPoint.x != nextStep.x || unfinished->nextPoint.y != nextStep.y) {
                continue;
            } else{
                limit = unfinished->value;
                count_step = unfinished->count_step;
            }
        }
        float former_limit = limit;//仅用于第一层判断limit是否被下层改变，若改变则同步更改resultStep。
        int former_count_step = count_step;

        //temp_step在2层以上不会被实际使用，在2层最终会参与选出最优步返回给第1层。
        traverse_new(b, sideMax, type == Max ? Min : Max, &nextStep, &count_step, &limit, layer + 1,
                     layerLimit, randomSet, hashKey, hashTable, &data);//不断确定当前层的值limit

        //对2层以上 alpha-beta剪枝 或 修改上层值limit 第二层 返回最优Step结果记录
        if (layer >= 2) {
            if (type == Max) {
                if (limit > superiorLimit) {
                    hashTableStoreUnfinished(hashTable,*hashKey,limit,nextStep,layerLimit-layer+1,count_step);
                    changeHash(hashKey, randomSet, step, -side);
                    changePiece(b, step, Empty);
                    delete_stack(search_list);
                    free(result.data);
                    free(data_empty);
                    if(layer == 2){
                        printf("V(%d,%d)=%f\n", step->x, step->y, limit);
                    }
                    return *step;//返回任意值，目的为提前结束该节点。因为首个节点为Max,可能返回INFINITY时对应的步作为resultStep。
                }
            } else {
                if (limit < superiorLimit) {
                    hashTableStoreUnfinished(hashTable,*hashKey,limit,nextStep,layerLimit-layer+1,count_step);
                    changeHash(hashKey, randomSet, step, -side);
                    changePiece(b, step, Empty);
                    delete_stack(search_list);
                    free(result.data);
                    free(data_empty);
                    if(layer == 2){
                        printf("V(%d,%d)=%f\n", step->x, step->y, limit);
                    }
                    return *step;
                }
            }
        }

        if (layer == 1){
            if(limit != former_limit) {
                printf("better limit:%f ", limit);
                resultStep = nextStep;
                printf("Changed Result to (%d,%d)\n", resultStep.x, resultStep.y);
            } else if(former_count_step != count_step){
                printf("better count_step:%d\n", count_step);
                resultStep = nextStep;
                printf("Changed Result to (%d,%d)\n", resultStep.x, resultStep.y);
            }
        }

    }

    delete_stack(search_list);
    free(result.data);
    free(data_empty);

    //对于完成全部可能搜索，搜索子节点完成过程中本节点未从上节点剪枝的情况，还原棋盘，结束。更新上层limit的值为本层值。
    if(layer >= 2){
        if(layer == 2){
            printf("V(%d,%d)=%f\n", step->x, step->y, limit);
        }
        if (type == Max) {
            if(limit == superiorLimit){
                if( superiorLimit > 0 && layer - 1 > *pCount_step){
                    *pCount_step = count_step;
                }else if (superiorLimit < 0 && layer - 1 <*pCount_step){
                    *pCount_step = count_step;
                }
            } else {
                *(pSuperiorLimit) = limit;
                *pCount_step = count_step;
            }
        } else {
            if(limit == superiorLimit){
                if(superiorLimit > 0 && layer - 1 <*pCount_step){
                    *pCount_step = count_step;
                }else if(superiorLimit < 0 && layer - 1 > *pCount_step){
                    *pCount_step = count_step;
                }
            }else{
                *(pSuperiorLimit) = limit;
                *pCount_step = count_step;
            }
        }
        if(HashMatch(hashTable,*hashKey) && hashTableExtractValue(hashTable,*hashKey)!=limit){
            count_conflict[layer-1]++;
        }
        hashTableStoreScore(hashTable, (Hash_value) {*hashKey, limit},layerLimit-layer+1,count_step);

        changePiece(b,step,Empty);
        changeHash(hashKey, randomSet, step, -side);
        return *step;
    }

    if(layer == 1){
        if(pSuperiorLimit){//如果提供了值地址，则返回最优位置对应值
            *pSuperiorLimit = limit;
        }
        return resultStep;
    }

}

void binary_print(unsigned long long num){
    unsigned long long mask = 0x8000000000000000;
    for( ; mask; mask>>=1){
        printf("%d",num & mask?1:0);
    }
}
//梅森旋转算法 32bit -> 64bit 测试
//int main(){
//    unsigned long long randomSet[15][15][2] = {0};
//    randomFill(randomSet);
//    for(int i = 0; i < 15; i++){
//        for(int j =0;j<15;j++){
//            printf("%lld ",randomSet[i][j][0]);
//            printf("%lld\n",randomSet[i][j][1]);
//        }
//    }
//    unsigned long long hashKey = 0;
//    Point a = {5,5};
//    changeHash(&hashKey,randomSet,&a,Black);
//
//    printf("%lld",hashKey);
//    return 0;
//}

//部分功能测试
//int main(){
//    int b[15][15] = {
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//
//    };
//
//    printf("begin\n");
//    for(int i =0;i<100000;i++) {
//        Point *influenced_empty[225] = {NULL};
//        Point *data = NULL;
//        find_influenced_empty(b, influenced_empty, &data);
//
//        Stack *s;
//        GenData result = {NULL, {NULL}};
//        s = generate_new(b, White, &result, influenced_empty);
//
//        Point step = {6, 6};
//        changePiece(b, &step, Black);
//
//        Point *influenced_empty_2[225] = {NULL};
//        Point *data_2 = NULL;
//        re_find_influenced_empty(b, &step, influenced_empty_2, &data_2, influenced_empty);
//
//        GenData result_2 = {NULL, {NULL}};
//        Stack *s_2;
//        s_2 = regenerate_new(b, influenced_empty_2, Black, &step, &result_2, &result);
//
//        free(data);
//        free(data_2);
//        free(result.data);
//        free(result_2.data);
//        delete_stack(s);
//        delete_stack(s_2);
//    }
//    printf("finished\n");
//
////对新空位计算与空位局部更新的测试
////    Point *empty[225] = {NULL};
////    Point *data = NULL;
////    find_influenced_empty(b, empty, data);
////    int count = 0;
////    for(int i =0;i<225;i++){
////        if(empty[i]){
////            count++;
////            b[empty[i]->y][empty[i]->x] = 3;
////            printf("%d:(%d,%d)\n",count,empty[i]->x,empty[i]->y);
////        }
////    }
////    for(int i =0 ; i<15; i++){
////        for(int j =0; j<15;j++){
////            if(b[i][j]!=0) {
////                printf("%d ", b[i][j]);
////            }else{
////                printf("  ");
////            }
////        }
////        printf("\n");
////    }
////
////    for(int i =0;i<225;i++){
////        if(empty[i]){
////            b[empty[i]->y][empty[i]->x] = 0;
////        }
////    }
////
////    Point new = {6,6};
////    changePiece(b,&new,Black);
////
////    Point *empty2[225] = {NULL};
////    Point *data2 = NULL;
////    re_find_influenced_empty(b,&new,empty2,data2,empty);
////
////    count = 0;
////    for(int i =0;i<225;i++){
////        if(empty2[i]){
////            count++;
////            b[empty2[i]->y][empty2[i]->x] = 3;
////            printf("%d:(%d,%d)\n",count,empty2[i]->x,empty2[i]->y);
////        }
////    }
////
////    count = 0;
////    for(int i =0 ; i<15; i++){
////        for(int j =0; j<15;j++){
////            if(b[i][j]!=0) {
////                count++;
////                printf("%d ", b[i][j]);
////            }else{
////                printf("  ");
////            }
////        }
////        printf("\n");
////    }
////    printf("%d",count);
////
////    free(data);
//
//
////    Range range = limit(b);
////
////    Point_Value *result[15*15]={NULL};
////    Stack *s = generate(b,range,Black,result);
////
////    while(s->count){
////        Point temp = stack_pop(s);
////        printf("(%d,%d) ",temp.x,temp.y);
////    }
//
////    Stack *stack = create_stack(1000*1000);
////    delete_stack(stack);
////    HashTable* hashTable =  hashTableInit(1000);
////    hashTableDelete(hashTable);
////
////    Point p1 = {8,2};
////    float r1 = evaluate_point(b,&p1,Black);
////    Point p2 = {5,9};
////    float r2 = evaluate_point(b,&p2,Black);
////    printf("%f,%f",r1,r2);
//
////    Range range = limit(b);
////    Point_Value **result[225] = {NULL};
////    Stack *stack = generate(b,range,Black,result);
////    while(stack->count){
////        Point temp = stack_pop(stack);
////        printf("(%d,%d)",temp.x,temp.y);
////    }
////
////    Stack *s2 = regenerate(b,)
//    return 0;
//}