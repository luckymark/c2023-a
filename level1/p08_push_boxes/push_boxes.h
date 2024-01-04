//
// Created by ycm on 2023/10/9.
//

#ifndef C2023_CHALLENGE_PUSH_BOXES_H
#define C2023_CHALLENGE_PUSH_BOXES_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

#define PLAYER 0
#define PATH 1
#define EMPTY 2
#define WALL 3
#define BOX 4
#define GOAL 5
#define FILL 6

#define PLAYER_C '*'
#define PATH_C ' '
#define EMPTY_C ' '
#define WALL_C '/'
#define BOX_C '#'
#define GOAL_C 'O'
#define FILL_C '$'

typedef struct{
    unsigned x;
    unsigned y;
}Place;

char** init_map(char* filename);
void draw_map(char** map/*, Place size*/);
char move(char** map, /*Place,*/ Place, unsigned * score);
char** read_map(char* filename);
Place read_size(char* filename);
void destroy_map(char** map);

typedef struct {
    char* name;
    unsigned *score;
}NameScore;
void write_score(char* filename, NameScore*);
NameScore* read_score(char* filename, unsigned length);


#endif //C2023_CHALLENGE_PUSH_BOXES_H
