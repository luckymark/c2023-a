#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_LENGTH 100

typedef struct Goods {
    char name[100];
    int num;
} Goods;

enum Instruction {
    Show_inventory_list = 1,
    Warehouse,
    Out_of_warehouse,
    Quit
};

typedef struct GeneralData {
    enum Instruction userInstruction;
} GeneralData;

Goods goods[MAX_DATA_LENGTH] = {};
GeneralData generalData;

void read_data();

void init_screen();

void show_menu();

void get_instruction();

bool to_quit();

void core();

void save_data();

void show_inventory_list_core();

void Warehouse_core();

void Out_of_warehouse_core();

int main() {
    read_data();
    while (true) {
        init_screen();
        show_menu();
        get_instruction();
        if (to_quit()) break;
        core();
    }
    save_data();
    return 0;
}

void save_data() {
    FILE *fp = fopen("goods.dat", "w");//读写打开或建立一个二进制文件，允许读和写。
    if (!fp) exit(1);//写文件失败
    fwrite(goods, sizeof(Goods), MAX_DATA_LENGTH, fp);
    fclose(fp);
}

void core() {
    switch (generalData.userInstruction) {
        case Show_inventory_list:
            show_inventory_list_core();
            break;
        case Warehouse:
            Warehouse_core();
            break;
        case Out_of_warehouse:
            Out_of_warehouse_core();
            break;
        case Quit:
            return;
    }
}

void Out_of_warehouse_core() {
    printf("Enter the name:");
    char name[MAX_DATA_LENGTH];
    scanf("%s", name);
    printf("Enter the num:");
    int num;
    scanf_s("%d", &num);
    int tail_index=-1;
    for (int i = 0; i < MAX_DATA_LENGTH; ++i) {
        if(strcmp(goods[i].name,name) == 0) {
            goods[i].num -= num;
            return;
        }
        if(goods[i].num) {
            tail_index = i;
        }
    }
    tail_index++;
    strcpy(goods[tail_index].name, name);
    goods[tail_index].num = num;
}

void Warehouse_core() {
    printf("Enter the name:");
    char name[MAX_DATA_LENGTH];
    scanf("%s", name);
    printf("Enter the num:");
    int num;
    scanf_s("%d", &num);
    int tail_index=-1;
    for (int i = 0; i < MAX_DATA_LENGTH; ++i) {
        if(strcmp(goods[i].name,name) == 0) {
            goods[i].num += num;
            return;
        }
        if(goods[i].num) {
            tail_index = i;
        }
    }
    tail_index++;
    strcpy(goods[tail_index].name, name);
    goods[tail_index].num = num;
}

void show_inventory_list_core() {
    init_screen();
    printf("Name\tNum\n");
    for (int i = 0; i < MAX_DATA_LENGTH; ++i) {
        if(goods[i].num) {
            printf("%s\t%d\n", goods[i].name, goods[i].num);
        }
    }
    system("pause");
}

bool to_quit() {
    return generalData.userInstruction == Quit;
}

void get_instruction() {
    scanf_s("%d", &generalData.userInstruction);
}

void show_menu() {
    char menu[] = "1. Show inventory list\n"
                  "2. Warehouse\n"
                  "3. out of warehouse\n"
                  "4. Quit"
                  "\n"
                  "\n"
                  "enter a number: ";
    printf("%s", menu);
}

void init_screen() {
    system("cls");
}

void read_data() {
    FILE *fp = fopen("goods.dat", "r");
    if (!fp) return;
    fread(goods, sizeof(Goods), 100, fp);
    fclose(fp);
}
