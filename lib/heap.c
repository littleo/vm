#include "heap.h"

void heap_init(heap * h) {
    h->capacity = 0;
    h->count = 0;
    h->data = NULL;
}

void heap_push(heap * h, heap_e entry) {
    if (h->capacity < h->count+1) {
        uint32_t old_capacity = h->capacity;
        h->capacity = GROW_CAPACITY(old_capacity);
        h->data = GROW_ARRAY(h->data, heap_e, 
            old_capacity, h->capacity);
    }

    h->data[h->count] = entry;
    h->count++;
}

void heap_free(heap * h) {                      
  FREE_ARRAY(heap_e, h->data, h->capacity);
  heap_init(h);                                 
}