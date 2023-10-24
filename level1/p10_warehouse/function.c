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
                for (int input2; (input2 = fgetc(list)) != '.' && input2 != EOF;) {
                    fseek(list, -1, SEEK_CUR);
                    char sModel[32] = {'\0'};
                    char sQuantity[32] = {'\0'};
                    fscanf(list, "%[^,],%[^;];", sModel, sQuantity);
                    fseek(list, 0, SEEK_CUR);
                    printf("  %s: %s\n", sModel, sQuantity);
                }
            }
        }
        fclose(list);
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

        if(atoi(in->quantity)<=0){
            printf("Invalid quantity.");
            return;
        }
        //Tell whether the category to be warehoused has existed.
        char temp[32]={'\0'};
        int notExist = 0;
        do{
            for(int i;(i=fgetc(list))!='#';){
                if(i == EOF){
                    notExist = 1;
                    break;
                }
            };
            fseek(list,0,SEEK_CUR);
            fscanf(list,"%[^:]:",temp);
        }while(notExist == 0 && strcmp(temp, in->category) != 0);

        if(notExist){
            fseek(list,0,SEEK_CUR);
            fprintf(list,"\n#%s:%s,%s;.",in->category,in->model,in->quantity);
            fclose(list);
        }else{
            //Search the item and quantity,no matter existing or not.
            int destination = 0;
            char temp2[32] = {'\0'};
            char quantity[32] = {'\0'};
            do{
                int next;
                if((next = fgetc(list)) == '.'){
                    destination = ftell(list) - 2;
                    break;
                }else{
                    destination = ftell(list) - 2;
                    fseek(list,-1,SEEK_CUR);
                    fscanf(list,"%[^,],%[^;];",temp2,quantity);
                }
            }while(strcmp(temp2,in->model)!=0);

            char sNewQuantity[32] = {'\0'};
            if(strcmp(temp2,in->model)!=0){
                strcpy(sNewQuantity,in->quantity);
            }else{
                int newQuantity = atoi(quantity) + atoi(in->quantity);
                itoa(newQuantity, sNewQuantity, 10);
            }

            FILE *new = fopen("new","w+");
            if(new){
                rewind(list);
                while(ftell(list)<=destination){
                    fputc(fgetc(list),new);
                }

                fprintf(new,"%s,%s;",in->model,sNewQuantity);

                for(int i;(i=fgetc(list))!=';';){
                    if(i == '.'){
                        fseek(list,-1,SEEK_CUR);
                        break;
                    }
                };

                while(fgetc(list)!=EOF){
                    fseek(list,-1,SEEK_CUR);
                    fputc(fgetc(list),new);
                }
                fclose(list);
                fclose(new);
                remove("warehouse.txt");
                rename("new","warehouse.txt");
            }else{
                fclose(list);
                printf("Fail to creat the temporary file.");
            }

        }
        printf("Added %s:%s to %s",in->model,in->quantity,in->category);
    }else{
        printf("Loading Failure.");
        return;
    }

}
void ex_warehouse(){
    FILE *list = fopen("warehouse.txt","r+");
    if(list){
        Item *in = creat_item();

        printf("Ex-warehouse:Delete Items\n");
        printf("Category:");
        scanf("%32s",in->category);
        printf("Model:");
        scanf("%32s",in->model);
        printf("Quantity:");
        scanf("%32s",in->quantity);

        if(atoi(in->quantity)<=0){
            printf("Invalid quantity.");
            return;
        }
        char temp[32]={'\0'};
        int notExist = 0;
        int p_category;
        do{
            for(int i;(i=fgetc(list))!='#';){
                if(i == EOF){
                    notExist = 1;
                    break;
                }
            }
            fseek(list,0,SEEK_CUR);
            p_category = ftell(list);
            fscanf(list,"%[^:]:",temp);
        }while(notExist == 0 && strcmp(temp, in->category) != 0);

        if(notExist){
            printf("The category doesn't exist.");
            fclose(list);

        }else{
            int itemExist = 1;
            int destination = 0;
            char temp2[32] = {'\0'};
            char quantity[32] = {'\0'};
            do{
                int next;
                if((next = fgetc(list)) == '.'){
                    itemExist = 0;
                    break;
                }else{
                    destination = ftell(list) - 2;
                    fseek(list,-1,SEEK_CUR);
                    fscanf(list,"%[^,],%[^;];",temp2,quantity);
                }
            }while(strcmp(temp2,in->model)!=0);


            if(itemExist){
                int newQuantity = atoi(quantity) - atoi(in->quantity);

                if(newQuantity < 0){
                    fclose(list);
                    printf("No enough items for ex-warehousing.");
                    return;
                }

                char sNewQuantity[32] = {'\0'};
                itoa(newQuantity,sNewQuantity,10);

                FILE *new = fopen("new","w+");
                if(new){
                    //Write the new quantity(it maybe 0 and then not write).
                    rewind(list);
                    while(ftell(list)<=destination){
                        fputc(fgetc(list),new);
                    }
                    if(newQuantity>0) {
                        fprintf(new, "%s,%s;", in->model, sNewQuantity);
                    }
                    for(int i;(i=fgetc(list))!=';';){
                        if(i == '.'){
                            fseek(list,-1,SEEK_CUR);
                            break;
                        }
                    }
                    while(fgetc(list)!=EOF){
                        fseek(list,-1,SEEK_CUR);
                        fputc(fgetc(list),new);
                    }

                    //Delete the possible empty category.
                    fseek(new,p_category-1,SEEK_SET);
                    for(int i;(i= fgetc(new))!=':';);

                    if(fgetc(new)=='.'){
                        fclose(new);
                        FILE *new2 = fopen("new","w+");
                        if(new2) {
                            rewind(list);
                            destination = p_category - 2;
                            while (ftell(list) < destination) {
                                fputc(fgetc(list), new2);

                            }
                            for (int i; (i = fgetc(list)) != '.';);
                            while (fgetc(list) != EOF) {
                                fseek(list, -1, SEEK_CUR);
                                fputc(fgetc(list), new2);

                            }
                            fclose(new2);
                        }else{
                            printf("Fail to creat new2.");
                        }
                    }else{
                        fclose(new);
                    }
                    printf("Ex-warehoused %s:%s from %s",in->category,in->model,in->quantity);

                    fclose(list);
                    remove("warehouse.txt");
                    rename("new","warehouse.txt");
                }else{
                    printf("Fail to creat the temporary file.");
                    fclose(list);
                }
            }else{
                printf("The item doesn't exist.");
                fclose(list);
            }
        }
    }else{
        printf("Loading Failure.");
    }
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