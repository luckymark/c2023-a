//
// Created by ycm on 2023/12/9.
//

#ifndef GOBANG_CONFIG_H
#define GOBANG_CONFIG_H

#include <string>

namespace config{
    const int timeLimit = 10;
    const int spreadLimit = 3;
    const int searchDepth = 10;
    const bool star = true;
    const int starSpread = 10;//开启star spread模式的轮数
    const int candidatesLimit = 100;
    const bool cache = true;
}

#endif //GOBANG_CONFIG_H
