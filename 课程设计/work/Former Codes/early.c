#include "../defination.h"

Point traverse_old(int (*b)[15], enum piece sideMax, enum type type, Point *step, float *pSuperiorLimit, int layer, int layerLimit) {//layer 为上层层数
    enum piece side = type == Max ? sideMax : -sideMax;//根据当前层的类型,确定相应棋子类型。
    float superiorLimit;//复制指针的值，指针仅用于修改上层的最终值。
    //!可否不创建变量，直接使用指针并兼容第一层？
    //!:默认搜索2层以上，不含2层。

    if(layer  >= 2) {
        superiorLimit = *(pSuperiorLimit);
        changePiece(b, step, -side);//在上层指定的位置下入上一层的棋子-side。所有layer>=2的层return前必定先还原所下步。

        float value = isStepTerminate(b, step, sideMax, -side);//对上层指定的位置进行评估，判断上层类型棋子所下位置是否终结对局。
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

    //printf("%d,%d,%d,%d",range.Xmin,range.Xmax,range.Ymin,range.Ymax);
    float limit = type == Max ? -INFINITY : INFINITY;//遍历所有子节点后，limit的值为节点所下步的最终值。
    Point resultStep = {7,7};//仅有第一层需要用于返回最优下一步。
    //遍历子节点
    for (int i = range.Xmin; i <= range.Xmax; i++) {
        for (int j = range.Ymin; j <= range.Ymax; j++) {
            if (*(b[j] + i) == Empty) {
                float former_limit = limit;//仅用于第一层判断limit是否被下层改变，若改变则同步更改resultStep。
                Point nextStep = {i, j};

                //temp_step在2层以上不会被实际使用，在2层最终会参与选出最优步返回给第1层。
                Point temp_step = traverse_old(b, sideMax, type == Max ? Min : Max, &nextStep, &limit,layer+1,layerLimit);//不断确定当前层的值limit

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

                if(layer == 1) {
                    printf("V(%d,%d)=%f\n", i,j,limit);
                }
                if(layer == 1 && limit != former_limit){
                    printf("limit:%f ",limit);
                    printf("former_limit:%f\n",former_limit);
                    resultStep = temp_step;
                    printf("Changed Result to (%d,%d)\n",resultStep.x,resultStep.y);
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
Point traverse_01(int (*b)[15], enum piece sideMax, enum type type, Point *step, float *pSuperiorLimit, int layer, int layerLimit) {//layer 为上层层数
    enum piece side = type == Max ? sideMax : -sideMax;//根据当前层的类型,确定相应棋子类型。
    float superiorLimit;//复制指针的值，指针仅用于修改上层的最终值。
    //!可否不创建变量，直接使用指针并兼容第一层？
    //!:默认搜索2层以上，不含2层。

    if(layer  >= 2) {
        superiorLimit = *(pSuperiorLimit);
        changePiece(b, step, -side);//在上层指定的位置下入上一层的棋子-side。所有layer>=2的层return前必定先还原所下步。

        float value = isStepTerminate(b, step, sideMax, -side);//对上层指定的位置进行评估，判断上层类型棋子所下位置是否终结对局。
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

    //printf("%d,%d,%d,%d",range.Xmin,range.Xmax,range.Ymin,range.Ymax);
    float limit = type == Max ? -INFINITY : INFINITY;//遍历所有子节点后，limit的值为节点所下步的最终值。
    Point resultStep = {7,7};//仅有第一层需要用于返回最优下一步。
    //遍历子节点
    for (int i = range.Xmin; i <= range.Xmax; i++) {
        for (int j = range.Ymin; j <= range.Ymax; j++) {
            if (*(b[j] + i) == Empty) {
                float former_limit = limit;//仅用于第一层判断limit是否被下层改变，若改变则同步更改resultStep。
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

                if(layer == 1) {
                    printf("V(%d,%d)=%f\n", i,j,limit);
                }
                if(layer == 1 && limit != former_limit){
                    printf("limit:%f ",limit);
                    printf("former_limit:%f\n",former_limit);
                    resultStep = temp_step;
                    printf("Changed Result to (%d,%d)\n",resultStep.x,resultStep.y);
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
Point traverse_02(int (*b)[15], enum piece sideMax, enum type type, Point *step, float *pSuperiorLimit, int layer, int layerLimit) {//layer 为上层层数
    enum piece side = type == Max ? sideMax : -sideMax;//根据当前层的类型,确定相应棋子类型。
    float superiorLimit;//复制指针的值，指针仅用于修改上层的最终值。
    //!可否不创建变量，直接使用指针并兼容第一层？
    //!:默认搜索2层以上，不含2层。

    if(layer  >= 2) {
        superiorLimit = *(pSuperiorLimit);
        changePiece(b, step, -side);//在上层指定的位置下入上一层的棋子-side。所有layer>=2的层return前必定先还原所下步。

        float value = isStepTerminate(b, step, sideMax, -side);//对上层指定的位置进行评估，判断上层类型棋子所下位置是否终结对局。
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
    Stack *search_list = generate(b,range,side);

    float limit = type == Max ? -INFINITY : INFINITY;//遍历所有子节点后，limit的值为节点所下步的最终值。
    Point resultStep = {7,7};//仅有第一层需要用于返回最优下一步。
    //遍历子节点
    while(search_list->count){
        Point nextStep = stack_pop(search_list);
        float former_limit = limit;//仅用于第一层判断limit是否被下层改变，若改变则同步更改resultStep。

        //temp_step在2层以上不会被实际使用，在2层最终会参与选出最优步返回给第1层。
        Point temp_step = traverse(b, sideMax, type == Max ? Min : Max, &nextStep, &limit, layer + 1,
                                   layerLimit);//不断确定当前层的值limit

        //对2层以上 alpha-beta剪枝 或 修改上层值limit 第二层 返回最优Step结果记录
        if (layer >= 2) {
            if (type == Max) {
                if (limit > superiorLimit) {
                    changePiece(b, step, Empty);
                    delete_stack(search_list);
                    return *step;//返回任意值，目的为提前结束该节点。因为首个节点为Max,可能返回INFINITY时对应的步作为resultStep。
                }
            } else {
                if (limit < superiorLimit) {
                    changePiece(b, step, Empty);
                    delete_stack(search_list);
                    return *step;
                }
            }
        }

        if (layer == 1) {
            printf("V(%d,%d)=%f\n", nextStep.x, nextStep.y, limit);
        }
        if (layer == 1 && limit != former_limit) {
            printf("limit:%f ", limit);
            printf("former_limit:%f\n", former_limit);
            resultStep = temp_step;
            printf("Changed Result to (%d,%d)\n", resultStep.x, resultStep.y);
        }

    }

    delete_stack(search_list);

    //对于完成全部可能搜索，搜索子节点完成过程中本节点未从上节点剪枝的情况，还原棋盘，结束。对上层limit的值的更新已经在搜索确定本层值地的过程中同步完成。
    if(layer >= 2){
        *(pSuperiorLimit) = limit;
        changePiece(b,step,Empty);
        return *step;
    }

    if(layer == 1){
        if(pSuperiorLimit){//如果提供了值地址，则返回最优位置对应值
            *pSuperiorLimit = limit;
        }
        return resultStep;
    }

}
Point traverse3(int (*b)[15], enum piece sideMax, enum type type, Point *step, float *pSuperiorLimit, int layer, int layerLimit, unsigned long long (*randomSet)[15][2], unsigned long long *hashKey, HashTable *hashTable, Data *dataBefore) {//layer 为上层层数
    enum piece side = type == Max ? sideMax : -sideMax;//根据当前层的类型,确定相应棋子类型。
    float superiorLimit;//复制指针的值，指针仅用于修改上层的最终值。
    //!可否不创建变量，直接使用指针并兼容第一层？
    //!:默认搜索2层以上，不含2层。

    if(layer  >= 2) {
        superiorLimit = *(pSuperiorLimit);
        changePiece(b, step, -side);//在上层指定的位置下入上一层的棋子-side。所有layer>=2的层return前必定先还原所下步。
        changeHash(hashKey, randomSet, step, -side);//下入棋子后，相应地更新hashKey

        //首先尝试从Zobrist置换表中寻找可能的重复局面，若找到则直接带入值，判断是否修改上层值。
        if(HashMatch(hashTable,*hashKey)){
            float value = hashTableExtractValue(hashTable, *hashKey);
//            printf("Find Hash:%u Value:%f\n", *hashKey, value);

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
            changeHash(hashKey, randomSet, step, -side);
            return *step;
        }

        float value = isStepTerminate(b, step, sideMax, -side);//对上层指定的位置进行评估，判断上层类型棋子所下位置是否终结对局。
        if (value) {

            if (type == Max) {
                if (value < superiorLimit) {
                    *(pSuperiorLimit) = value;
                }
            } else {
                if (value > superiorLimit) {
                    *(pSuperiorLimit) = value;
                }
            }

            hashTableStore(hashTable,(Hash_value){*hashKey,value});
//            printf("Save Hash:%u Value:%f (terminated)\n",*hashKey,value);

            changePiece(b,step,Empty);
            changeHash(hashKey, randomSet, step, -side);
            return *step;
        }

        //!:考虑在上一层提前判断，避免多次判断
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

            hashTableStore(hashTable,(Hash_value){*hashKey,value});
//            printf("Save Hash:%u Value:%f (layer limit)\n",*hashKey,value);

            changePiece(b,step,Empty);
            changeHash(hashKey, randomSet, step, -side);
            return *step;
        }

    }

    Data data;
    //确定搜索范围
    Range range;
    if(layer == 1) {
        range = limit(b);
    }else{
        range = re_limit(*(dataBefore->pRange), step);
    }
    data.pRange = &range;

    //着点生成与排序

    Point_Value* result[15*15] = {NULL};
    data.result = result;
    Stack *search_list=NULL;
    if(layer == 1) {
        search_list = generate(b, range, side, result);
    }else{
        search_list = regenerate(b, dataBefore->pRange, &range, side, step, result, dataBefore->result);
    }
    //遍历子节点
    float limit = type == Max ? -INFINITY : INFINITY;//遍历所有子节点后，limit的值为节点所下步的最终值。
    Point resultStep = {7,7};//仅有第一层需要用于返回最优下一步。
    while(search_list->count){
        Point nextStep = stack_pop(search_list);
        float former_limit = limit;//仅用于第一层判断limit是否被下层改变，若改变则同步更改resultStep。

        //temp_step在2层以上不会被实际使用，在2层最终会参与选出最优步返回给第1层。
        traverse3(b, sideMax, type == Max ? Min : Max, &nextStep, &limit, layer + 1,
                  layerLimit,randomSet,hashKey,hashTable,&data);//不断确定当前层的值limit

        //对2层以上 alpha-beta剪枝 或 修改上层值limit 第二层 返回最优Step结果记录
        if (layer >= 2) {
            if (type == Max) {
                if (limit > superiorLimit) {
                    changePiece(b, step, Empty);
                    changeHash(hashKey, randomSet, step, -side);
                    delete_stack(search_list);
                    for(int i = 0;i<225;i++){
                        if(result[i])
                        {
                            free(result[i]);
                        }
                    }
                    if(layer == 2){
                        printf("V(%d,%d)=%f\n", step->x, step->y, limit);
                    }
                    return *step;//返回任意值，目的为提前结束该节点。因为首个节点为Max,可能返回INFINITY时对应的步作为resultStep。
                }
            } else {
                if (limit < superiorLimit) {
                    changePiece(b, step, Empty);
                    changeHash(hashKey, randomSet, step, -side);
                    delete_stack(search_list);
                    for(int i = 0;i<225;i++){
                        if(result[i])
                        {
                            free(result[i]);
                        }
                    }
                    if(layer == 2){
                        printf("V(%d,%d)=%f\n", step->x, step->y, limit);
                    }
                    return *step;
                }
            }
        }

        if (layer == 1 && limit != former_limit) {
            printf("limit:%f ", limit);
            printf("former_limit:%f\n", former_limit);
            resultStep = nextStep;
            printf("Changed Result to (%d,%d)\n", resultStep.x, resultStep.y);
        }

    }

    delete_stack(search_list);
    for(int i = 0;i<225;i++){
        if(result[i])
        {
            free(result[i]);
        }
    }

    if(layer == 2){
        printf("V(%d,%d)=%f\n", step->x, step->y, limit);
    }
    //对于完成全部可能搜索，搜索子节点完成过程中本节点未从上节点剪枝的情况，还原棋盘，结束。对上层limit的值的更新已经在搜索确定本层值地的过程中同步完成。
    if(layer >= 2){
        *(pSuperiorLimit) = limit;
        hashTableStore(hashTable,(Hash_value){*hashKey,limit});
//        printf("Save Hash:%u Value:%f \n",*hashKey,limit);
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