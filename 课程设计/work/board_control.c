#include "defination.h"

void changePiece(int (*b)[15], Point *point, enum piece piece) {
    *(b[point->y] + point->x) = piece;
}