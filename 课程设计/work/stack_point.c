#include <stdbool.h>
#include <stdlib.h>
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

Stack *create_stack(int size) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->count = 0;
    s->size = size;
    s->data = (Point *) malloc(size * sizeof(Point));
    return s;
}

bool is_empty(Stack *s) {
    return s->count == 0;
}

bool is_full(Stack *s) {
    return s->count == s->size;
}

void stack_push(Stack *s, Point value) {
    s->data[s->count++] = value;
}

Point stack_pop(Stack *s) {
    return s->data[--s->count];
}

void delete_stack(Stack *s){
    free(s->data);
    free(s);
}