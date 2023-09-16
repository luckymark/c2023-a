#include <stdio.h>
#include <string.h>
struct item {
    char name[999];
    int amount;
};
int InventoryCount = 0;
struct item Inventory[999];
FILE* fp;
void Show() {
    printf("Item List:\n");
    for (int i = 0; i < InventoryCount; ++i) {
        printf("Name: %s -> Amount: %d\n",Inventory[i].name,Inventory[i].amount);
    }
}
void add() {
    struct item newItem;
    printf("Enter the name of a new item: ");
    scanf("%s", newItem.name);
    int itemcount;
    do {
        printf("Enter the amount of a new item: ");
        scanf("%d",&itemcount);
        if (itemcount <= 0) {
            printf("ERROR: Invalid amount.Please enter again.");
        }
    } while (itemcount <=0);
    newItem.amount = itemcount;
    Inventory[InventoryCount] = newItem;
    InventoryCount++;
}
void OutBound() {
    printf("Enter the name of the item you want to remove:\n");
    char name[999];
    scanf("%s",name);
    for (int i = 0; i < InventoryCount; ++i) {
        if (strcmp(Inventory[i].name , name) == 0) {
            for (int j = i; j < InventoryCount - 1; ++j) {
                Inventory[j] = Inventory[j+1];
            }
            InventoryCount--;
            return;
        }
    }
    printf("ERROR: Invalid item");
}
void Menu() {
    int choice;
    do {
        printf("1. Show the Inventory.\n");
        printf("2. Add a new item.\n");
        printf("3. Remove an item.\n");
        printf("4. Exist.\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                Show();
                break;
            case 2:
                add();
                break;
            case 3:
                OutBound();
                break;

        }
    } while (choice !=4);
    fp = fopen("Inventory.dat","w");
    fwrite(&InventoryCount , sizeof(int) , 1 , fp);
    fwrite(Inventory , sizeof(struct item) , InventoryCount , fp);
    fclose(fp);
    return;
}
int main() {
    fp = fopen("Inventory.dat", "r");
    if (fp != NULL) {
        fread(&InventoryCount, sizeof(int), 1, fp);
        fread(Inventory, sizeof(struct item), InventoryCount, fp);
        fclose(fp);
    } else {
        printf("ERROR: Failed to read the file.");
        return 1;
    }
    Menu();
    return 0;
}