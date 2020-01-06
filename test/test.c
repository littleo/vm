#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STACK_SIZE 10
#define HEAP_SIZE 10

#define byte uint8_t
// #define stack_e int32_t

typedef struct {
    int32_t value: 30;
    int32_t type : 1;
} stack_e;

typedef struct {
    stack_e f;
    stack_e s;
} heap_e;

typedef struct {
    heap_e * heap_array;
    uint32_t size;
    // uint32_t * scan, * next;
} heap_s;

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
    stack_e default_entry = {0,0};
    stack_e test = default_entry;
    
    // printbits(&test, 32);

    // char * array;
    // array = (char *) malloc(4 * sizeof(char));
    // array[0] = 0x09;
    // array[1] = 0x87;
    // array[2] = 0x83;
    // array[3] = 0x02;

    // test.value = * (int32_t *) array;
    // printf("T:%x V:%x \n", test.type, test.value);
    // test.value = -1;

    char * test1 = "Shit";
    printf("%s", test1);
    fflush(stdout);

    char * test2 = "Shit";
    printf("\r%-20s", stdout);

    // printbits(&test, 32);
}
