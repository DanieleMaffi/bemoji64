#include <stdio.h>
#include <string.h>
#include "encode.h"


#define BASE 64

const char* set[] = {
	"🗻", "🗼", "🗽", "🗾", "🗿", "😀", "😁", "😂", 
	"😃", "😄", "😅", "😆", "😇", "😈", "😉", "😊", 
	"😋", "😌", "😍", "😎", "😏", "😐", "😑", "😒",
	"😓", "😔", "😕", "😖", "😗", "😘", "😙", "😚", 
	"😛", "😜", "😝", "😞", "😟", "😠", "😡", "😢", 
	"😣", "😤", "😥", "😦", "😧", "😨", "😩", "😪", 
	"😫", "😬", "😭", "😮", "😯", "😰", "😱", "😲", 
	"😳", "😴", "😵", "😶", "😷", "😸", "😹", "😺"
};


unsigned const char find_bemoji_value(const unsigned char* bemoji) {
	for (int i = 0; i < BASE; i++)
		if (!strcmp(set[i], bemoji))
			return i;
}

void decode(FILE* file) {
	printf("Not implemented yet :(\n");
}

/*
void decode(FILE* file) {
	printf("Decoding...\n");

	const unsigned char* buffer[4];
	unsigned char decoded[3];
	size_t bytes_read;	

	while (bytes_read = fread(buffer, 1, 4, file) > 0) {
		for (int i = 0; i < 4; i++)
			buffer[i] = &(find_bemoji_value(buffer[i]));
		
		decoded[0] = (buffer[0] << 2) | (buffer[1] >> 4);
		decoded[1] = (buffer[1] << 4) | (buffer[2] >> 2);
		decoded[2] = (buffer[2] << 6) | buffer[3];
	}

	printf("\n---------------------------- DECODING DONE ----------------------------\n");
}*/

void encode(FILE* file) {
	// printf("Encoding...\n");

	unsigned char buffer[3];
	unsigned const char* encoded[4];
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, 3, file)) > 0) {
		encoded[0] = set[buffer[0] >> 2];
		encoded[1] = set[((buffer[0] & 0x03 << 4) | (buffer[1] >> 4))];
		encoded[2] = (bytes_read > 1) ? set[((buffer[1] & 0x0F << 2) | (buffer[2] >> 6))] : "=";
		encoded[3] = (bytes_read > 2) ? set[buffer[2] & 0x3F] : "=";
		
		for (int i = 0; i < 4; i++)
			printf("%s", encoded[i]);	

	}
	
	// printf("\n---------------------------- ENCODING DONE ----------------------------\n");
}
