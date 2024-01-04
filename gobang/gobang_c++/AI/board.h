//
// Created by ycm on 2023/12/8.
//

#ifndef GOBANG_BOARD_H
#define GOBANG_BOARD_H

#include "static.h"
#include "evaluatePoint.h"
#include "config.h"
#include "logging.h"

#include <unordered_map>
#include <list>
#include <vector>
#include <string>

namespace board{
    template <typename T> T abs(T x);
    double fixScore(double score);
    bool starTo(const Place &point, const std::list<Place> &points= {});
}

class Board{
public:
    static const int X=15, Y=15;
    Role map[15][15]{};
    double comScore[15][15]{};
    double humScore[15][15]{};
    double comMaxScore=0, humMaxScore=0;
    unsigned turn=0;
    std::vector<Place> allSteps{};
    std::vector<Place> currentSteps{};
    double scoreCache[2][4][15][15]{};

    void updateScore(Place &place);
    bool put(Place &place, Role role, bool log=false);
    bool remove(Place &place, bool log=false);
    std::list<Place> &generator(Role role, bool onlyThrees=false, bool starSpread=false, bool log=false);
    double evaluate(Role role);
    Role isWin(bool log=false);

    Board();
    std::string toString();
//private:
    Board(const Board &board);
    Board &operator=(const Board &board);
    ~Board();
protected:
    std::unordered_map<int, Place> evaluateCache;

    bool hasNeighbor(int px, int py, int distance, int count);
    void update(int px, int py, int updateDir);
    int isFive(const Place &place, Role role);
};

#endif //GOBANG_BOARD_H
