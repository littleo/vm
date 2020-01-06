#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../lib/memory.h"

// #define STACK_SIZE 100
#define HEAP_SIZE 100

void printbits(void * pnt0, size_t cnt) {
    uint32_t * pnt = pnt0;
    // unsigned int cnt = 8;

    while (cnt--) {
        putchar('0'|(((*pnt) >> cnt) & 1));

        if (cnt == 31) putchar('|');
        // if (cnt == 30) putchar('|');
    }
    putchar('\n');
}

typedef struct {
    int32_t value	: 30;
    int32_t type 	: 1;
	int32_t marked 	: 1;
} stack_e;

typedef struct {
    stack_e f;
    stack_e s;
    uint32_t next;
} heap_e;

typedef struct {
    heap_e * heap_t;
    uint32_t size;
    uint32_t count;
} heap_s;

typedef struct {
    uint32_t * data;
    uint32_t capacity;
    uint32_t count;
} vector;

void vector_init(vector * v) {
    v->capacity = 0;
    v->count = 0;
    v->data = NULL;
}

void vector_push(vector * v, uint32_t entry) {
    if (v->capacity < v->count+1) {
        uint32_t old_capacity = v->capacity;
        v->capacity = GROW_CAPACITY(old_capacity);
        v->data = GROW_ARRAY(v->data, uint32_t, 
            old_capacity, v->capacity);
    }
}

int main(int argc, char const *argv[])
{
    vector free_list;


    return 0;
}
