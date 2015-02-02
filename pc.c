#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

#define TYPE_ADD 0
#define TYPE_SUB 1
#define TYPE_MUL 2
#define TYPE_DIV 3

typedef char *callback_t(Stack *);

char *do_simple(Stack *s, int type) {
    double one, two, result;

    STACK_CHECK(s, 2)

    one = stack_pop(s);
    two = stack_pop(s);
    
    switch (type) {
        case TYPE_ADD:
            result = one + two;
            break;
        case TYPE_SUB:
            result = one - two;
            break;
        case TYPE_MUL:
            result = one * two;
            break;
        case TYPE_DIV:
            result = one / two;
            break;
        default:
            result = 0;
            break;
    }

    stack_push(s, result);
    return NULL;
}

char *do_add(Stack *s) {
    return do_simple(s, TYPE_ADD);
}

char *do_subtract(Stack *s) {
    return do_simple(s, TYPE_SUB);
}

char *do_multiply(Stack *s) {
    return do_simple(s, TYPE_MUL);
}

char *do_divide(Stack *s) {
    return do_simple(s, TYPE_DIV);
}

char *do_sqrt(Stack *s) {
    double one, result;

    STACK_CHECK(s, 1)
    one = stack_pop(s);
    result = sqrt(one);
    stack_push(s, result);

    return NULL;
}
 
char *do_power(Stack *s) {
    double one, two, result;

    STACK_CHECK(s, 2)
    one = stack_pop(s);
    two = stack_pop(s);
 
    result = pow(one, two);
    stack_push(s, result);

    return NULL;
}

char *do_show(Stack *s) {
    int i;

    for (i = 0; i < s->size; i++) {
        printf("[%d]: %f\n", i, s->data[i]);
    }

    return NULL;
}

char *do_swap(Stack *s) {
    STACK_CHECK(s, 2);
    stack_swp(s);
    return NULL;
}

char *do_pop(Stack *s) {
    double d;
    char buf[32];

    STACK_CHECK(s, 1)

    d = stack_pop(s);
    memset(buf, 0, 32);
    snprintf(buf, 32, "%f\n", d);

    return strdup(buf);
}

char *do_dup(Stack *s) {
    STACK_CHECK(s, 1)
    stack_dup(s);
    return NULL;
}

typedef struct callback_s {
    char c;
    callback_t *callback;
} callback_s;

const callback_s callbacks[] = {
    { '+', do_add },
    { '-', do_subtract },
    { '*', do_multiply },
    { '/', do_divide },
    { '^', do_power },
    { 'v', do_sqrt },
    { 'p', do_pop },
    { 'd', do_dup }, 
    { 's', do_show },
    { 'S', do_swap },
    { 0, NULL }
};

const int num_callbacks = 10;

void repl() {
    Stack *s = stack_new();
    char *line;
    size_t line_size;
    int ret;
    int i;
    callback_s cur;
    bool good;
    double d;
    char *res;

    while (true) {
        line = NULL;
        good = false;
        res = NULL;
        ret = getline(&line, &line_size, stdin);

        if (ret == -1) {
            break;
        }

        line[ret - 1] = 0; /* Strip newline */
        
        if (strlen(line)) {
            for (i = 0; i < num_callbacks; i++) {
                cur = callbacks[i];
                if (cur.c == line[0]) {
                    res = (cur.callback)(s);
                    if (res != NULL) {
                        printf("%s", res);
                        free(res);
                    }
                    good = true;
                    break;
                }
            }

            if (!good) { /* Not valid, push number to stack. */
                d = strtod(line, NULL);
                stack_push(s, d);
            }
        }
        free(line);
    }

    stack_free(s);
}

int main(void) {
    repl();
    return 0;
}
