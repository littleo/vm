#include "lib/common.h"
#include "lib/bytecode.h"
#include "lib/debug.h"
#include "lib/heap.h"
#include "lib/stack.h"

#define next_instruction \
	goto next_instruction_d

#define next_instruction_f \
	goto *(void *)(label_tab[*pc])

// NOT DEBUG
// #define next_instruction 
// 	goto *(void *)(label_tab[*pc])

int main(int argc, char const *argv[])
{
	static void * label_tab[] = {
		&&halt_label,
		&&jump_label,
		&&jnz_label,
		&&dup_label,
		&&swap_label,
		&&drop_label,
		&&push4,
		&&push2,
		&&push1,
		&&add_label,
		&&sub_label,
		&&mul_label,
		&&div_label,
		&&mod_label,
		&&eq_label,
		&&ne_label,
		&&lt_label,
		&&gt_label,
		&&le_label,
		&&ge_label,
		&&not_label,
		&&and_label,
		&&or_label,
		&&input_label,
		&&output_label,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&clock,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&nop,
		&&cons,
		&&hd,
		&&tl
	};

	if (argc < 2)
		exit(EXIT_FAILURE);

	// open byte_program file
	FILE * fp;
	fp = fopen(argv[1], "r");

	if (fp == NULL)
		exit(EXIT_FAILURE);

	// read byte_program
	byte * byte_program;
	byte_program = read_bytecode(fp);

	// init stack
	stack_e * stack;
	stack = (stack_e *) malloc(STACK_SIZE * sizeof(stack_e));

// --------------------------------
	byte * pc;
	stack_e * sp;
	addr jmp_addr;

	stack_e arg, temp;
	stack_e a,b;
	uint32_t offset;
	// int32_t arg_val, sarg_val;

	clock_t t; 
	double time_taken;
// --------------------------------
	heap_e * heap, * hp, * heap_base;
	heap = (heap_e *) malloc(HEAP_SIZE * sizeof(heap_e));

	heap_e h_entry;
// ---------------------------------
	// pc = &byte_program[0];
	pc = byte_program;
	// sp = &stack[0];
	sp = stack;
	// hp = &heap[0];
	hp = heap;
	heap_base = heap;
	t = clock(); 

	printf("[Started]");

	// int offset;
	int opcode;

next_instruction_d:
	opcode = *pc & 0xFF;
	printf("\t [%08x, %08x]", *(sp), *(sp-1));
	printf("\n");

	printf("%p: [%02x] %s", pc, opcode, labels[opcode]);
	next_instruction_f;

halt_label:
	goto end_label;

jump_label:
	jmp_addr = get_addr(pc);
	printf(" (+) %04x", jmp_addr);

	pc = byte_program + jmp_addr;
	next_instruction;

jnz_label:
	arg = *(sp--);

	if (get_value(arg)) {
		jmp_addr = get_addr(pc);
		pc = byte_program + jmp_addr;

		printf(" (+) %02x", jmp_addr);
	} else { 
		printf(" (+) 1");

		pc += 3;
	}

	next_instruction;

dup_label:
	arg = *(++pc);
	offset = get_value(arg);

	arg = *(sp - offset);
	*(++sp) = arg;

	printf(" (pos) SP-%d", offset);

	pc++;
	next_instruction;

swap_label:
	arg = *(++pc);
	offset = get_value(arg);

	arg = *(sp - offset);
	temp = *sp;

	*sp = arg;
	*(sp - offset) = temp;

	pc++;
	next_instruction;

drop_label:
	sp--;

	pc++;
	next_instruction;

push4:	
	*(++sp) = *(int32_t *) (++pc);

	pc += 4;
	next_instruction;

push2:
	*(++sp) = *(int16_t *) (++pc);

	pc += 2;
	next_instruction;

push1:
	*(++sp) = *(int8_t *) (++pc);

	pc++;
	next_instruction;

add_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = (a+b) | temp;

	pc++;
	next_instruction;

sub_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = (a-b) | temp;

	pc++;
	next_instruction;

mul_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = (a*b) | temp;

	pc++;
	next_instruction;

div_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = (a/b) | temp;

	pc++;
	next_instruction;

mod_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = (a%b) | temp;

	pc++;
	next_instruction;

eq_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = a == b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

ne_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = a != b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

lt_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = a < b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

gt_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = a > b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

le_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = a <= b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

ge_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = a >= b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

not_label:
	b = *(sp--);

	*(++sp) = !b;

	pc++;
	next_instruction;

and_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = ((a == 0) | (b == 0)) ? 0 : 1;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

or_label:
	b = *(sp--);
	a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	a = get_value(a);
	b = get_value(b);

	*(++sp) = ((a == 0) & (b == 0)) ? 0 : 1;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

input_label:
	printf(" ");
	*(++sp) = getchar();

	pc++;
	next_instruction;

output_label:
	arg = *(sp--);

	printf("(%c)", arg);
	// putchar(arg);

	pc++;
	next_instruction;

clock:
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf(": %0.6lf", time_taken);

	pc++;
	next_instruction;

cons:
	b = *(sp--);
	a = *(sp--);

	h_entry = (heap_e) {.hd = a, .tl = b};
	// printf(" (hd: %08x, tl: %08x)", h_entry.hd, h_entry.tl);
	*(++hp) = h_entry;
	// print_entry(hp);

	offset = (hp - heap_base);
	*(++sp) = address_me(offset);

	pc++;
	next_instruction;

hd:
	arg = *(sp--);

	if (!(mask(arg))) {
		perror("No address");
		exit(1);
	}

	offset = get_value(arg);
	printf(" (offset) %04x", offset);

	h_entry = *(heap_base + offset);
	*(++sp) = (h_entry.hd);

	pc++;
	next_instruction;

tl:
	arg = *(sp--);

	if (!(mask(arg))) {
		perror("No address");
		exit(1);
	}

	offset = get_value(arg);
	printf(" (offset) %04x", offset);

	h_entry = *(heap_base + offset);
	*(++sp) = (h_entry.tl);

	pc++;
	next_instruction;

nop:
	pc++;
	next_instruction;

end_label:
	free(stack);
	free(byte_program);
	fclose(fp);
	exit(EXIT_SUCCESS);

	return 0;
}