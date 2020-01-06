#include "common.h"

void printbits(void *pnt0, size_t cnt) {
    unsigned char *pnt = pnt0;
    // unsigned int cnt = 8;

    while (cnt--) {
        putchar('0'|(((*pnt) >> cnt) & 1));

        if (cnt == 7) putchar('|');
    }
    putchar('\n');
}