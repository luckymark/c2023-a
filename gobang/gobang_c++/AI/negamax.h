//
// Created by ycm on 2023/12/8.
//

#ifndef GOBANG_NEGAMAX_H
#define GOBANG_NEGAMAX_H

#include "board.h"
#include "comparer.h"
#include "static.h"
#include "config.h"
#include "logging.h"
#include <ctime>
#include <climits>
#include <list>
#include <chrono>

namespace negamax{
    Leaf &_r(Board &board, int depth, double alpha, double beta, Role role, int step);
    double negamax(Board &board, std::list<Place> &candidates, Role role, int depth, double alpha, double beta);
    Place &deepening(Board &board, std::list<Place> &candidates, Role role, int depth);
}

Place deepenAll(Board &board, Role role=Role::COMPUTER, int depth=-1);

#endif //GOBANG_NEGAMAX_H
