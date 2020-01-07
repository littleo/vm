#include "gc.h"

void gc_mark_me(heap_s * hp, stack_s * sp, uint32_t offset) {
    heap_e * entry;
    entry = &(hp->data[offset]);

    if (entry->hd.marked) {
        return;
    }

    entry->hd.marked = 1;

    if (entry->hd.type) {
        gc_mark_me(hp, sp, entry->hd.value);
    }

    if (entry->tl.type) {
        gc_mark_me(hp, sp, entry->tl.value);
    }
}

void gc_mark(heap_s * hp, stack_s * sp) {
    uint32_t offset;

    for (size_t i = 0; i < sp->count; i++)
    {
        if (sp->data[i].type) {
            offset = sp->data[i].value;
            gc_mark_me(hp, sp, offset);
        }
    }
    
}

void gc_sweep(heap_s * hp) {
    for (size_t i = 0; i < hp->count; i++)
    {  
        heap_e entry = hp->data[i];

        if (entry.hd.marked) {
            continue;
        } else {
            vector_push(&hp->free_list, i);
        }
    }
}
