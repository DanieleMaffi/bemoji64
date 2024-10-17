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

/**
 * Decodes a 4-byte UTF-8 encoded character into an integer representing an emoji.
 *
 * @param encoded  An array of 4 bytes representing a UTF-8 encoded character.
 * @param size     The size of the encoded character (always 4 bytes in this case).
 * @return         An integer representing the decoded emoji.
 */
int decode_utf8_character(const unsigned char encoded[], size_t size) {
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

/**
 * Finds the index of the Base64-like emoji set corresponding to a given emoji.
 *
 * @param bemoji   The integer value of the emoji (from UTF-8 decoding).
 * @return         The index of the emoji in the set array, or padding_position if not found.
 */
int find_bemoji_value(int bemoji) {
	for (int i = 0; i < BASE; i++)
		if (decode_utf8_character((unsigned char*)set[i], 4) == bemoji)
			return i;
	return padding_position;
}

/**
 * Decodes a Base64-like encoded input stream from a file and prints the decoded characters.
 *
 * @param file  The input file pointer containing the encoded data.
 */
void decode(FILE* file) {
	unsigned char buffer[4 * 4];
	unsigned char decoded[3];
	int positions[4];
	size_t bytes_read;	
	int emoji, decoded_number;	

	while ((bytes_read = fread(buffer, 4, 4, file)) > 0) {
		decoded_number = 0;
		for (int i = 0; i < 4; i++) {	
			emoji = decode_utf8_character(buffer + i * 4, 4);
			positions[i] = find_bemoji_value(emoji);
		}
	
		decoded[0] = (positions[0] << 2) | (positions[1] >> 4 & 0x03);
		decoded[1] = (positions[1] << 4) | ((positions[2] >> 2) & 0x0F);
		decoded[2] = ((positions[2] & 0x03) << 6) | positions[3];

		if (positions[3] == padding_position) decoded_number = 2;
        	if (positions[2] == padding_position) decoded_number = 1;
		
		for (int i = 0; i < 3 - decoded_number; i++)
			printf("%c", decoded[i]);
	}	

	printf("\n");
}

/**
 * Encodes input data from a file into Base64-like format using emojis and prints the encoded output.
 *
 * @param file  The input file pointer containing the raw data to be encoded.
 */
void encode(FILE* file) {
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
}
