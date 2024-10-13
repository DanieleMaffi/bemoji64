#include <stdio.h>
#include "encode.h"


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


int main(int argc, char** argv) {
	
	printf("This is a test beacuse emojis in C are strings apparently: %s\n", set[2]);

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
		return 1;								
	}
	
	FILE* input_file = fopen(argv[1], "rb");
	if (!input_file) {
		perror("Failed to open input file");
		return 1;
	}
	fclose(input_file);
	
	encode();

	printf("---------------------------- ENCODING DONE ----------------------------\n");

	return 0;
}
