//
// Created by ycm on 2023/12/9.
//

#include "ai.h"

Logger aiLogger("GobangAI");

//Computer::Computer():board() {}

Place Computer::setComputer() {
    aiLogger.info("Computer is thinking...");
    if(this->board.allSteps.size()>1) {
        //TODO: 随机开局
    }
    auto p = deepenAll(this->board, Role::COMPUTER, config::searchDepth);
    this->board.put(p, Role::COMPUTER, true);

    this->isWin(true);
    return p;
}

Place Computer::setHuman(Place &place) {
    aiLogger.info(std::string("human's next step is "+place.toString()));

    if(!(this->set(place, Role::HUMAN)) || this->isWin(true)!=Role::NONE){
        return *(new Place{-1, -1});
    }else{
        return this->setComputer();
    }
}

bool Computer::set(Place &place, Role role) {
    return this->board.put(place, role, true);
}

Role Computer::isWin(bool log/*=false*/) {
    auto Win = this->board.isWin(log);
    if(Win!=Role::NONE){
        aiLogger.info((Win==Role::COMPUTER)?"Computer wins!":"Human wins!");
        // TODO: Game over
    }
    this->win = Win;
    return Win;
}
