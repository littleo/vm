#include "lib/common.h"
#include "lib/bytecode.h"
#include "lib/debug.h"
#include "lib/heap.h"
#include "lib/stack.h"
#include "lib/memory.h"

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
	stack_e default_stack_val = {0,0,0};
	stack_e default_stack_ptr = {0,1,0};

	int32_t a,b;
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
	printf("\t [%x, %x]", *(sp), *(sp-1));
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

	if (arg.value) {
		jmp_addr = get_addr(pc);
		pc = byte_program + jmp_addr;

		printf(" (+) %02x", jmp_addr);
	} else { 
		printf(" (+) 1");

		pc += 3;
	}

	next_instruction;

dup_label:
	offset = *(++pc);
	// offset = get_value(arg);

	arg = *(sp - offset);
	*(++sp) = arg;

	printf(" (pos) SP-%d", offset);

	pc++;
	next_instruction;

swap_label:
	offset = *(++pc);
	// offset = get_value(arg);

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
	default_stack_val.value = *(int32_t *) (++pc);
	*(++sp) = default_stack_val;

	pc += 4;
	next_instruction;

push2:
	default_stack_val.value = *(int16_t *) (++pc);
	*(++sp) = default_stack_val;

	pc += 2;
	next_instruction;

push1:
	default_stack_val.value = *(int8_t *) (++pc);
	*(++sp) = default_stack_val;

	pc++;
	next_instruction;

add_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a+b;
	*(++sp) = arg;

	// *(++sp) = (a+b) | temp;

	pc++;
	next_instruction;

sub_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a-b;
	*(++sp) = arg;

	// *(++sp) = (a-b) | temp;

	pc++;
	next_instruction;

mul_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a*b;
	*(++sp) = arg;

	// *(++sp) = (a*b) | temp;

	pc++;
	next_instruction;

div_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a/b;
	*(++sp) = arg;

	// *(++sp) = (a/b) | temp;

	pc++;
	next_instruction;

mod_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a%b;
	*(++sp) = arg;

	// *(++sp) = (a%b) | temp;

	pc++;
	next_instruction;

eq_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a == b ? 1 : 0;
	*(++sp) = arg;

	// *(++sp) = a == b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

ne_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a != b ? 1 : 0;
	*(++sp) = arg;

	// *(++sp) = a != b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

lt_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a < b ? 1 : 0;
	*(++sp) = arg;

	// *(++sp) = a < b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

gt_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a > b ? 1 : 0;
	*(++sp) = arg;

	// *(++sp) = a > b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

le_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a <= b ? 1 : 0;
	*(++sp) = arg;

	// *(++sp) = a <= b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

ge_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = a >= b ? 1 : 0;
	*(++sp) = arg;

	// *(++sp) = a >= b ? 1 : 0;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

not_label:
	arg = *(sp--);
	arg.value = !arg.value;

	*(++sp) = arg;

	pc++;
	next_instruction;

and_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = ((a == 0) | (b == 0)) ? 0 : 1;
	*(++sp) = arg;

	// *(++sp) = ((a == 0) | (b == 0)) ? 0 : 1;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

or_label:
	// b = *(sp--);
	// a = *(sp--);
	// temp = mask(a) ^ mask(b);

	// if (temp) {
	// 	perror("Not the same type");
	// 	exit(1);
	// }

	// a = get_value(a);
	// b = get_value(b);
	temp = *(sp--);
	arg = *(sp--);

	a = arg.value;
	b = temp.value;

	arg.value = ((a == 0) & (b == 0)) ? 0 : 1;
	*(++sp) = arg;

	// *(++sp) = ((a == 0) & (b == 0)) ? 0 : 1;
	// *(sp) = *(sp) | temp;

	pc++;
	next_instruction;

input_label:
	printf(" ");
	default_stack_val.value = getchar();
	*(++sp) = default_stack_val;

	pc++;
	next_instruction;

output_label:
	arg = *(sp--);

	printf("\t\t(%c)", arg.value);
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
	temp = *(sp--);
	arg = *(sp--);

	h_entry = (heap_e) {.hd = arg, .tl = temp};
	// printf(" (hd: %08x, tl: %08x)", h_entry.hd, h_entry.tl);
	*(++hp) = h_entry;
	// print_entry(hp);

	default_stack_ptr.value = (hp - heap_base);
	*(++sp) = default_stack_ptr;

	pc++;
	next_instruction;

hd:
	arg = *(sp--);

	if (!(arg.type)) {
		perror("No address");
		exit(1);
	}

	offset = arg.value;
	printf(" (offset) %04x", offset);

	h_entry = *(heap_base + offset);
	*(++sp) = (h_entry.hd);

	pc++;
	next_instruction;

tl:
	arg = *(sp--);

	if (!(arg.type)) {
		perror("No address");
		exit(1);
	}

	offset = arg.value;
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