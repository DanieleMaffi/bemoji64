#include <stdio.h>
#include <string.h>
#include <math.h>
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
	"😳", "😴", "😵", "😶", "😷", "😸", "😹", "😺",
	"👾"
};

const int padding_position = 64;


int decode_utf8_character(const unsigned char encoded[]) {
	unsigned char digits[6];

	digits[5] = (encoded[0] & 4) >> 2;
	digits[4] = ((encoded[0] & 3) << 2) | ((encoded[1] >> 4) & 3);
	digits[3] = encoded[1] & 15;
	digits[2] = (encoded[2] >> 2) & 15;
	digits[1] = ((encoded[2] & 3) << 2) | ((encoded[3] >> 4) & 3);
	digits[0] = encoded[3] & 15;
	
	int emoji = 0;
	for (int i = 0; i < 5; i++)
		emoji += pow(16, i) * digits[i];
	return emoji;
}

int find_bemoji_value(int bemoji) {
	for (int i = 0; i < BASE; i++)
		if (decode_utf8_character((unsigned char*)set[i]) == bemoji)
			return i;
	return padding_position;
}

void decode(FILE* file) {
	// printf("Decoding...\n");

	unsigned char buffer[4];
	unsigned char decoded[3];
	size_t bytes_read;	
	int emoji, position;	

	while ((bytes_read = fread(buffer, 1, 4, file)) > 0) {
		// if (bytes_read != 4)
		// 	break;
		emoji = decode_utf8_character(buffer);
		position = find_bemoji_value(emoji);
		printf("Decoded position: %d, emoji: %d: %s\n", position, emoji, set[position]);
	}	

	// printf("\n---------------------------- DECODING DONE ----------------------------\n");
}

void encode(FILE* file) {
	// printf("Encoding...\n");

	unsigned char buffer[3];
	const char* encoded[4];
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, 3, file)) > 0) {
		encoded[0] = set[buffer[0] >> 2];
		encoded[1] = set[(((buffer[0] & 0x03) << 4) | (buffer[1] >> 4))];
		encoded[2] = (bytes_read > 1) ? set[(((buffer[1] & 0x0F) << 2) 
			   | (buffer[2] >> 6))] : set[padding_position];
		encoded[3] = (bytes_read > 2) ? set[buffer[2] & 0x3F] : set[padding_position];
		
		for (int i = 0; i < 4; i++)
			printf("%s", encoded[i]);	

	}
	
	printf("\n");
	// printf("\n---------------------------- ENCODING DONE ----------------------------\n");
}
