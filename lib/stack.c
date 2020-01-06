#include "stack.h"

void stack_init(stack_s * v) {
    v->capacity = STACK_SIZE;
    v->count = 0;
    v->data = (stack_e *) malloc(STACK_SIZE * sizeof(stack_e));
}

void stack_head_show(stack_s * v) {
    if (v->count) {
        printf(" [%08x]", v->data[v->count-1]);
    } else {
        printf(" [EMPTY]");
    }
}

stack_e stack_head(stack_s * v) {
    if (v->count)
        return v->data[v->count-1];

    perror("Not stack head");
    exit(EXIT_FAILURE);
}

void stack_push(stack_s * v, stack_e entry) {
    if (v->capacity < v->count+1) {
        perror("Not enough stack");
        exit(EXIT_FAILURE);
    }

    v->data[v->count] = entry;
    v->count++;
}

stack_e stack_pop(stack_s * v) {
    if (v->count > 0) {
        return v->data[--v->count];
    }
}

void stack_free(stack_s * v) {                      
  FREE_ARRAY(stack_e, v->data, v->capacity);
  stack_init(v);                                 
}

