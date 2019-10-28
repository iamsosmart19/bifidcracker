#include <unistd.h>

#include "bifidcrack.h"
#include "period.h"

int main(int argc, char* argv[]) {
	if(argc <= 1) {
		fprintf(stderr, "Error: No file provided\n");
		return 1;
	}
	if(access(argv[1], F_OK) == -1) {
		fprintf(stderr, "Error: File not found\n");
		return 1;
	}
	FILE* ciphertext;
	ciphertext = fopen(argv[1], "r");
	char check;
	while(1) {
		check == fgetc(ciphertext);
		if(check == EOF || check == '\0') {
			break;
		}
		if( check < 65 || check > 90 || check == 'J') {
			fprintf(stderr, "Error: Invalid character %c: check that all characters are lowercase, there are no spaces, and no 'J's\n", check);
			return 1;
		}	   
	}
	rewind(ciphertext);
	bifidMain(ciphertext, period(ciphertext));
}
