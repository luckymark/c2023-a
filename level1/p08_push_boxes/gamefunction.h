#ifndef C2023_CHALLENGE_GAMEFUNCTION_H
#define C2023_CHALLENGE_GAMEFUNCTION_H
typedef struct{
    int x;
    int y;
} point;

enum direction{Up,Down,Left,Right};
void playermove(char (*walls)[10],point *player,enum direction a);
void setmap(char (*walls)[10],const point *player,point target[],int targets);
int allBack(char (*walls)[10],point target[],int targets);
void gameover();
#endif //C2023_CHALLENGE_GAMEFUNCTION_H
