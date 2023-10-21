#include <stdio.h>
#include <windows.h>
#include "shellControl.h"
#include <conio.h>
#include <string.h>

typedef struct {
    char category[32];
    char model[32];
    char quantity[32];
} Item;


void menu(int* choice);
void showlist();
void warehouse();
void ex_warehouse();
Item* creat_item();

int main() {
    int choice = 1;
    while(1) {
        menu(&choice);
        switch (choice) {
            case 1:
                showlist();
                break;
            case 2:
                warehouse();
                break;
            case 3:
                ex_warehouse();
                break;
            case 4:
                exit(0);
                break;
            default:
                break;
        }
        getch();
    }
}

void menu(int* choice){
    system("cls");

    gotoxy(16,0);
    printf("Warehouse Menu");//mid:16 + 14/2 = 23

    //① ② ③ ④
    gotoxy(16,1);
    printf("1. Show the list");
    gotoxy(16,2);
    printf("2. Warehouse");
    gotoxy(16,3);
    printf("3. Ex-warehouse");
    gotoxy(16,4);
    printf("4. Exit");

    int tempChoice = *choice;
    *choice = 0;

    gotoxy(15,tempChoice);
    printf(">");//▶
    while(*choice == 0){
        int input = getch();

        gotoxy(15,tempChoice);
        printf(" ");

        switch(input){
            case '1': tempChoice = 1;break;
            case '2': tempChoice = 2;break;
            case '3': tempChoice = 3;break;
            case '4': tempChoice = 4;break;
            case 13:*choice = tempChoice;break;//when \n is inputted.
            default:break;
        }
        gotoxy(15,tempChoice);
        printf(">");//▶
    }
    system("cls");

    return;
}

void showlist(){
    FILE *list = fopen("warehouse.txt","r+");

    if(list){
        int input = 0;
        while((input = fgetc(list))!=EOF){
            if( input == '#') {
                char sCategory[32] = {'\0'};
                fseek(list, -1, SEEK_CUR);
                fscanf(list, "#%[^:]:", sCategory);
                printf("%s:\n", sCategory);
                for (int input; (input = fgetc(list)) != '\n' && input != EOF;) {
                    fseek(list, -1, SEEK_CUR);
                    char sModel[32] = {'\0'};
                    char sQuantity[32] = {'\0'};
                    fscanf(list, "%[^,],%[^;];", sModel, sQuantity);
                    fseek(list, 0, SEEK_CUR);
                    printf("  %s: %s\n", sModel, sQuantity);
                }
            }
        }
    } else{
        printf("Loading Failure.");
        return;
    }

}

void warehouse(){
    FILE *list = fopen("warehouse.txt","r+");
    if(list){
        Item *in = creat_item();

        printf("Warehouse:Add Items\n");
        printf("Category:");
        scanf("%32s",in->category);
        printf("Model:");
        scanf("%32s",in->model);
        printf("Quantity:");
        scanf("%32s",in->quantity);

        char temp[32]={'\0'};
        int end = 0;
        do{
            for(int i;(i=fgetc(list))!='#';){
                if(i == EOF){
                    end = 1;
                    break;
                }
            };
            fseek(list,0,SEEK_CUR);
            fscanf(list,"%[^:]:",temp);
        }while(end == 0 && strcmp(temp,in->category)!=0);

        if(end){
            fseek(list,0,SEEK_CUR);
            fprintf(list,"\n#%s:%s,%s;",in->category,in->model,in->quantity);
        }else{
            int type = 0;
            for(int i;(i=fgetc(list))!='\n';){
                if(i == EOF){
                    type = 1;
                    break;
                }
            }
            fseek(list,-2,SEEK_CUR);
            if(type){
                fprintf(list,";%s,%s;",in->model,in->quantity);
            }else{
                fprintf(list,"%s,%s;\n",in->model,in->quantity);
            }
        }
        fclose(list);
        printf("Added %s %s to the category %s",in->quantity,in->model,in->category);
    }else{
        printf("Loading Failure.");
        return;
    }

}
void ex_warehouse(){
    system("cls");
    printf("warehouse");
}

Item* creat_item() {
    Item *item = (Item *) malloc(sizeof(Item));

    for (int i = 0; i < 32; i++) {
        item->category[i] = '\0';
        item->model[i] = '\0';
        item->quantity[i] = '\0';
    }

    return item;
}