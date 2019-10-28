#ifndef BIFIDCRACK_H
#define BIFIDCRACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "scoreText.h"

#define TEMP 20
#define STEP 0.1
#define COUNT 10000

char *bifidDecipher(char *key, int period, char *in,char *out, int len);
float bifidCrack(char *text,int len, char* maxKey, int period);
static char *shuffleKey(char *in);

int bifidMain(FILE* ciphertext, int period);

void exchange2letters(char *key);
float bifidCrack(char *text,int len, char* bestKey, int period);

#endif /*BIFIDCRACK_H*/

