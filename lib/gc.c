#include "gc.h"

void gc_mark_me(heap_s * hp, stack_s * sp, uint32_t offset) {
    heap_e * entry;
    entry = &(hp->data[offset]);

    if (entry->hd.marked) {
        return;
    }

    entry->hd.marked = 1;

    if (entry->hd.type) {
        uint32_t offset = entry->hd.value;

        printf(" > %d", offset);
        gc_mark_me(hp, sp, offset);
    }

    if (entry->tl.type) {
        uint32_t offset = entry->tl.value;

        printf("> %d", offset);
        gc_mark_me(hp, sp, offset);
    }
}

void gc_mark(heap_s * hp, stack_s * sp) {
    uint32_t offset;

    // printf("\nLets begin marking: stack size %d\n", sp->count);

    for (size_t i = 0; i < sp->count; i++)
    {
        
        if (sp->data[i].type) {
            // printf("[%d] Pointer offset: %08x \n", i, sp->data[i].value);
            offset = sp->data[i].value;
            // gc_mark_me(hp, sp, offset);
            printf("\n %d", offset);
            gc_mark_me(hp, sp, offset);
            printf("\n");
        }
        // printf("[%d] Value offset: %08x \n", i, sp->data[i].value);
    }
    
}

void gc_sweep(heap_s * hp) {
    for (size_t i = 0; i < hp->count; i++)
    {  
        heap_e entry = hp->data[i];

        if (entry.hd.marked) {
            hp->data[i].hd.marked = 0;
        } else {
            vector_push(&hp->free_list, i);
        }
    }
}
