#ifndef __STACK_H_INCLUDED
#define __STACK_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#define STACK_CHECK(S, N) if (s->size < N) return NULL;

typedef struct Stack {
    int size;
    double *data;
} Stack;

Stack *stack_new();

void stack_free(Stack *stack);

void stack_grow(Stack *stack, int new_size);

void stack_shrink(Stack *stack, int new_size);

void stack_push(Stack *stack, double d);

double stack_pop(Stack *stack);

void stack_swp(Stack *stack);

void stack_dup(Stack *stack);
#endif