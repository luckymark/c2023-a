//
// Created by ycm on 2023/9/26.
//
#include "storage_sqlite.h"

sqlite3* pdb = NULL;
static bool is_open = false;
const char SQL_CREATE_DB[] = "CREATE TABLE IF NOT EXISTS goods(type TEXT UNIQUE NOT NULL, FILE_NAME TEXT, price REAL CHECK (price>=0) DEFAULT 0, amount INTEGER CHECK (amount>=0) DEFAULT 0, note TEXT DEFAULT \"\");";
const char SQL_INSERT_GOODS[] = "INSERT INTO goods(type, FILE_NAME, price, amount, note) VALUES(?, ?, ?, ?, ?);";
const char SQL_UPDATE_GOODS[] = "UPDATE goods SET FILE_NAME=?, price=?, amount=?, note=? WHERE type=?;";
const char SQL_SELECT_GOODS[] = "SELECT type, FILE_NAME, price, amount, CASE WHEN note IS NULL THEN \"(null)\" ELSE note END AS note  FROM goods WHERE type=? OR FILE_NAME=? ORDER BY type ASC;";
const char SQL_PRESELECT_GOODS[] = "SELECT COUNT(*) FROM goods WHERE type=? OR FILE_NAME=?;";
const char SQL_SELECT_ALL[] = "SELECT type, FILE_NAME, price, amount, CASE WHEN note IS NULL THEN \"(null)\" ELSE note END AS note  FROM goods;";
const char SQL_PRESELECT_ALL[] = "SELECT COUNT(*) FROM goods;";
const char SQL_DELETE_GOODS[] = "DELETE FROM goods WHERE type=? OR FILE_NAME=?;";
sqlite3_stmt *STMT_CREATE_DB = NULL;
sqlite3_stmt *STMT_INSERT_GOODS = NULL;
sqlite3_stmt *STMT_UPDATE_GOODS = NULL;
sqlite3_stmt *STMT_SELECT_GOODS = NULL;
sqlite3_stmt *STMT_PRESELECT_GOODS = NULL;
sqlite3_stmt *STMT_SELECT_ALL = NULL;
sqlite3_stmt *STMT_PRESELECT_ALL = NULL;
sqlite3_stmt *STMT_DELETE_GOODS = NULL;


