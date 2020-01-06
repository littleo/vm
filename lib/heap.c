#include "heap.h"
#include "memory.h"

void init_heap(heap_s * h) {
    h->count = 0;
    h->capacity = 0;
    h->heap_t = NULL;
}

void heap_add(heap_s * h, heap_e new_entry) {   
    if (h->capacity < h->count + 1) {       
        int old_capacity = h->capacity;            
        h->capacity = GROW_CAPACITY(old_capacity); 
        h->heap_t = GROW_ARRAY(h->heap_t, heap_e,
            old_capacity, h->capacity);            
    }

    h->heap_t[h->count] = new_entry;               
    h->count++;
}     
