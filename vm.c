#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define vm_not(x) x & 0x8000000000000000
#define REGISTERS_COUNT 16

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
	COPY,
	SET,

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

enum primitive { 
	ULONG,  SLONG,
	UINT,   SINT,
	USHORT, SSHORT,
	UCHAR,  SCHAR,
	FLOAT,  DOUBLE
};

struct vm_register { 
	union value {
		uint64_t ulong;
		int64_t slong;
		uint32_t uint;
		int32_t sint; 
		uint16_t ushort;
		int16_t sshort;
		uint8_t uchar;
		int8_t schar;
		float f;
		double d;
	};
	enum primitive type;
};

// Doing bitwise AND on any number produces 0x8000000000000000 (equal)
// if the other number is negative. Otherwise, it is unequal.
unsigned long NOT_MASK = 0x8000000000000000;
struct vm_register registers[16];
// zero initialize registers, prevent bugs
for(uint8_t i = 0; i < REGISTERS_COUNT; i++) {
	// 64 bit ulong is the largest member, so this zeros all bits
	registers[i].value.ulong = 0;
	registers[i].type = ULONG;	
}
unsigned long stack[512];

registers[SP] = 0;

// like "move" in other assemblies
void copy(enum v_register dest, enum v_register r1) {
	registers[dest] = registers[r1];
}

void set(enum v_register dest, void *data, enum primitive type) {
	if(data == NULL) {
		fprintf(stderr, "[set] NULL pointer used for argument \"void *data\". Full instruction was set(%d, NULL, %d)\n", dest, type);
		registers[dest].value.ulong = 0;
		return;
	}
	// Preemptively update track for register's current value type
	registers[dest].type = type; 		
	switch(type) {
		case ULONG:
			registers[dest].value.ulong = (*data);
			break;
		case SLONG:
			registers[dest].value.slong = (*data);
			break;
		case UINT:
			registers[dest].value.uint = (*data);
			break;
		case SINT:
			registers[dest].value.sint = (*data);
			break;
		case USHORT:
			registers[dest].value.ushort = (*data);
			break;
		case SSHORT:
			registers[dest].value.sshort = (*data);
			break;
		case UCHAR:
			registers[dest].value.uchar = (*data);
			break;
		case SCHAR: 
			registers[dest].value.schar = (*data);
			break;
		case FLOAT:
			registers[dest].value.f = (*data);
			break;
		case DOUBLE:
			registers[dest].value.d = (*data);
			break;
		// This case should not be reached, just set to 0
		default:
			registers[dest].value.ulong = 0; 
			// Reset to ULONG default type
			registers[dest].type = ULONG; 
			break;
	}
}

// Sum of 2 regular registers
void addr(enum v_register dest, enum v_register r1, enum v_register r2) {
	registers[dest] = registers[r1] + registers[r2];
}

// Sum of regular register and an immediate
void addi(enum v_register dest, enum v_register r1, uint32_t i) {
	registers[dest] = registers[r1] + i;
}

void (*operation_table)(enum operation) {
	[COPY] = copy,
	[SET]  = set,

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
