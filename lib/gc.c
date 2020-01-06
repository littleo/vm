#include "gc.h"

void gc_mark(stack_e * sp) {
    
}

void gc_mark(heap_s * hp, stack_e * entry) {
    // save us from cycle
    if (entry->marked) return;

    if (entry->type) 
        entry->marked = 1;

    if (entry->type == OBJ_PAIR) {
        mark(object->head);
        mark(object->tail);
    }
}

void gc_mark
void gc_mark() {
    return 0;
}