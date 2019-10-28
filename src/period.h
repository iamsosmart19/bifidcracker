#ifndef PERIOD_H
#define PERIOD_H
#define MAX( a, b ) ( ( a > b) ? (a) : (b) ) 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

int period(FILE* ciphertext);

float findVar(int count[26][26]);

void printFloat(float value, int accuracy);

float findP(int count[26][26]);
#endif /*PERIOD_h*/
