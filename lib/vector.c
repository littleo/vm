#include "vector.h"

void vector_init(vector * v) {
    v->capacity = 0;
    v->count = 0;
    v->data = NULL;
}

void vector_push(vector * v, uint32_t entry) {
    if (v->capacity < v->count+1) {
        uint32_t old_capacity = v->capacity;
        v->capacity = GROW_CAPACITY(old_capacity);
        v->data = GROW_ARRAY(v->data, uint32_t, 
            old_capacity, v->capacity);
    }

    v->data[v->count] = entry;
    v->count++;
}

uint32_t vector_pop(vector * v) {
    if (v->count > 0) {
        return v->data[--v->count];
    }
}

void vector_free(vector * v) {                      
  FREE_ARRAY(uint32_t, v->data, v->capacity);
  vector_init(v);                                 
}

