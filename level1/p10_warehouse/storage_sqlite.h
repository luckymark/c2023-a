//
// Created by ycm on 2023/9/26.
//
#include "sqlite3.h"
#include "goods.h"
#include "stdbool.h"
#include "string.h"

#include "stdio.h"//错误信息输出

#ifndef C2023_CHALLENGE_STORAGE_SQLITE_H
#define C2023_CHALLENGE_STORAGE_SQLITE_H
#define FILE_NAME "goods.db"


bool init_db();
bool sql_insert(Goods**, int);
bool sql_update(Goods**, int);
Goods** sql_select(char*, char*);
bool sql_delete(char*, char*);

#endif //C2023_CHALLENGE_STORAGE_SQLITE_H
