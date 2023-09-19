#include <stdio.h>
#include <process.h>
#include <conio.h>

char Map[10][10] = {
        {'#',' ','#','#','#','#','#','#','#','#'},
        {'#',' ','#',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ','#',' ',' ','#',' ',' ',' ','#'},
        {'#',' ','#',' ','#','#','#','#',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ','#',' ','#'},
        {'#',' ','#',' ','#',' ','#','#',' ','@'},
        {'#',' ','#',' ','#',' ',' ','#',' ','#'},
        {'#',' ','#',' ','#','#','#','#','#','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#','#','#','#','#','#','#','#','#','#'},};
int player_x = 0;
int player_y = 1;
void paintMAze() {
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            if (x == player_x && y == player_y) {
                printf(" p");
            } else {
                printf(" %c", Map[x][y]);
            }
        }
        printf("\n");
    }
}
void move(char direction) {
    switch (direction) {
        case 'u':
            if (Map[player_x - 1][player_y] != '#') {
                system("cls");
                player_x--;
                paintMAze();
            }
            break;
        case 'd':
            if (Map[player_x + 1][player_y] != '#') {
                system("cls");
                player_x++;
                paintMAze();
            }
            break;
        case 'r':
            if (Map[player_x][player_y - 1] != '#') {
                system("cls");
                player_y--;
                paintMAze();
            }
            break;
        case 'l':
            if (Map[player_x][player_y + 1] != '#') {
                system("cls");
                player_y++;
                paintMAze();
            }
            break;
    }
}
int is_win() {
    if(Map[player_x][player_y] == '@') {
        return 1;
    } else {
        return 0;
    }
}
int main() {
    paintMAze();
    while (1) {
        if (is_win()) {
            printf("You won!!!");
            return 0;
        }
        char press = getch();
        switch (press) {
            case 'w':
                move('u');
                break;
            case 's':
                move('d');
                break;
            case 'a':
                move('r');
                break;
            case 'd':
                move('l');
                break;
        }

    }
}