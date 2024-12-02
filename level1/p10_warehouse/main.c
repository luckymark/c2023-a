#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
typedef struct {
    char name[80];
    int num;
}store;
store commodity[4000];
int sum=0;
HANDLE out;
void store_explanation(){
    out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(out, (COORD) {35,3} );
    printf("Inventory Sysmtem");
    SetConsoleCursorPosition(out, (COORD) {30,4} );
    printf("Press '1' to look up the inventory");
    SetConsoleCursorPosition(out, (COORD) {30,5} );
    printf("Press '2' to add goods to the inventory");
    SetConsoleCursorPosition(out, (COORD) {30,6} );
    printf("Press '3' to take out something from the inventory");
    SetConsoleCursorPosition(out, (COORD) {0,0});
}
void store_read(){
    FILE *fp=NULL;
    fp=fopen("C:\\Users\\scanffer\\CLionProjects\\c2023-a\\level1\\p10_warehouse\\仓库信息.txt","r");
    sum=1;
    int flag=1;
    while(flag){
        flag=fscanf(fp,"Name:%s Amount:%d\n",commodity[sum++].name,&commodity[sum].num);
    }
    sum-=2;
    fclose(fp);
    return ;
}
void store_print(){
    store_read();
    system("cls");
    store_explanation();
    for(int i=1;i<=sum;i++){
        printf("Name:%s Amount:%d\n",commodity[i].name,commodity[i].num);
    }
}
void store_upload(){
    FILE *fp=fopen("C:\\Users\\scanffer\\CLionProjects\\c2023-a\\level1\\p10_warehouse\\仓库信息.txt","w");
    for(int i=1;i<=sum;i++){
        fprintf(fp,"Name:%s Amount:%d\n",commodity[i].name,commodity[i].num);
    }
    fprintf(fp,"*\n");
    fclose(fp);
}
char addcom[80],addnum;
void store_add(){
    SetConsoleCursorPosition(out, (COORD) {30,8} );
    printf("complete the list following");
    SetConsoleCursorPosition(out, (COORD) {30,9} );
    printf("Name:");
    SetConsoleCursorPosition(out, (COORD) {30,10} );
    printf("Amount:");
    SetConsoleCursorPosition(out, (COORD) {35,9} );
    scanf("%s",addcom);
    SetConsoleCursorPosition(out, (COORD) {37,10} );
    scanf("%d",&addnum);
    SetConsoleCursorPosition(out, (COORD) {0,0});
    int flag=0;
    for(int i=1;i<=sum;i++){
        if(!strcmp(addcom,commodity[i].name) ){
            flag=1;
            commodity[i].num+=addnum;
        }
    }
    if(!flag){
        sum++;
        strcpy(commodity[sum].name,addcom);
        commodity[sum].num=addnum;
    }
    store_upload();
}
void store_out(){
    SetConsoleCursorPosition(out, (COORD) {30,8} );
    printf("complete the list following");
    SetConsoleCursorPosition(out, (COORD) {30,9} );
    printf("Name:");
    SetConsoleCursorPosition(out, (COORD) {30,10} );
    printf("Amount:");
    SetConsoleCursorPosition(out, (COORD) {35,9} );
    scanf("%s",addcom);
    SetConsoleCursorPosition(out, (COORD) {37,10} );
    scanf("%d",&addnum);
    SetConsoleCursorPosition(out, (COORD) {0,0});
    int flag=0;
    for(int i=1;i<=sum;i++){
        if(!strcmp(addcom,commodity[i].name) ){
            flag=1;
            if(commodity[i].num>=addnum){
                commodity[i].num-=addnum;
                if(commodity[i].num==0)sum--;
            }else{
                SetConsoleCursorPosition(out, (COORD) {30,11} );
                printf("We don't have enough commodity");
                SetConsoleCursorPosition(out, (COORD) {0,0} );
            }
        }
    }
    if(!flag){
        SetConsoleCursorPosition(out, (COORD) {30,11} );
        printf("We don't have the commodity you needed");
        SetConsoleCursorPosition(out, (COORD) {0,0} );
    }
    store_upload();
}
void store_control(){
    store_explanation();
    while(1){
        int key=getch();
        if(key==49){
            store_print();
        }
        if(key==50){
            store_add();
        }
        if(key==51){
            store_out();
        }
        if(key==13)return;
    }
}
int main(){
    store_control();
}
