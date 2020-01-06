#ifndef gc_stack_h
#define gc_stack_h

#include "common.h"
#include "memory.h"
#include "vector.h"

#define STACK_SIZE 65536

typedef struct {
    int32_t value	: 30;
    int32_t type 	: 1;
	int32_t marked 	: 1;
} stack_e;

typedef struct {
    stack_e * data;
    int count;
    int capacity;
} stack_s;

void stack_init();
void show_stack_head();
stack_e stack_head();
void stack_push();
stack_e stack_pop();
void stack_free();

#endif