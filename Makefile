CC = gcc
IDIR =./lib
CFLAGS=-I$(IDIR)

vm: vm.c ./lib/common.c ./lib/bytecode.c ./lib/heap.c ./lib/memory.c ./lib/vector.c
	gcc -o vm vm.c ./lib/bytecode.c ./lib/common.c ./lib/heap.c ./lib/memory.c ./lib/vector.c $(CFLAGS)
