#include "lib/common.h"
#include "lib/bytecode.h"
#include "lib/debug.h"
#include "lib/heap.h"
#include "lib/stack.h"
#include "lib/vector.h"
#include "lib/memory.h"
#include "lib/gc.h"

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

	FILE * fp;
	fp = fopen(argv[1], "r");

	if (fp == NULL)
		exit(EXIT_FAILURE);

	byte * byte_program;
	byte_program = read_bytecode(fp);

// ----------Variables-------------
	byte * pc;
	// stack_e * sp;
	addr jmp_addr;

// ------------Stack---------------
	stack_s sp;
	stack_init(&sp, STACK_SIZE);

	stack_e arg, temp;
	stack_e default_stack_val = {0,0,0};
	stack_e default_stack_ptr = {0,1,0};

	int32_t a,b;
	uint32_t offset;

// -------------Clock--------------
	clock_t t; 
	double time_taken;

// -------------Heap---------------
	heap_s hp;
	heap_init(&hp, 100);

	heap_e h_entry;
// ---------------------------------
	// pc = &byte_program[0];
	pc = byte_program;

	t = clock(); 

	// printf("[Started]");

	// int offset;
	int opcode;

next_instruction_d:
	opcode = *pc & 0xFF;
	// printf("\t\t");
	// stack_head_show(&sp);
	// printf("\n");

	// printf("%p: [%02x] %s", pc, opcode, labels[opcode]);
	next_instruction_f;

halt_label:
	goto end_label;

jump_label:
	jmp_addr = get_addr(pc);
	// printf(" (+) %04x", jmp_addr);

	pc = byte_program + jmp_addr;
	next_instruction;

jnz_label:
	// arg = *(sp--);
	arg = stack_pop(&sp);

	if (arg.value) {
		jmp_addr = get_addr(pc);
		pc = byte_program + jmp_addr;

		// printf(" (+) %02x", jmp_addr);
	} else { 
		// printf(" (+) 1");

		pc += 3;
	}

	next_instruction;

dup_label:
	offset = *(++pc);

	// arg = *(sp - offset);
	arg = sp.data[sp.count - offset - 1];

	// *(++sp) = arg;
	stack_push(&sp, arg);

	// printf(" (pos) SP-%d", offset);

	pc++;
	next_instruction;

swap_label:
	offset = *(++pc);

	// arg = *(sp - offset);
	arg = sp.data[sp.count - offset - 1];
	// temp = *sp;
	temp = sp.data[sp.count - 1];

	// *sp = arg;
	sp.data[sp.count-1] = arg;
	// *(sp - offset) = temp;
	sp.data[sp.count - offset - 1] = temp;

	pc++;
	next_instruction;

drop_label:
	// sp--;
	stack_pop(&sp);

	pc++;
	next_instruction;

push4:
	default_stack_val.value = *(int32_t *) (++pc);
	// *(++sp) = default_stack_val;
	stack_push(&sp, default_stack_val);

	pc += 4;
	next_instruction;

push2:
	default_stack_val.value = *(int16_t *) (++pc);
	// *(++sp) = default_stack_val;
	stack_push(&sp, default_stack_val);

	pc += 2;
	next_instruction;

push1:
	default_stack_val.value = *(int8_t *) (++pc);
	// *(++sp) = default_stack_val;
	stack_push(&sp, default_stack_val);

	pc++;
	next_instruction;

add_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a+b;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

sub_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a-b;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

mul_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a*b;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

div_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a/b;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

mod_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a%b;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

eq_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a == b ? 1 : 0;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

ne_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a != b ? 1 : 0;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

lt_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a < b ? 1 : 0;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

gt_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a > b ? 1 : 0;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

le_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a <= b ? 1 : 0;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

ge_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = a >= b ? 1 : 0;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

not_label:
	// arg = *(sp--);
	arg = stack_pop(&sp);
	arg.value = !arg.value;

	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

and_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = ((a == 0) | (b == 0)) ? 0 : 1;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

or_label:
	// temp = *(sp--);
	temp = stack_pop(&sp);
	// arg = *(sp--);
	arg = stack_pop(&sp);

	a = arg.value;
	b = temp.value;

	arg.value = ((a == 0) & (b == 0)) ? 0 : 1;
	// *(++sp) = arg;
	stack_push(&sp, arg);

	pc++;
	next_instruction;

input_label:
	printf(" ");
	default_stack_val.value = getchar();
	// *(++sp) = default_stack_val;
	stack_push(&sp, default_stack_val);

	pc++;
	next_instruction;

output_label:
	// arg = *(sp--);
	arg = stack_pop(&sp);

	// printf("\033[0;31m");
	// putchar(arg.value);
	printf("%c", arg.value);
	// printf("\033[0m");

	pc++;
	next_instruction;

clock:
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf(": %0.6lf", time_taken);

	pc++;
	next_instruction;

cons:
	// temp = *(sp--);
	// temp = stack_pop(&sp);
	temp = sp.data[sp.count-1];
	// arg = *(sp--);
	// arg = stack_pop(&sp);
	arg = sp.data[sp.count-2];

	h_entry = (heap_e) {.hd = arg, .tl = temp};
	offset = heap_push(&hp, &sp, h_entry);

	stack_pop(&sp);
	stack_pop(&sp);
	// printf("> [%08x] [%08x] <", h_entry.hd, h_entry.tl);
	// heap_head_show(&hp);

	default_stack_ptr.value = offset;
	// *(++sp) = default_stack_ptr;
	stack_push(&sp, default_stack_ptr);

	pc++;
	next_instruction;

hd:
	// arg = *(sp--);
	arg = stack_pop(&sp);

	if (!(arg.type)) {
		perror("No address");
		exit(1);
	}

	offset = arg.value;
	// printf(" (offset) %04x", offset);

	h_entry = hp.data[offset];
	// *(++sp) = (h_entry.hd);
	stack_push(&sp, h_entry.hd);

	pc++;
	next_instruction;

tl:
	// arg = *(sp--);
	arg = stack_pop(&sp);

	if (!(arg.type)) {
		perror("No address");
		exit(1);
	}

	offset = arg.value;
	// printf(" (offset) %04x", offset);

	h_entry = hp.data[offset];
	// *(++sp) = (h_entry.tl);
	stack_push(&sp, h_entry.tl);

	pc++;
	next_instruction;

nop:
	pc++;
	next_instruction;

end_label:
	stack_free(&sp);
	heap_free(&hp);
	fclose(fp);
	exit(EXIT_SUCCESS);

	return 0;
}