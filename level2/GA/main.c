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
const int step_amount = 200;
struct pop {
    int step[200];
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
/*void paintMAze() {
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
}*/
void move(char direction) {
    switch (direction) {
        case 'u':
            if (Map[player_x - 1][player_y] != '#') {
                system("cls");
                player_x--;
            //    paintMAze();
            }
            break;
        case 'd':
            if (Map[player_x + 1][player_y] != '#') {
                system("cls");
                player_x++;
             //   paintMAze();
            }
            break;
        case 'r':
            if (Map[player_x][player_y - 1] != '#') {
                system("cls");
                player_y--;
               // paintMAze();
            }
            break;
        case 'l':
            if (Map[player_x][player_y + 1] != '#') {
                system("cls");
                player_y++;
              //  paintMAze();
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
void scoring(struct pop** pop,int n,int it) {
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
            system("cls");
            printf("Iteration: %d,Individual: %d,Attempt: %d\n",it,i,j);
            score[i] = step_amount - j;
            if(is_win() == 1) {
                break;
            }
        }
    }
}
int roulette(int input[100]) {
    int sum = 0;
    for (int i = 0; i < 100; ++i) {
        sum += input[i];
    }
    for (int i = 0; i < 100; ++i) {
        srand(rand());
        double probability = (input[i]/sum);
        if ((rand()/(RAND_MAX+1.0)) <= probability) {
            return i;
        }
        srand(rand());
        return (rand()%pop_size);
    }
}
int inroulette(int input[100]) {
    int sum = 0;
    for (int i = 0; i < 100; ++i) {
        sum += (201-input[i]);
    }
    for (int i = 0; i < 100; ++i) {
        srand(rand());
        double probability = ((201-input[i])/sum);
        if ((rand()/(RAND_MAX+1.0)) <= probability) {
            return i;
        }
        srand(rand());
        return (rand()%pop_size);
    }
}
struct pop** sift(struct pop** pop) {
    //抽取
    int gene_mark_1 = roulette(score);
    int gene_mark_2 = roulette(score);
    int *gene_1 = pop[gene_mark_1] -> step;
    int *gene_2 = pop[gene_mark_2] -> step;
    //交换
    srand(rand());
    int times = rand()%200 + 1;
    for (int i = 0; i < times; ++i) {
        srand(rand());
        int mark = rand()%200;
        int pre = gene_1[mark];
        gene_1[mark] = gene_2[mark];
        gene_2[mark] = pre;
    }
    //变异
    float mutation_pro = 0.01f;
    srand(rand());
    if ((rand()/(RAND_MAX+1.0)) <= mutation_pro) {
        srand(rand());
        int mutation_times = rand()%200 + 1;
        for (int i = 0; i < mutation_times; ++i) {
            srand(rand());
            gene_1[rand()%200] = rand()%4 +1;
            gene_2[rand()%200] = rand()%4 +1;
        }
    }
    //淘汰并继承子代
    for (int i = 0; i < 200; ++i) {
        pop[inroulette(score)] -> step[i] = gene_1[i];
    }
    for (int i = 0; i < 200; ++i) {
        pop[inroulette(score)] -> step[i] = gene_2[i];
    }
    return pop;
}
void best(int input[100],struct pop** pop) {
    int max = input[0];
    int i;
    for (i = 0; i < pop_size; ++i) {
        if(input[i]>max) {
            max=input[i];
        }
    }
    for (i = 0; i < pop_size; ++i) {
        if (input[i] == max) {
            break;
        }
    }
    printf("Optimal solution:\n");
    for (int j = 0; j < (step_amount - score[i] + 1); ++j) {
        switch (pop[i] -> step[j]) {
            case 1:
                printf("W ->");
            case 2:
                printf("S ->");
            case 3:
                printf("D ->");
            case 4:
                printf("A ->");
        }
    }
};
int main() {
    printf("Enter the iterations: ");
    int iterations;
    scanf("%d",&iterations);
    struct pop** population = summon(pop_size);
    for (int i = 0; i < iterations; ++i) {
        scoring(population,pop_size,i);
        population = sift(population);
    }
    scoring(population,pop_size,-1);
    best(score,population);
    system("pause");
    return 0;
}