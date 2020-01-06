#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../lib/memory.h"
#include "../lib/vector.h"
#include "../lib/heap.h"

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

int main(int argc, char const *argv[])
{
    vector free_list;

    vector_init(&free_list);
    
    for (size_t i = 0; i < 33; i++)
    {
        vector_push(&free_list, i);
    }

    
    for (size_t i = 0; i < 33; i++)
    {
        printf("%d ", free_list.data[i]);
    }

    printf("\n%d, %d", free_list.capacity, free_list.count);

    vector_free(&free_list);
    return 0;
}
