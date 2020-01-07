#include "heap.h"
#include "gc.h"

void heap_init(heap_s * hp) {
    hp->capacity = 0;
    hp->count = 0;
    hp->data = NULL;
    vector_init(&hp->free_list);
}

void heap_head_show(heap_s * hp) {
    if (hp->count) {
        heap_e head = hp->data[hp->count-1];

        // printf("\n[");
        // printbits(head.hd, 32);
        // printf(",");
        // printbits(head.tl, 32);
        // printf("]\n");
        printf("[%08x,%08x]", head.hd, head.tl);
    } else {
        printf(" [EMPTY]");
    }
}

void heap_push(heap_s * hp, stack_e * sp, heap_e entry) {
    
    if (hp->capacity < hp->count+1) {
        // 1. check for available entries
        if (hp->free_list.count > 0) {
            uint32_t offset = vector_pop(&hp->free_list);
            printf("\nFound empty spot: %d \n", offset);
            hp->data[offset] = entry;

            return;
        }
        // 2. call garbage collector to find new available entries
        printf("\n-------------GC start-------------\n");
        gc_mark(hp, sp);
        gc_sweep(hp, sp);
        printf("\n-------------GC stop--------------\n");

        if (hp->free_list.count > 0) {
            uint32_t offset = vector_pop(&hp->free_list);
            printf("Found empty spot: %d \n", offset);
            hp->data[offset] = entry;

            return;
        } else {
            printf("I did't succeed to garbage collection\n");
        }
        

        // 3. try to realloc
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
        // printf("bye bye");
    }

    hp->data[hp->count] = entry;
    hp->count++;
}

void heap_free(heap_s * hp) {                      
  FREE_ARRAY(heap_e, hp->data, hp->capacity);
  heap_init(hp);                                 
}