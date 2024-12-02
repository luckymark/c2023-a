#ifndef GOBANG_HASH_TABLE_H
#define GOBANG_HASH_TABLE_H
#include "defination.h"
#include <time.h>
typedef struct {
    Hash_value *data;
    unsigned int num;
}HashTable;

HashTable* hashTableInit(unsigned int num_Hash_value);
bool HashMatch(HashTable *hashTable, unsigned long long hash);
float hashTableExtractValue(HashTable *hashTable, unsigned long long hash);
Hash_value* hashTableGetAddress(HashTable *hashTable, unsigned long long hash);
void hashTableStoreScore(HashTable *hashTable, Hash_value hash_value,int depth,int count_step);
void hashTableStoreUnfinished(HashTable *hashTable, unsigned long long hash,float score,Point point,int depth,int count_step);
void hashTableDelete(HashTable *hashTable);

#endif //GOBANG_HASH_TABLE_H
