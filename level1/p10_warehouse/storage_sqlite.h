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

/*
sqlite3* pdb = NULL;
static bool is_open = false;
const char SQL_CREATE_DB[] = "CREATE TABLE IF NOT EXISTS goods(type TEXT UNIQUE, name TEXT, price REAL (CHECK price>=0), amount INTEGER (CHECK amount>=0), note TEXT DEFAULT \"\");";
const char SQL_INSERT_GOODS[] = "INSERT INTO goods(type, name, price, amount, note) VALUES(?, ?, ?, ?, ?);";
const char SQL_UPDATE_GOODS[] = "UPDATE goods SET name=?, price=?, amount=?, note=? WHERE type=?;";
const char SQL_SELECT_GOODS[] = "SELECT (type, name, price, amount, note) FROM goods WHERE type=? OR name=? ORDER BY type ASC;";
const char SQL_PRESELECT_GOODS[] = "SELECT COUNT(*) FROM goods WHERE type=? OR name=?;";
const char SQL_DELETE_GOODS[] = "DELETE FROM goods WHERE type=? OR　name=?;";
sqlite3_stmt *STMT_CREATE_DB = NULL;
sqlite3_stmt *STMT_INSERT_GOODS = NULL;
sqlite3_stmt *STMT_UPDATE_GOODS = NULL;
sqlite3_stmt *STMT_SELECT_GOODS = NULL;
sqlite3_stmt *STMT_PRESELECT_GOODS = NULL;
sqlite3_stmt *STMT_DELETE_GOODS = NULL;

*/

bool init_db();
bool sql_insert(Goods**, int);
bool sql_update(Goods**, int);
Goods** sql_select(char*, char*);
bool sql_delete(char*, char*);

#endif //C2023_CHALLENGE_STORAGE_SQLITE_H
