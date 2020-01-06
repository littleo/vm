#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STACK_SIZE 10
#define HEAP_SIZE 10

#define byte uint8_t
#define stack_e int32_t

typedef struct {
    stack_e f;
    stack_e s;
} heap_e;

typedef struct {
    heap_e * heap_array;
    uint32_t size;
    // uint32_t * scan, * next;
} heap_s;


int main(int argc, char const *argv[])
{

    int x;

    x = 65;

    printf("(%c)", x);

    return 0;
}
