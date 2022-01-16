CC = gcc
IDIR =../lib
CFLAGS=-I$(IDIR)

OUTPUT=../

vm: vm.c ./lib/common.c ./lib/bytecode.c ./lib/heap.c ./lib/memory.c ./lib/vector.c ./lib/stack.c ./lib/gc.c
	gcc -Wno-format -o $(OUTPUT)vm vm.c ./lib/bytecode.c ./lib/common.c ./lib/heap.c ./lib/memory.c ./lib/vector.c ./lib/stack.c ./lib/gc.c $(CFLAGS)
