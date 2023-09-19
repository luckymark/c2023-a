#include <stdio.h>
#include <process.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>

char Map[10][10] = {
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#',' ','#',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ','#',' ',' ','#',' ',' ',' ','#'},
        {'#',' ','#',' ','#','#','#','#',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ','#',' ','#'},
        {'#',' ','#',' ','#',' ','#','#',' ','@'},
        {'#',' ','#',' ','#',' ',' ','#',' ','#'},
        {'#',' ','#',' ','#','#','#','#','#','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#','#','#','#','#','#','#','#','#','#'},};
int pop_size = 100;
int score[100];
int player_x;
int player_y;
const int step_amount = 100;
struct pop {
    int step[100];
};
struct score {
    int sc;
};
void reset() {
    player_y = 1;
    player_x = 1;
};
struct pop** summon(int pop_size) {
    struct pop** pop = malloc(pop_size*sizeof(struct pop*));
    for (int i = 0; i < pop_size; ++i) {
        pop[i] = malloc(sizeof(struct pop));
    }
    for (int i = 0; i < pop_size; ++i) {
        srand(rand());
        for (int j = 0; j < step_amount; ++j) {
            pop[i] -> step[j] = rand()%4 + 1;
        }
    }
    return pop;
}
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
void scoring(struct pop** pop,int n) {
    int step;
    for (int i = 0; i < n; ++i) {
        reset();
        for (int j = 0; j < step_amount; ++j) {
            step = pop[i] -> step[j];
            switch (step) {
                case 1:
                    move('u');
                    break;
                case 2:
                    move('d');
                    break;
                case 3:
                    move('r');
                    break;
                case 4:
                    move('l');
                    break;
            }
            printf("\nIndividual: %d , Attempt: %d",i+1,j+1);
            score[i] = step_amount - j - 1;
            if(is_win() == 1) {
                break;
            }
        }
    }
}
void printpop(struct pop** pop,int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < step_amount; ++j) {
            printf("%d",pop[i] -> step[j]);
        }
        printf("\n");
    }
}
int main() {
    system("pause");
    struct pop** population = summon(pop_size);
    scoring(population,pop_size);
    for (int i = 0; i < pop_size; ++i) {
        printf("%d\n",score[i]);
    }
    system("pause");
    return 0;
}