CC = gcc
IDIR =./lib
CFLAGS=-I$(IDIR)

gc: vm.c ./lib/common.c ./lib/bytecode.c 
	gcc -o gc vm.c ./lib/bytecode.c ./lib/common.c $(CFLAGS)
