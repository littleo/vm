#ifndef gc_gc_h
#define gc_gc_h

#include "common.h"
#include "heap.h"
#include "stack.h"
#include "memory.h"

void gc_mark();
void gc_mark_all();
void gc_sweep();

#endif