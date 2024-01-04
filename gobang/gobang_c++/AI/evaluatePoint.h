//
// Created by ycm on 2023/12/8.
//

#ifndef GOBANG_EVALUATE_POINT_H
#define GOBANG_EVALUATE_POINT_H

#include "board.h"
#include "static.h"
#include "logging.h"

class Board;

namespace evaluateScore{
    double countToScore(int count, int block, int empty=0);
    void reset(int *empty, int *count, int *block, int *secondBlock);
}

double scorePoint(Board &board, int px, int py, Role role, int tmpDir=-1);

#endif //GOBANG_EVALUATE_POINT_H
