#ifndef gc_heap_h
#define gc_heap_h

#include "common.h"
#include "stack.h"
#include "memory.h"
#include "vector.h"

#define HEAP_SIZE 10

typedef struct {
    stack_e hd;
    stack_e tl;
} heap_e;

typedef struct {
    heap_e * data;
    int count;
    int capacity;
    vector free_list;
} heap_s;

void heap_init();
void heap_push();
void heap_free();

#endif