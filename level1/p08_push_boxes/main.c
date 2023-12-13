#include <stdio.h>
#include <conio.h>
#include <process.h>

int player_x = 0;
int player_y = 0;
int box_x = 0;
int box_y = 0;
char Map[10][10];
FILE * fp;
void paintMap() {
    system("cls");
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            if (x == player_x && y == player_y) {
                printf(" p");
            } else {
                if (x == box_x && y == box_y) {
                    printf("B ");
                } else {
                    printf(" %c", Map[x][y]);
                }
            }
        }
        printf("\n");
    }
}
int player_on_the_right() {
    if (player_y + 1 == box_y && player_x == box_x) {
        return 1;
    }
    return 0;
}
int player_on_the_left() {
    if (player_y - 1 == box_y && player_x == box_x) {
        return 1;
    }
    return 0;
}
int player_on_the_up() {
    if (player_y == box_y && player_x - 1 == box_x) {
        return 1;
    }
    return 0;
}
int player_on_the_down() {
    if (player_y == box_y && player_x + 1 == box_x) {
        return 1;
    }
    return 0;
}

void player_move(char direct) {
    switch (direct) {
        case 'u':
            if (Map[player_x - 1][player_y] != '#') {
                player_x--;
                paintMap();
            }
            break;
        case 'd':
            if (Map[player_x + 1][player_y] != '#') {
                player_x++;
                paintMap();
            }
            break;
        case 'r':
            if (Map[player_x][player_y + 1] != '#') {
                player_x++;
                paintMap();
            }
            break;
        case 'l':
            if (Map[player_x][player_y - 1] != '#') {
                player_x--;
                paintMap();
            }
            break;
        default:
            break;

    }
}
void box_move(char direct) {
    switch (direct) {
        case 'u':
            if (Map[player_x - 2][player_y] != '#') {
                box_x--;
                player_x--;
                paintMap();
            }
            break;
        case 'd':
            if (Map[player_x + 2][player_y] != '#') {
                box_x++;
                player_x++;
                paintMap();
            }
            break;
        case 'r':
            if (Map[player_x][player_y + 2] != '#') {
                box_x++;
                player_x++;
                paintMap();
            }
            break;
        case 'l':
            if (Map[player_x][player_y - 2] != '#') {
                box_x--;
                player_x--;
                paintMap();
            }
            break;
        default:
            break;

    }
}
void choosemap() {
    int choose = 0;
    printf("To choose the map,please enter a number(1~3): ");
    scanf("%d",&choose);
    switch (choose) {
        case 1:
            fp = fopen("1.txt","r");
            break;
        case 2:
            fp = fopen("2.txt","r");
            break;
        case 3:
            fp = fopen("3.txt","r");
            break;
        default:
            printf("ERROR: invaild choice.");
            break;

    }
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            Map[x][y] = getc(fp);

        }
    }
    player_x = getc(fp);
    player_y = getc(fp);
    box_x = getc(fp);
    box_y = getc(fp);
    fclose(fp);
    paintMap();
}
int main() {
    choosemap();
    while (1) {
        if (Map[box_x][box_y] == '$') {
            printf("You won!!!");
            return  0;
        }
        if (Map[box_x][box_y] == 'H') {
            printf("You failed!");
            return 0;
        }
        char move = getch();
        switch (move) {
            case 'w':
                if (player_on_the_up()) {
                    box_move('u');
                } else {
                    player_move('u');
                }
                break;
            case 's':
                if (player_on_the_down()) {
                    box_move('d');
                } else {
                    player_move('d');
                }
                break;
            case 'a':
                if (player_on_the_left()) {
                    box_move('l');
                } else {
                    player_move('l');
                }
                break;
            case 'd':
                if (player_on_the_right()) {
                    box_move('r');
                } else {
                    player_move('r');
                }
                break;
            default:
                break;
        }
    }
}