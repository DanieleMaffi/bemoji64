#include <stdio.h>
#include <string.h>
#include "encode.h"


int main(int argc, char** argv) {
	// char buffer[1024];	
	// memset(buffer, 0, sizeof(buffer));
	// while (fgets(buffer, sizeof(buffer), stdin)) {
	//	 printf("Received: %s", buffer);
	// }

	FILE* input_file;

	// Apparently 0 means equal and a negative number shorter
	int is_decode = 0;
	if (argc >= 2 && !strcmp(argv[1], "-d"))
		is_decode = 1;	

	if ((argc == 2 && is_decode) || argc == 1) {
		// fprintf(stderr, "Usage: %s (-d) <input file>\n", argv[0]);
		// return 1;
		input_file = stdin;								
	}
	else {
		input_file = fopen(is_decode ? argv[2] : argv[1], "rb");
		if (!input_file) {
			perror("Failed to open input file");
			return 1;
		}
	}	
		
	is_decode ? decode(input_file) : encode(input_file);
	fclose(input_file);
	
	return 0;
}
