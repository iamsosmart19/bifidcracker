#include "sigint.h"

void sig_handler(int signo) {
	  if (signo == SIGINT) {
		  char cwd[PATH_MAX];
		  FILE* keyfile;
		  printf("Saving Key...\n");
		  getcwd(cwd, sizeof(cwd));
		  strcat(cwd, "/plaintext.txt");
		  keyfile = fopen(cwd, "w");
		  fprintf(keyfile, "Key: %s\nPlaintext: %s", key, out);
		  printf("Key & plaintext saved to %s/plaintext.txt\n", cwd);
		  exit(0);
	  }
}
