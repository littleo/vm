CC = gcc
IDIR =./lib
CFLAGS=-I$(IDIR)

test: test.c ../lib/memory.c ../lib/vector.c ../lib/heap.c
	gcc -o test test.c ../lib/memory.c ../lib/vector.c ../lib/heap.c $(CFLAGS)
