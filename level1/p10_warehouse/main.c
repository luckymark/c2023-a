#include "stdio.h"
#include "storage_sqlite.h"

int main() {
    Goods good1, good2, good3, good4;
    good1.type="ACUENCFIOE";good1.name="good1";good1.price=1.14;good1.amount=514;good1.note=NULL;
    good2.type="DHFCSIDUOH";good2.name="good2";good2.price=11.45;good2.amount=14;good2.note=NULL;
    good3.type="BBDCFHOIVI";good3.name="good3";good3.price=11;good3.amount=4514;good3.note=NULL;
    good4.type="COIUHVEWOU";good4.name="good4";good4.price=1145.14;good4.amount=0;good4.note=NULL;
    Goods* pGoods[5]={&good1,&good2,&good3,&good4, NULL};
    bool ret;
    ret = init_db();
    printf("init db: %s\n", ret?"success":"fail");
    if(!ret)return -1;
    printf("insert goods: %s\n", sql_insert(pGoods, 4)?"success":"fail");
    good1.amount=5140;
    good2.price=114.5;
    good3.note="good3 note";
    good4.name="f**k C";
    printf("update goods: %s\n", sql_update(pGoods, 4)?"success":"fail");
    Goods ** new_goods = sql_select(good3.type, NULL);
    if(new_goods!=NULL&&new_goods[0]!=NULL) {
        printf("select good1: good(type='%s', FILE_NAME='%s', price=%.2f, amount=%d, note='%s')\n", new_goods[0]->type, new_goods[0]->name, new_goods[0]->price, new_goods[0]->amount, new_goods[0]->note);
    }else printf("select good1: (null)\n");
    printf("delete goods: %s\n",  sql_delete(good1.type, NULL)?"success":"fail");
    new_goods = sql_select(good1.type, NULL);
    if(new_goods!=NULL&&new_goods[0]!=NULL) {
    printf("select good1: good(type='%s', FILE_NAME='%s')\n", new_goods[0]->type, new_goods[0]->name);}
    else printf("select good1: (null)\n");
    sql_close();
}