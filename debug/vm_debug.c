#include "lib/common.h"
#include "lib/bytecode.h"

#define next_instruction \
	goto next_instruction2

#define next_instruction3 \
	goto *(void *)(label_tab[*pc])

#define get_addr(pc) \
	(*(pc+1) & 0xFF) | (*(pc+2) << 8)

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
		&&clock
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
	stack_tt * stack;
	stack = (stack_tt *) malloc(STACK_SIZE * sizeof(stack_t));

// --------------------------------
	byte * pc;
	// byte opcode;
	stack_tt * sp;
	addr jmp_addr;

	stack_tt arg, sarg,temp;
	stack_tt a,b;

	clock_t t; 
	double time_taken;
// --------------------------------

	// pc = &byte_program[0];
	pc = byte_program;
	// sp = &stack[0];
	sp = stack;

	// stack[0] = 0x0a;
	// stack[1] = 0x0a;
	// // stack[2] = 0xff;
	// sp += 1;

	// printf("stack at 1\n", *(sp-1));
	t = clock(); 

	printf("[Started]");

	// opcode = pc[0];
	// printf(">> Let's begin: %02x\n", opcode);
next_instruction2:
	printf("\t | [%08x]", *(sp));
	printf("\n");
	next_instruction3;

halt_label:
	goto end_label;

jump_label:
	// printf("Hell yeah\n");
	jmp_addr = get_addr(pc);
	// printf("%04x\n", jmp_addr);
	printf("%p: jmp_label (+) %04x", (pc), jmp_addr);

	pc = byte_program + jmp_addr;
	next_instruction;

jnz_label:
	printf("%p: jnz_label ", (pc));
	arg = *(sp--);

	if (arg) {
		// printf("I am here\n");
		jmp_addr = get_addr(pc);
		// printf("%04x\n", jmp_addr);
		pc = byte_program + jmp_addr;

		printf("(+) %02x", jmp_addr);
	} else { 
		printf("(+) 1");

		pc += 3;
	}

	next_instruction;

dup_label:
	printf("%p: dup_label", pc);
	// printf("Before\n");
	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %02x\n", *(sp-i));
	// }

	// printf("Iam here\n");
	arg = *(++pc);
	// printf("Dup stack - %02x\n", arg);
	sarg = *(sp - arg);
	// printf("sarg %02x\n", sarg);
	*(++sp) = sarg;

	// printf("yoyo %02x\n", stack[2]);
	printf(" (pos) SP-%d", arg);
	// printf("After\n");
	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %08x\n", *(sp-i));
	// }

	pc++;
	next_instruction;

swap_label:
	printf("%p: swap_label", pc);
	// printf("%02x %02x %02x \n", stack[0], stack[1], stack[2]);
	arg = *(++pc);
	// printf("Swap head with (stack - %02x)\n", arg);
	sarg = *(sp - arg);
	// printf("sarg %02x\n", sarg);

	temp = *sp;
	*sp = sarg;
	*(sp - arg) = temp;

	// printf("%02x %02x %02x \n", stack[0], stack[1], stack[2]);
	pc++;
	next_instruction;

drop_label:
	printf("%p: drop_label", pc);
	// printf("%02x %02x %02x \n", stack[0], stack[1], stack[2]);
	// printf("Before %02x\n", *sp);
	sp--;
	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %02x\n", *(sp-i));
	// }
	// printf("After %02x\n", *sp);
	pc++;
	next_instruction;

push4:
	printf("%p: push4", pc);

	*(++sp) = *(int32_t *) (++pc);

	// printf("\t %08x\n", *(sp));

	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %08x\n", *(sp-i));
	// }

	pc += 4;
	next_instruction;

push2:
	printf("%p: push2", pc);

	*(++sp) = *(int16_t *) (++pc);

	// printf("\t %08x\n", *(sp));

	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %08x\n", *(sp-i));;
	// }

	pc += 2;
	next_instruction;

push1:
	printf("%p: push1", pc);

	*(++sp) = *(int8_t *) (++pc);

	// printf("\t %08x\n", *(sp));

	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %08x\n", *(sp-i));
	// }

	pc++;
	next_instruction;


add_label: //9
	printf("%p: add_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a+b;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;


sub_label: //0a
	printf("%p: sub_label", pc);

	// printf("Before\n");
	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %08x\n", *(sp-i));
	// }

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a-b;

	// printf("After\n");
	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %08x\n", *(sp-i));
	// }

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

mul_label: //0b
	printf("%p: mul_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a*b;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

div_label: //0c
	printf("%p: div_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a/b;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

mod_label: //0d
	printf("%p: mod_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a % b;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

eq_label: //0e
	printf("%p: eq_label", pc);

	// printf("Before\n");
	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %08x\n", *(sp-i));
	// }

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp);

	*(sp) = a == b ? 1 : 0;

	// printf("After\n");
	// for (int i = 0; i < 3; ++i)
	// {
	// 	printf("\t %08x\n", *(sp-i));
	// }
	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

ne_label: //0f
	printf("%p: ne_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a != b ? 1 : 0;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

lt_label: //10
	printf("%p: lt_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a < b ? 1 : 0;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

gt_label: //11
	printf("%p: gt_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a > b ? 1 : 0;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

le_label: //12
	printf("%p: le_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a <= b ? 1 : 0;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

ge_label: //13
	printf("%p: ge_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = a >= b ? 1 : 0;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

not_label: //14
	printf("%p: not_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);

	*(++sp) = !b;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

and_label: //15
	printf("%p: and_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = ((a == 0) | (b == 0)) ? 0 : 1;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

or_label: //16
	printf("%p: or_label", pc);

	// printf("%02x %02x\n", stack[0], stack[1]);
	b = *(sp--);
	a = *(sp--);

	*(++sp) = ((a == 0) & (b == 0)) ? 0 : 1;

	// printf("%02x %02x\n", stack[0], stack[1]);
	pc++;
	next_instruction;

input_label://17
	printf("%p: input_label PC", pc);

	printf("\t [Input] ");
	// printf("-- %02x\n", stack[2]);
	*(++sp) = getchar();
	// printf("-- %02x\n", stack[2]);

	pc++;
	next_instruction;

output_label://18
	printf("%p: output_label", pc);

	arg = *(sp--);
	printf("\t [Output] ");
	putchar(arg);
	// printf("\n");

	pc++;
	next_instruction;

clock:
	printf("%p: clock_label", pc);

	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf(": %0.6lf", time_taken);

	pc++;
	next_instruction;

nop: //
	printf("%p: nop PC", pc);

	pc++;
	next_instruction;

end_label:
	free(stack);
	free(byte_program);
	fclose(fp);
	exit(EXIT_SUCCESS);

	return 0;
}