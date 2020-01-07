#include "heap.h"

void heap_init(heap_s * hp) {
    hp->capacity = 0;
    hp->count = 0;
    hp->data = NULL;
    vector_init(&hp->free_list);
}

void heap_head_show(heap_s * hp) {
    if (hp->count) {
        heap_e head = hp->data[hp->count-1];

        printf(" HEAP [%08x, %08x]", head.hd, head.tl);
    } else {
        printf(" [EMPTY]");
    }
}

void heap_push(heap_s * hp, stack_e * sp, heap_e entry) {
    
    if (hp->capacity < hp->count+1) {
        // 1. call garbage collector and fit empty entries
        printf("\n-------------GC start-------------\n");
        // gc_mark();
        // gc_sweep();
        printf("\n-------------GC stop--------------\n");

        if (hp->free_list.count > 0) {
            uint32_t offset = vector_pop(&hp->free_list);
            hp->data[offset] = entry;

            return;
        } else {
            printf("I did't succeed to garbage collection\n");
        }

        // 2. try to realloc
        uint32_t old_capacity = hp->capacity;
        hp->capacity = GROW_CAPACITY(old_capacity);
        hp->data = GROW_ARRAY(hp->data, heap_e, 
            old_capacity, hp->capacity);

        printf("\n-------------Realloc-------------\n");
        if (hp->data == NULL) {
            printf("I CAN'T DO ANYTHING ELSE");
            exit(1);
        }
        printf("\n-------------Successfull realloc-------------\n");
    }

    hp->data[hp->count] = entry;
    hp->count++;
}

void heap_free(heap_s * hp) {                      
  FREE_ARRAY(heap_e, hp->data, hp->capacity);
  heap_init(hp);                                 
}