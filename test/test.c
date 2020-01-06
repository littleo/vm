#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../lib/memory.h"
#include "../lib/vector.h"
#include "../lib/heap.h"

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

int main(int argc, char const *argv[])
{
    stack_e * stack_base, * sp;
    stack_base = (stack_e *) malloc(sizeof(stack_e) * STACK_SIZE);
   
    heap_e * heap_base;
    heap_s heap;
    heap_init(&heap);

	stack_e default_stack_val = {0,0,0};
	stack_e default_stack_ptr = {0,1,0};

    free(stack_base);

    return 0;
}
