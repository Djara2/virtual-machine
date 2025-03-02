#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define vm_not(x) x & 0x8000000000000000
#define REGISTERS_COUNT 22
#define INTEGER_REGISTERS_COUNT 12
#define FLOATING_POINT_REGISTERS_COUNT 6 
#define SPECIAL_REGISTERS_COUNT 4

// Real CPUs have separate registers and instructions for dealing with floating point values.
// This virtual architecture will do the same. There are...
// - 12 general purpose integer registers
// - 6 floating point registers
// - 4 special registers
enum vm register_id {
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
	
	RA,   // Return address
	RV,   // Return value
	SP,   // Stack pointer
	PC,   // Program counter
	      //
	FP1,  // Floating point Registers
	FP2,  
	FP3,  
	FP4,  
	FP5,
	FP6
};

enum vm_operation {
	COPY,
	SET,
	SETU,
	SETL,
	SETF,

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

union vm_register {
	uint64_t uint64;
	int64_t int64; 

	uint32_t uint32;
	int32_t int32;

	uint16_t uint16;
	int16_t int16;

	uint8_t uint8;
	int8_t int8;

	float f;
	double d;
}; 

// Doing bitwise AND on any number produces 0x8000000000000000 (equal)
// if the other number is negative. Otherwise, it is unequal.
unsigned long NOT_MASK = 0x8000000000000000;
union vm_register registers[22];

// zero initialize registers, prevent bugs
for (uint8_t i = 0; i < 16; i++)
	registers[i].uint64 = 0;

for(uint8_t i = 16; i < REGISTERS_COUNT; i++) 
	registers[i].d = 0;

unsigned long stack[512];

// like "move" in other assemblies 
void copy(enum vm_register_id dest, enum v_register_id r1) {
	// For OK integer setting, dest needs to be in {0..15}
	if(r1 < 16) { 
		if(dest >= 16) {
			fprintf(stderr, "[copy] Cannot copy data from integer register %d to floating point register FP%d.\n", r1, dest - 15);
			exit(EXIT_FAILURE);
		}
		// set value here, figure out using two's complement on register first.
	}
	// Floating point
	else {
		if(dest < 16) {
			fprintf(stderr, "[copy] Cannot copy data from floating point register %d to integer register %d.\n", r1 - 15, dest);
			exit(EXIT_FAILURE);
		}
		registers[dest].d = registers[r1].d;
	}
}

void set(enum v_register dest, void *data, enum primitive type) {
	if(data == NULL) {
		fprintf(stderr, "[set] NULL pointer used for argument \"void *data\". Full instruction was set(%d, NULL, %d)\n", dest, type);
		registers[dest].ulong = 0;
		return;
	}
	// Preemptively update track for register's current value type
	registers[dest].type = type; 		
	// Preemptively zero-out ALL bits so there are no side effects when setting lower bits.
	registers[dest].ulong = 0;	
	switch(type) {
		case ULONG:
			registers[dest].ulong = (uint64_t) (*data);
			break;
		case SLONG:
			registers[dest].slong = (int64_t) (*data);
			break;
		case UINT:
			registers[dest].uint = (uint32_t) (*data);
			break;
		case SINT:
			registers[dest].sint = (int32_t) (*data);
			break;
		case USHORT:
			registers[dest].ushort = (uint16_t) (*data);
			break;
		case SSHORT:
			registers[dest].sshort = (int16_t) (*data);
			break;
		case UCHAR:
			registers[dest].uchar = (uint8_t) (*data);
			break;
		case SCHAR: 
			registers[dest].schar = (int8_t) (*data);
			break;
		case FLOAT:
			registers[dest].f = (float) (*data);
			break;
		case DOUBLE:
			registers[dest].d = (double) (*data);
			break;
		// This case should not be reached, just set to 0
		default:
			registers[dest].ulong = 0; 
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
	union {
		uint32_t i;
		float f;
	} immediate;
};

int main(void) {
	const char *example_instruction = "addr ra r1 r2";
	
	return 0;
}
