#ifndef gc_vector_h
#define gc_vector_h

#include "common.h"
#include "memory.h"

typedef struct {
    uint32_t * data;
    uint32_t capacity;
    uint32_t count;
} vector;

void vector_init();
void vector_push();
uint32_t vector_pop();
void vector_free();

#endif