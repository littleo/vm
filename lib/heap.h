#ifndef gc_heap_h
#define gc_heap_h

#include "common.h"
#include "stack.h"

#define HEAP_SIZE 10

// typedef uint64_t heap_e;
typedef struct {
    stack_e hd;
    stack_e tl;
} heap_e;

typedef struct {
    int count;
    int capacity;
    heap_e * heap_t;
} heap_s;
#endif