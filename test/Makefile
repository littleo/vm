CC = gcc
IDIR =./lib
CFLAGS=-I$(IDIR)

test: test.c ../lib/memory.c ../lib/vector.c ../lib/stack.c
	gcc -o test test.c ../lib/memory.c ../lib/vector.c ../lib/stack.c $(CFLAGS)
