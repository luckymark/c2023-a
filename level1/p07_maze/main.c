#include <stdio.h>
#include <process.h>
#include <unistd.h>
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
int main() {
    paintMAze();
    while (1) {
        if (Map[player_x][player_y] == '@') {
            printf("You won!!!");
            return 0;
        }
        char press = getch();
        if (press == 'w' && Map[player_x - 1][player_y] != '#') {
            system("cls");
            player_x--;
            paintMAze();
        }
        if (press == 's' && Map[player_x + 1][player_y] != '#') {
            system("cls");
            player_x++;
            paintMAze();
        }
        if (press == 'a' && Map[player_x][player_y - 1] != '#') {
            system("cls");
            player_y--;
            paintMAze();
        }
        if (press == 'd' && Map[player_x][player_y + 1] != '#') {
            system("cls");
            player_y++;
            paintMAze();
        }
    }
}