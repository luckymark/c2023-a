#ifndef GOBANG_DEFINATION_H
#define GOBANG_DEFINATION_H
#include <stdbool.h>
enum piece {
    Empty = 0, Black = 1, White = -1
};
enum type {
    Max, Min
};
typedef struct {
    int x;
    int y;
} Point;

//每一个局面的下一步搜索范围如何确定？
typedef struct {
    int Xmin;
    int Xmax;
    int Ymin;
    int Ymax;
} Range;

typedef struct {
    Point point;
    float value;
}Point_Value;

typedef struct {
    Point point;
    int step;
} Point_step;

typedef struct {
    unsigned long long hash;
    float value;
    int count_step;
    int depth;
    bool isSearchFinished;
    Point nextPoint;
}Hash_value;

typedef struct {
    Point_Value *data;
    Point_Value *sequence[225];
} GenData;

typedef struct {
    Range *pRange;
    GenData *old_sequence;
    float score;
} Data;

typedef struct {
    Point *influenced_empty_old;
    GenData *old_sequence;
    float score;
}newData;

#endif //GOBANG_DEFINATION_H