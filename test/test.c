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
    vector freelist;
    vector_init(&freelist);
    for (size_t i = 0; i < 33; i++)
    {
        vector_push(&freelist, i);
    }
    
    printf("Capacity: %d Count: %d\n", freelist.capacity, freelist.count);
    for (size_t i = 0; i < freelist.count; i++)
    {
        printf("%d ", freelist.data[i]);
    }

    for (size_t i = 0; i < 10; i++)
    {
        vector_pop(&freelist);
    }

    printf("\nCapacity: %d Count: %d\n", freelist.capacity, freelist.count);
    for (size_t i = 0; i < freelist.count; i++)
    {
        printf("%d ", freelist.data[i]);
    }

    return 0;
}
