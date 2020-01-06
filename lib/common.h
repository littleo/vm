#ifndef gc_common_h
#define gc_common_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h> 

#define TRUE 1
#define FALSE 0
#define BYTECODE_SIZE 65536 // 2**16
#define STACK_SIZE 200

#define get_addr(pc) \
	(*(pc+1) & 0xFF) | (*(pc+2) << 8)

#define show_bits8(ptr) printbits(ptr, 8)
#define show_bits32(ptr) printbits(ptr, 32)

#define print_entry(x) \
	printf(" (hd: %08x, tl: %08x)", x->hd, x->tl);

typedef uint8_t byte;
typedef uint16_t addr;

void printbits();

#endif