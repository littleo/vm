#include "stack.h"

void stack_init(stack_s * v) {
    v->capacity = 0;
    v->count = 0;
    v->data = NULL;
}

void stack_push(stack_s * v, stack_e entry) {
    if (v->capacity < v->count+1) {
        uint32_t old_capacity = v->capacity;
        v->capacity = GROW_CAPACITY(old_capacity);
        v->data = GROW_ARRAY(v->data, stack_e, 
            old_capacity, v->capacity);
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

