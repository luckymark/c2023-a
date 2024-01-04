#include "Gobang.h"

Stack *creat_stack(int size) {
    auto stack = (Stack *) malloc(sizeof(Stack));
    stack->count = 0;
    stack->size = size;
    stack->data = (Step *) calloc(size, sizeof(Step));
    return stack;
}

int is_empty(Stack *stack) {
    if (stack->count == 0)
        return 1;
    else
        return 0;
}

int is_full(Stack *stack) {
    if (stack->count == stack->size)
        return 1;
    else
        return 0;
}

void stack_push(Stack *stack, Step *value) {
    if (!is_full(stack)) {
        stack->data[stack->count] = *value;
        stack->count++;
    } else
        printf("error");
}

Step *stack_pop(Stack *stack) {
    if (!is_empty(stack)) {
        stack->count--;
        return &stack->data[stack->count];
    } else
        printf("error");
}