#include <stdlib.h>
#include <stdbool.h>
#include "defination.h"
#include <time.h>

typedef struct {
    Hash_value *data;
    unsigned int num;
}HashTable;

HashTable* hashTableInit(unsigned int num_Hash_value){
    HashTable *hashTable = (HashTable*) malloc(sizeof (HashTable));
    hashTable->data = (Hash_value*)malloc(num_Hash_value*sizeof (Hash_value));
    hashTable->num = num_Hash_value;

    return hashTable;
}

bool HashMatch(HashTable *hashTable, unsigned long long hash){
    unsigned int offset = hash % hashTable->num;//Slow! Better?
    return hashTable->data[offset].hash == hash;
}

float hashTableExtractValue(HashTable *hashTable, unsigned long long hash){
    unsigned int offset = hash % hashTable->num;//Slow! Better?
    return hashTable->data[offset].value;
}

void hashTableStoreScore(HashTable *hashTable, Hash_value hash_value,int depth,int count_step){
    unsigned int offset = hash_value.hash % hashTable->num;//Slow! Better?

    hashTable->data[offset].hash = hash_value.hash;
    hashTable->data[offset].value = hash_value.value;
    hashTable->data[offset].count_step = count_step;
    hashTable->data[offset].isSearchFinished = true;
}

Hash_value* hashTableGetAddress(HashTable *hashTable, unsigned long long hash){
    unsigned int offset = hash % hashTable->num;
    return &(hashTable->data[offset]);
}

void hashTableStoreUnfinished(HashTable *hashTable, unsigned long long hash,float score, Point point,int depth, int count_step){
    unsigned int offset = hash % hashTable->num;
    hashTable->data[offset].hash = hash;
    hashTable->data[offset].value = score;
    hashTable->data[offset].count_step = count_step;
    hashTable->data[offset].nextPoint = point;
    hashTable->data[offset].isSearchFinished = false;
}

void hashTableDelete(HashTable *hashTable){
    free(hashTable->data);
    free(hashTable);
}