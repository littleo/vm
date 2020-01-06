#include "bytecode.h"

byte * read_bytecode(FILE * fp){
	int cur_bytecode, cnt;
	byte * bytecode;

	cnt = 0;
	bytecode = (byte *) malloc(BYTECODE_SIZE * sizeof(byte));

	while ((cur_bytecode = getc(fp)) != EOF)
		bytecode[cnt++] = (char) cur_bytecode;

	return bytecode;
}