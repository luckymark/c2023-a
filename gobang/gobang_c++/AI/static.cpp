//
// Created by ycm on 2023/12/8.
//

#include "static.h"

std::string Leaf::toString() const {
    std::string result = "Leaf(score=";
    result += std::to_string(this->score);
    result += ", step=";
    result += std::to_string(this->step);
    result += ")";

    return result;
}

std::string Place::toString() const {
    std::string result = "Place(";
    result += std::to_string(this->x);
    result += ", ";
    result += std::to_string(this->y);
    result += ", role=";
    switch (this->role) {
        case Role::HUMAN:
            result += "human";
            break;
        case Role::COMPUTER:
            result += "computer";
            break;
        case Role::NONE:
            result += "blank";
            break;
        default:
            result += "unknown";
            break;
    }
    if(this->score!=0)result += ", score="+std::to_string((long)this->score);
    if(this->scoreCom!=0)result += ", computer's score="+std::to_string((long)this->scoreCom);
    if(this->scoreHum!=0)result += ", human's score="+std::to_string((long)this->scoreHum);
    if(this->step)result += ", step="+std::to_string(this->step);
    if(this->min)result += ", min="+std::to_string(this->min);
    result += ")";

    return result;
}
