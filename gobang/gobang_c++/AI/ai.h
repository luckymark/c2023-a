//
// Created by ycm on 2023/12/9.
//

#ifndef GOBANG_AI_H
#define GOBANG_AI_H

#include "static.h"
#include "board.h"
#include "config.h"
#include "negamax.h"
#include "logging.h"

class Computer{
public:
    Board board;
    Role win=Role::NONE;
    Place setComputer();
    Place setHuman(Place& place);
    Role isWin(bool log=false);

//    Computer();
//    ~Computer();
protected:
    bool set(Place &place, Role role);
};

#endif //GOBANG_AI_H
