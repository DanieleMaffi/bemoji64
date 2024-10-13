#include <stdio.h>
#include <string.h>
#include "encode.h"


int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s (-d) <input file>\n", argv[0]);
		return 1;								
	}

	// Apparently 0 means equal and a negative number shorter
	int is_decode = 0;
	if (!strcmp(argv[1], "-d") && argc == 3)
		is_decode = 1;

	FILE* input_file = fopen(is_decode ? argv[2] : argv[1], "rb");
	if (!input_file) {
		perror("Failed to open input file");
		return 1;
	}
	
	is_decode ? decode(input_file) : encode(input_file);
	fclose(input_file);
	
	return 0;
}
