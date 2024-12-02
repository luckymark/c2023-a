#ifndef GOBANG_GENERATE_H
#define GOBANG_GENERATE_H
#include <minmax.h>
#include <stdbool.h>
#include "defination.h"
#include "stack_point.h"
#include "hash_table.h"

Range limit(int (*b)[15]);
Range re_limit(Range range,Point *step);
Stack* generate(int (*b)[15], Range range, enum piece side,enum piece sideMax,GenData *result,HashTable *hashTable,unsigned long long (*randomSet)[15][2],unsigned long long *hashKey,int depthRequired);
Stack* generate_old(int (*b)[15], Range range,enum piece side);
Stack* regenerate(int (*b)[15], Range *pRangeBefore, Range *range, enum piece side, Point *step, GenData *result, GenData *GenDataBefore,HashTable *hashTable,unsigned long long (*randomSet)[15][2],unsigned long long *hashKey,int depthRequired);
void find_nearby_empty(int (*b)[15],Point step,Point **empty,Point **pData);
void find_influenced_empty(int (*b)[15], Point **influenced_empty, Point **pData_all);
void re_find_influenced_empty(int (*b)[15],Point *new_step, Point **influenced_empty, Point **pData_all,Point **influenced_empty_old);

Stack* generate_new(int (*b)[15],enum piece side, GenData *result,Point **influenced_empty);
Stack* regenerate_new(int (*b)[15],Point **influenced_empty, enum piece side, Point *step, GenData *result, GenData *GenDataBefore);
#endif //GOBANG_GENERATE_H