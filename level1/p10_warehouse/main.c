#include <windows.h>
#include <conio.h>
#include "function.h"

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