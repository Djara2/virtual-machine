#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define vm_not(x) x & 0x8000000000000000

// Doing bitwise AND on any number produces 0x8000000000000000 (equal)
// if the other number is negative. Otherwise, it is unequal.
unsigned long NOT_MASK = 0x8000000000000000;
unsigned long registers[16];

enum v_register {
	GP1,  // General Purpose integer registers
	GP2,  // |
	GP3,  // |
	GP4,  // |
	GP5,  // |
	GP6,  // |
	GP7,  // |
	GP8,  // |
	GP9,  // |
	GP10, // |
	GP11, // |
	GP12, // V
	F1,   // Floating Point Registers 
	F2,
	F3,
	F4,
	RA,   // Return address
	RV,   // Return value
	SP,   // Stack pointer
	PC	
};

enum vm_operation {
	ADDR,
	ADDI,
	ADDFR,
	ADDFI,

	SUBR,
	SUBI, 
	SUBF,

	MULTR,
	MULTI,
	MULTF,

	DIVR,
	DIVI,
	DIVF,

	JUMPN,
	JUMPZ,
	JUMPP,
	JUMPU
};

// Sum of 2 regular registers
void addr(enum v_register dest, enum v_register r1, enum v_register r2) {
	registers[dest] = registers[r1] + registers[r2];
}

// Sum of regular register and an immediate
void addi(enum v_register dest, enum v_register r1, uint32_t i) {
	registers[dest] = registers[r1] + i;
}

// Sum of 2 float registers
void addfr(enum v_register dest_f, enum v_register r1_f, enum v_register r2_f) {
	registers[dest_f] = registers[r1_f] + registers[r2_f];
}

// Sum of a float register and a float immediate 
void addfi(enum v_register dest, enum v_register r1_f, float f) {
	registers[dest_f] = registers[r1_f] + f;
}

void (*operation_table)(enum operation) {
	[ADDR] = addr,
	[ADDI] = addi,
	[ADDF] = addf,
	[SUBR] = subr,
	[SUBI] = subr,
	[SUBF] = subf,

	[MULTR] = multr,
	[MULTI] = multi,
	[MULTF] = multf,

	[DIVR] = divr,
	[DIVI] = divi,
	[DIVF] = divf,

	[JUMPN] = jumpn,
	[JUMPZ] = jumpz,
	[JUMPP] = jumpp,
	[JUMPU] = jumpu 
};

struct instruction {
	enum operation;
	enum v_register dest;
	enum v_register r1;
	enum v_register r2;
	union immediate {
		uint32_t i;
		float f;
	};
};

int main(void) {
	const char *example_instruction = "addr ra r1 r2";
	
	return 0;
}
