#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void read_data();

void init_screen();

void show_menu();

void get_instruction();

bool to_quit();

void core();

void save_data();

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

}

void core() {

}

bool to_quit() {
    return false;
}

void get_instruction() {

}

void show_menu() {

}

void init_screen() {

}

void read_data() {

}
