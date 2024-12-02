#ifndef GOBANG_STACK_POINT_H
#define GOBANG_STACK_POINT_H
#include <stdbool.h>
#include "defination.h"
typedef struct Stack {
    Point *data;
    int count;
    int size;
} Stack;

Stack *create_stack(int size);
bool is_empty(Stack *);
bool is_full(Stack *s);
void stack_push(Stack *s, Point value);
Point stack_pop(Stack *s);
void delete_stack(Stack *s);
#endif