bool init_db() {
    int ret = sqlite3_open(FILE_NAME, &pdb);
    if (ret != SQLITE_OK) { is_open = false;
        fprintf(stderr, "ERROR: cannot open '%s' with error message '%s'\n",FILE_NAME,sqlite3_errmsg(pdb));
        return false; }
    else is_open = true;
    ret = sqlite3_prepare_v2(pdb, SQL_CREATE_DB, -1, &STMT_CREATE_DB, NULL);
    if(sqlite3_step(STMT_CREATE_DB)!=SQLITE_DONE){fprintf(stderr, "ERROR: cannot create table 'goods' with error message '%s'\n", sqlite3_errmsg(pdb));
        return false;}
    ret += sqlite3_prepare_v2(pdb, SQL_INSERT_GOODS, -1, &STMT_INSERT_GOODS, NULL);
    ret += sqlite3_prepare_v2(pdb, SQL_UPDATE_GOODS, -1, &STMT_UPDATE_GOODS, NULL);
    ret += sqlite3_prepare_v2(pdb, SQL_DELETE_GOODS, -1, &STMT_DELETE_GOODS, NULL);
    ret += sqlite3_prepare_v2(pdb, SQL_SELECT_GOODS, -1, &STMT_SELECT_GOODS, NULL);
    ret += sqlite3_prepare_v2(pdb, SQL_PRESELECT_GOODS, -1, &STMT_PRESELECT_GOODS, NULL);
    ret += sqlite3_prepare_v2(pdb, SQL_SELECT_ALL, -1, &STMT_SELECT_ALL, NULL);
    ret += sqlite3_prepare_v2(pdb, SQL_PRESELECT_ALL, -1, &STMT_PRESELECT_ALL, NULL);

//    ret = SQLITE_OK * 6;
    if(ret!=SQLITE_OK*8){
        STMT_SELECT_GOODS = STMT_DELETE_GOODS = STMT_UPDATE_GOODS = STMT_CREATE_DB = STMT_INSERT_GOODS = NULL;
        fprintf(stderr, "ERROR: cannot prepare statement with error message '%s'\n", sqlite3_errmsg(pdb));
        return false;
    }
    return true;
}
bool sql_insert(Goods** pGoods, int n){
    if(!is_open)init_db();
    if(STMT_INSERT_GOODS==NULL)return false;
    int ret;
    bool flag = true;
    for(int i=0; i<n; i++) {
        sqlite3_reset(STMT_INSERT_GOODS);
        sqlite3_clear_bindings(STMT_INSERT_GOODS);
        sqlite3_bind_text(STMT_INSERT_GOODS, 1, pGoods[i]->type, -1, SQLITE_STATIC);//SQLITE_STATIC vs SQLITE_TRANSIENT, https://stackoverflow.com/questions/1229102/when-to-use-sqlite-transient-vs-sqlite-static
        sqlite3_bind_text(STMT_INSERT_GOODS, 2, pGoods[i]->name, -1, SQLITE_STATIC);
        sqlite3_bind_double(STMT_INSERT_GOODS, 3, pGoods[i]->price);
        sqlite3_bind_int(STMT_INSERT_GOODS, 4, (int)pGoods[i]->amount);
        sqlite3_bind_text(STMT_INSERT_GOODS, 5, pGoods[i]->note, -1, SQLITE_STATIC);
        ret = sqlite3_step(STMT_INSERT_GOODS);
        if(ret!=SQLITE_DONE){
            fprintf(stderr, "ERROR: cannot insert goods(type='%s', FILE_NAME='%s', price=%.2f, amount=%d) "
                            "with error message '%s'\n", pGoods[i]->type, pGoods[i]->name, pGoods[i]->price,
                            pGoods[i]->amount, sqlite3_errmsg(pdb));
            flag = false;}
    }
    return flag;
}
bool sql_update(Goods** pGoods, int n){
    if(!is_open)init_db();
    if(STMT_UPDATE_GOODS==NULL)return false;
    int ret;
    bool flag = true;
    for(int i=0; i<n; i++){
        sqlite3_reset(STMT_UPDATE_GOODS);
        sqlite3_clear_bindings(STMT_UPDATE_GOODS);
        sqlite3_bind_text(STMT_UPDATE_GOODS, 1, pGoods[i]->name, -1, SQLITE_STATIC);
        sqlite3_bind_double(STMT_UPDATE_GOODS, 2, pGoods[i]->price);
        sqlite3_bind_int(STMT_UPDATE_GOODS, 3, (int)pGoods[i]->amount);
        sqlite3_bind_text(STMT_UPDATE_GOODS, 4, pGoods[i]->note, -1, SQLITE_STATIC);
        sqlite3_bind_text(STMT_UPDATE_GOODS, 5, pGoods[i]->type, -1, SQLITE_STATIC);
        ret = sqlite3_step(STMT_UPDATE_GOODS);
        if(ret!=SQLITE_DONE){
            fprintf(stderr, "ERROR: cannot update goods(type='%s', FILE_NAME='%s', price=%.2f, amount=%d) "
                            "with error message '%s'\n", pGoods[i]->type, pGoods[i]->name, pGoods[i]->price,
                    pGoods[i]->amount, sqlite3_errmsg(pdb));
            flag = false;
        }
    }
    return flag;
}
Goods** sql_select(char* type, char* name){
    if(!is_open)init_db();
    if(STMT_SELECT_GOODS==NULL||STMT_PRESELECT_GOODS==NULL)return false;
    sqlite3_reset(STMT_SELECT_GOODS);
    sqlite3_reset(STMT_PRESELECT_GOODS);

    sqlite3_bind_text(STMT_PRESELECT_GOODS, 1, type, -1, SQLITE_STATIC);
    sqlite3_bind_text(STMT_PRESELECT_GOODS, 2, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(STMT_SELECT_GOODS, 1, type, -1, SQLITE_STATIC);
    sqlite3_bind_text(STMT_SELECT_GOODS, 2, name, -1, SQLITE_STATIC);

    if(sqlite3_step(STMT_PRESELECT_GOODS)!=SQLITE_ROW){
        fprintf(stderr, "ERROR: cannot select goods(type='%s', FILE_NAME='%s') "
                        "with error message '%s'\n", type, name, sqlite3_errmsg(pdb));
        return NULL;
    }

    unsigned int cols = sqlite3_column_int(STMT_PRESELECT_GOODS, 0);
    Goods **pGoods = (Goods**)malloc((cols+1)*sizeof(Goods*));
    sqlite3_reset(STMT_PRESELECT_GOODS);

    int i;
    for(i=0; i<cols; i++){
        if(sqlite3_step(STMT_SELECT_GOODS)!=SQLITE_ROW)break;
        Goods* tmp_goods = pGoods[i] = (Goods*)malloc(sizeof(Goods));
        tmp_goods->type = (char*)sqlite3_column_text(STMT_SELECT_GOODS, 0);
        tmp_goods->name = (char*) sqlite3_column_text(STMT_SELECT_GOODS, 1);
        tmp_goods->price =  sqlite3_column_double(STMT_SELECT_GOODS, 2);
        tmp_goods->amount = sqlite3_column_int(STMT_SELECT_GOODS, 3);
        tmp_goods->note = (char*)sqlite3_column_text(STMT_SELECT_GOODS, 4);
    }
    pGoods[i] = NULL;
    return pGoods;
}

Goods** sql_select_all(){
    if(!is_open)init_db();
    if(STMT_SELECT_ALL==NULL||STMT_PRESELECT_ALL==NULL)return false;
    sqlite3_reset(STMT_SELECT_ALL);
    sqlite3_reset(STMT_PRESELECT_ALL);

    if(sqlite3_step(STMT_PRESELECT_GOODS)!=SQLITE_ROW){
        fprintf(stderr, "ERROR: cannot select ALL goods with error message '%s'\n", sqlite3_errmsg(pdb));
        return NULL;
    }

    unsigned int cols = sqlite3_column_int(STMT_PRESELECT_ALL, 0);
    Goods **pGoods = (Goods**)malloc((cols+1)*sizeof(Goods*));
    sqlite3_reset(STMT_PRESELECT_ALL);

    int i;
    for(i=0; i<cols; i++){
        if(sqlite3_step(STMT_SELECT_ALL)!=SQLITE_ROW)break;
        Goods* tmp_goods = pGoods[i] = (Goods*)malloc(sizeof(Goods));
        tmp_goods->type = (char*)sqlite3_column_text(STMT_SELECT_ALL, 0);
        tmp_goods->name = (char*) sqlite3_column_text(STMT_SELECT_ALL, 1);
        tmp_goods->price =  sqlite3_column_double(STMT_SELECT_ALL, 2);
        tmp_goods->amount = sqlite3_column_int(STMT_SELECT_ALL, 3);
        tmp_goods->note = (char*)sqlite3_column_text(STMT_SELECT_ALL, 4);
    }
    pGoods[i] = NULL;
    return pGoods;
}

bool sql_delete(char* type, char* name){
    if(!is_open)init_db();
    if(STMT_DELETE_GOODS==NULL)return false;
    sqlite3_reset(STMT_DELETE_GOODS);
    sqlite3_clear_bindings(STMT_DELETE_GOODS);
    sqlite3_bind_text(STMT_DELETE_GOODS, 1, type, -1, SQLITE_STATIC);
    sqlite3_bind_text(STMT_DELETE_GOODS, 2, name, -1, SQLITE_STATIC);
    if(sqlite3_step(STMT_DELETE_GOODS)!=SQLITE_DONE){
        fprintf(stderr, "ERROR: cannot delete goods(type='%s', FILE_NAME='%s') "
                        "with error message '%s'\n", type, name, sqlite3_errmsg(pdb));
        return false;
    }else return true;
};

bool sql_close(){
    return sqlite3_close(pdb);
}