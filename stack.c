#include "stack.h"

Stack *stack_new() {
    Stack *stack;

    stack = (Stack *)malloc(sizeof(Stack));
    stack->size = 0;
    stack->data = NULL;

    return stack;
}

void stack_free(Stack *stack) {
    if (stack->data) {
        free(stack->data);
    }
    free(stack);
}

void stack_grow(Stack *stack, int new_size) {
    if (stack->size >= new_size) {
        return;
    }

    stack->data = (double *)realloc(stack->data, sizeof(double) * new_size);
    stack->size = new_size;
}

void stack_shrink(Stack *stack, int new_size) {
    if (stack->size <= new_size) {
        return;
    }

    stack->data = (double *)realloc(stack->data, sizeof(double) * new_size);
    stack->size = new_size;
}

void stack_push(Stack *stack, double d) {
    stack_grow(stack, stack->size + 1);
    stack->data[stack->size - 1] = d;
}

double stack_pop(Stack *stack) {
    double d;

    d = stack->data[stack->size - 1];
    stack_shrink(stack, stack->size - 1);

    return d;
}

void stack_swp(Stack *stack) {
    double one, two;

    one = stack->data[stack->size - 1];
    two = stack->data[stack->size - 2];

    stack->data[stack->size - 1] = two;
    stack->data[stack->size - 2] = one;
}

void stack_dup(Stack *stack) {
    double d;

    d = stack->data[stack->size - 1];
    stack_grow(stack, stack->size + 1);
    stack->data[stack->size - 1] = d; 
}