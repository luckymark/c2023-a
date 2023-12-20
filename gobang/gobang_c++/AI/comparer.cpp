//
// Created by ycm on 2023/12/9.
//

#include "comparer.h"

bool comparer::equal(double a, double b){
    using namespace comparerConstVar;
    b = (b==0)?infinitesimal:b;
    return ((b>=0)?(b/threshold<=a and a<=b*threshold):(b*threshold<=a and a<=b/threshold));
}

bool comparer::greater(double a, double b){
    using namespace comparerConstVar;
    return (b>=0)?(a>=(b+delta)*threshold):(a>=(b+delta)/threshold);
}

bool comparer::greaterEqual(double a, double b){
    return comparer::equal(a, b) or comparer::greater(a, b);
}

bool comparer::less(double a, double b){
    using namespace comparerConstVar;
    return (b>=0)?(a<=(b-delta)/threshold):(a<=(b-delta)*threshold);
}

bool comparer::lessEqual(double a, double b){
    return comparer::equal(a, b) or comparer::less(a, b);
}
