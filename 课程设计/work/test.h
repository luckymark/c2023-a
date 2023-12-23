#ifndef GOBANG_TEST_H
#define GOBANG_TEST_H
#include "defination.h"
#include "board_control.h"
#include "evaluate_func.h"
#include "generate.h"
#include "stack_point.h"
#include "hash_table.h"
#include "Zobrist.h"


Point traverse_old(int (*b)[15], enum piece sideMax, enum type type, Point *step, float *pSuperiorLimit, int layer, int layerLimit);
Point traverse3(int (*b)[15], enum piece sideMax, enum type type, Point *step, float *pSuperiorLimit, int layer, int layerLimit, unsigned long long (*randomSet)[15][2], unsigned long long *hashKey, HashTable *hashTable, Data *dataBefore);
Point traverse(int (*b)[15], enum piece sideMax, enum type type, Point *step, float *pSuperiorLimit, int layer, int layerLimit, unsigned long long (*randomSet)[15][2], unsigned long long *hashKey, HashTable *hashTable, Data *dataBefore);
Point traverse_new(int (*b)[15], enum piece sideMax, enum type type, Point *step, int *pCount_step, float *pSuperiorLimit, int layer, int layerLimit, unsigned long long (*randomSet)[15][2], unsigned long long *hashKey, HashTable *hashTable, newData *dataBefore);
#endif
