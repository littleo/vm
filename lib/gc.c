#include "gc.h"

void gc_mark();
void gc_mark_all(stack_s * sp, heap_s * hp);
void gc_sweep();
