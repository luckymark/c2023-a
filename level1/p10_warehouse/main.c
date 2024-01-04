#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
//1显示存货列表，2入库，3出库，0退出程序
bool flag=true,dflag=false;
void print(FILE *f){
    char arr[300];
    while(1){
        fgets(arr,30,f);
        if(arr[0]=='\0'){
            break;
        }
        printf("%s",arr);
    }
}
void write(FILE *f,char arr[]){
    fputs(arr,f);
    fputc('\n',f);
}
void delete(FILE *pf,FILE *ff,char str2[]){
    char str1[100];
    int temp;
    while(1){
        fgets(str1,30,pf);
        if(str1[0]=='\0') break;
        temp=strcmp(str1,str2);
        if(temp != 0){
            fputs(str1,ff);
        }
    }
}
int main() {
    FILE *fp1,*fp2;
    int ctr;
    char tmp[300];
    fp1=fopen("list.txt", "a+");
    fp2=fopen("tp","w");
    while(flag){
        scanf("%d",&ctr);
        switch(ctr){
            case 1:{
                print(fp1);
                break;
            }
            case 2:{
                gets(tmp);
                write(fp1, tmp);
                break;
                //fflush(fp1);
            }
            case 3:{
                gets(tmp);
                delete(fp1,fp2,tmp);
                dflag=true;
                break;
                //fflush(fp1);
            }
            case 0:{
                flag=false;
                break;
            }
            default:{
                break;
            }
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(dflag){
        remove("list.txt");
        rename("tp","list.txt");
    }
    system("pause");
    return 0;
}