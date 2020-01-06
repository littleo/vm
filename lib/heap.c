#include "heap.h"
#include "memory.h"

void init_heap(heap_e * h) {
    h->count = 0;
    h->capacity = 0;
    h->heap_t = NULL;
}