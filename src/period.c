#include "period.h"

int period(FILE* ciphertext) {
	char* buff;
	int count[26][26];
	memset(count, 0, sizeof(int) * 26 * 26);

	fseek(ciphertext, 0L, SEEK_END);
	int textlength = ftell(ciphertext);
	buff = (char*) malloc(sizeof(char) * textlength);
	rewind(ciphertext);
	fgets(buff, textlength, (FILE*) ciphertext);
	//strcpy(buff, "ABCDEFGHIJK\0");
	//printf("%s, %d\n", buff, strlen(buff));
	setlocale(LC_CTYPE, "");

	int length = strlen(buff) - strlen(buff) % 2;
	int steps = 128;
	float* variance = (float*) malloc(steps*sizeof(float));

	for(int i = 1; i < steps+1; i++) {
		for(int j = 0; j < length-i; j++) {
			count[buff[j]-65][buff[j+i]-65]++;
			//printf("%c%c ", buff[j], buff[j+i]);
		}
		variance[i-1] = findVar(count);
		memset(count, 0, sizeof(int) * 26 * 26);
	}

	int temp[2] = {0, 0};
	for(int i = 1; i < steps; i++) {
		if(variance[i] > variance[temp[0]]) {
			if(variance[i] > variance[temp[1]]) {
				temp[1] = i;
			}
			else {
				temp[0] = i;
			}
		}
		printf("%d: %f\t",i+1,variance[i]);
		printFloat(variance[i], 2);
		printf("\n");
	}
	//printf("%d, %d\n", temp[0]+1, temp[1]+1);
	free(variance);
	free(buff);
	rewind(ciphertext);
	if(temp[0] == temp[1]-1 || temp[0]-1 == temp[1]) {
		printf("The period is: %d\n", temp[0]+temp[1]+2);
		return temp[0]+temp[1]+2;
	}
	else {
		printf("period is: %d\n", (MAX(temp[0],temp[1])+1) * 2);
		return (MAX(temp[0], temp[1]) + 1) * 2;
	}
}

float findVar(int count[26][26]) {
	float var = 0;
	float avg = 0;
	int sum = 0;
	int n = 0;
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j < 26; j++) {
			if(count[i][j] == 0) {
				continue;
			}
			n++;
			sum += count[i][j];
		}
	}
	if(n==0) {
		return 0;
	}
	//printf(" n: %d, sum: %d", n, sum);
	avg = sum / n;
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j < 26; j++) {
			if(count[i][j] == 0) {
				continue;
			}
			var += pow(avg - (float)count[i][j], 2);
		}
	}
	var = var/n;
	return var;
}

void printFloat(float value, int accuracy) {
	float rem = value - (int) value;
	wchar_t block = 0x2587;
	for(int i = 0; i < (int)value * pow(2, accuracy-1); i++) {
		printf("%lc",block);
	}
	for(int i = 1; i < accuracy; i++) {
		if(rem >= (float)(1/(pow(2,i)))) {
			rem -= (float)(1/pow(2,i));
			for(int j = 0; j < pow(2, accuracy-i-1); j++) {
				printf("%lc",block);
			}
		}
	}
	block++;
	for(int i = 7; i >= 1; i--) {
		if(rem >= (float)(i/(pow(2,(accuracy+2))))) {
			printf("%lc", block);
			break;
		}
		block++;
	}
}

float findP(int count[26][26]) {
	int n = 0;
	int prop = 0;
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j < 26; j++) {
			if(count[i][j] == 0) {
				continue;
			}
			n++;
			if(i == j) {
				prop++;
			}
		}
	}
	//printf("n: %d, prop: %d\n", n, prop);

	return 100*(float)prop/(float)n;
}
