#ifndef gc_stack_h
#define gc_stack_h

#include "common.h"

typedef struct {
    int32_t value: 30;
    int32_t type : 1;
} stack_e;

// #define MASK 0x80000000
// #define UNMASK 0x7fffffff

// #define mask(x) \
// 	(x & MASK)
// #define get_value(x) \
// 	(x & UNMASK)
// #define address_me(x) \
// 	(x | MASK)

#endif