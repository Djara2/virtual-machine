#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	if(argc < 2) { 
		fprintf(stderr, "Provide a number.\n");
		return 1;
	} 

	unsigned long char_bitmask = 0xFFFFFFFFFFFFFF00;
	unsigned long short_bitmask = 0xFFFFFFFFFFFF0000;
	unsigned long int_bitmask = 0xFFFFFFFF00000000;
	
	long number = atol(argv[1]);
	if( (number & char_bitmask) == 0) 
		printf("%c is a char.\n", (char) number);

	else if( (number & short_bitmask) == 0) 
		printf("%hd is a short.\n", (short) number);

	else if( (number & int_bitmask) == 0) 
		printf("%d is an int.\n", (int) number);

	else 
		printf("%ld is a long.\n", number); 

	return 0;
}
