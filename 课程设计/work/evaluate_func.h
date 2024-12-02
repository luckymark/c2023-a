#ifndef GOBANG_EVALUATE_FUNC_H
#define GOBANG_EVALUATE_FUNC_H
#include "defination.h"
float pow_float(int x, int y);
float evaluate_line(int (*b)[15], Point point, int dx, int dy, enum piece sideMax);
float evaluate_line_range(int (*b)[15], Point point, int dx, int dy,Range range,enum piece sideMax);
float evaluate_point(int (*b)[15],Point *step,enum piece side);
float evaluate(int (*b)[15], enum piece sideMax);
float re_evaluate(int (*b)[15],enum piece sideMax,Point *step,enum piece side,float score);
float isStepTerminate(int (*b)[15], Point *step, enum piece sideMax, enum piece side);
#endif //GOBANG_EVALUATE_FUNC_H
