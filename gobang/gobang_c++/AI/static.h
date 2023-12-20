//
// Created by ycm on 2023/12/8.
//

#ifndef GOBANG_STATIC_H
#define GOBANG_STATIC_H

#include <string>

enum class Role: signed char{
    HUMAN = 0,
    COMPUTER = 1,
    NONE = 2
};


namespace Score {
    enum Score {
        ONE = 10,
        TWO = 100,
        THREE = 1000,
        FOUR = 10000,
        FIVE = 100000,
        BLOCKED_ONE = 1,
        BLOCKED_TWO = 10,
        BLOCKED_THREE = 100,
        BLOCKED_FOUR = 10000,
    };
}

typedef struct Leaf {
    double score;
    int step;
    bool abCut;
    int depth;

    [[nodiscard]] std::string toString() const;//TODO: 为什么要加nodiscard标记???
} Leaf;

typedef struct Place{
    int x;
    int y;
    Leaf *v;
    Role role;
    double score;
    double scoreCom;
    double scoreHum;
    int step;
    int min;

    [[nodiscard]] std::string toString() const;
} Place;

#endif //GOBANG_STATIC_H
