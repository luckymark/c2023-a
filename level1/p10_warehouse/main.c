#include "sqlite3.h"
#include "stdio.h"

int main() {
    printf("hello world!\n");
    sqlite3 * db;
    sqlite3_open("test.db", &db);
    sqlite3_close(db);
    return 0;
}