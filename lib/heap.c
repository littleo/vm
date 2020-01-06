#include "heap.h"

void heap_init(heap_s * hp) {
    hp->capacity = 0;
    hp->count = 0;
    hp->data = NULL;
    hp->free_list = NULL;
}

void heap_push(heap_s * hp, stack_e * sp, heap_e entry) {
    if (hp->capacity < hp->count+1) {
        // No we have problem
        uint32_t old_capacity = hp->capacity;
        hp->capacity = GROW_CAPACITY(old_capacity);
        hp->data = GROW_ARRAY(hp->data, heap_e, 
            old_capacity, hp->capacity);
    }

    hp->data[hp->count] = entry;
    hp->count++;
}

void heap_free(heap_s * hp) {                      
  FREE_ARRAY(heap_e, hp->data, hp->capacity);
  heap_init(hp);                                 
}