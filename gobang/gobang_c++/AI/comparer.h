//
// Created by ycm on 2023/12/9.
//

#ifndef GOBANG_COMPARER_H
#define GOBANG_COMPARER_H

namespace comparerConstVar{
    const double threshold = 1.15;
    const double delta = 0.1;
    const double infinitesimal = 0.01;
}

namespace comparer {
    bool equal(double a, double b);

    bool greater(double a, double b);

    bool greaterEqual(double a, double b);

    bool less(double a, double b);

    bool lessEqual(double a, double b);
}

#endif //GOBANG_COMPARER_H
