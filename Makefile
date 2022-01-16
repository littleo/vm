CC = gcc
IDIR =./lib
CFLAGS=-I$(IDIR)

vm: vm.c ./lib/common.c ./lib/bytecode.c ./lib/heap.c ./lib/memory.c ./lib/vector.c ./lib/stack.c ./lib/gc.c
	gcc -o vm vm.c ./lib/bytecode.c ./lib/common.c ./lib/heap.c ./lib/memory.c ./lib/vector.c ./lib/stack.c ./lib/gc.c $(CFLAGS) -O3 -flto
