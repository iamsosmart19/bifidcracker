#include "bifidcrack.h"

int bifidMain(FILE* ciphertext, int period) {
    char* cipher;
	fseek(ciphertext, 0L, SEEK_END);
	int length = ftell(ciphertext);
	cipher = (char*) malloc(sizeof(char) * length);
	rewind(ciphertext);
	fgets(cipher, length, ciphertext);
	//printf("%s\n", cipher);
    int len = strlen(cipher);  
    char *out = malloc(sizeof(char)*(len+1));
    srand((unsigned)time(NULL)); // randomise the seed, so we get different results each time we run this program

    printf("Running bifidcrack, this could take a few minutes...\n");

    char key[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    int i=0;
    double score,maxscore=-99e99;
    // run until user kills it
    while(1){
        i++;
        score = bifidCrack(cipher,len,key, period);
        if(score > maxscore){
            maxscore = score;
            printf("best score so far: %f, on iteration %d\n",score,i);
            printf("    Key: '%s'\n",key);
            bifidDecipher(key, period, cipher,out, len);
            printf("    plaintext: '%s'\n",out);
        }
    }
    free(out);
    return 0;
}

void exchange2letters(char *key){
    int i = rand()%25;
    int j = rand()%25;
    char temp = key[i];
    key[i]= key[j];
    key[j] = temp;
}

// this is the bit that implements the simulated annealing algorithm 
float bifidCrack(char *text,int len, char* bestKey, int period){
    int i,j,count;
    float T;
    char temp, *deciphered = malloc(sizeof(char) * (len+1));
    char testKey[26];
    char maxKey[26];
    double prob,dF,maxscore,score;
    double bestscore;
    strcpy(maxKey,bestKey);
    bifidDecipher(maxKey, period,text,deciphered,len);
    maxscore = scoreTextQgram(deciphered,len);
    bestscore = maxscore;
    for(T = TEMP; T >= 0; T-=STEP){
        for(count = 0; count < COUNT; count++){ 
            strcpy(testKey,maxKey);
            exchange2letters(testKey);
            bifidDecipher(testKey, period,text,deciphered,len);
            score = scoreTextQgram(deciphered,len);
            dF = score - maxscore;
            if (dF >= 0){
                maxscore = score;
                strcpy(maxKey,testKey);
            }else if(T > 0){
                prob = exp(dF/T);
                if(prob > 1.0*rand()/RAND_MAX){
                    maxscore = score;
                    strcpy(maxKey,testKey);
                }
            }
            // keep track of best score we have seen so far
            if(maxscore > bestscore){
                bestscore = maxscore;
                strcpy(bestKey,maxKey);
            }
        }
    }
    free(deciphered);
    return bestscore;
}


char *bifidDecipher(char *key, int period, char *text, char *result, int len){
    int i, j;
    char a,b; /* the digram we are looking at */
    int a_ind,b_ind;
    int a_row,b_row;
    int a_col,b_col;
    
    for (i = 0; i < len; i += period){
        if (i + period > len){
            period = len - i;
        }
        for (j = 0; j < period; j ++){
            a = text[i+(j/2)];
            b = text[i+((period+j)/2)];

            /*if (index(key,a) == NULL || index(key,b) == NULL) break;*/
            a_ind = (int)(index(key,a) - key);
            b_ind = (int)(index(key,b) - key);
            a_row = a_ind / 5;
            b_row = b_ind / 5;
            a_col = a_ind % 5;
            b_col = b_ind % 5;
			if(period % 2 == 1) {
				if (j % 2 == 0){
					result[i+j] = key[5*a_row + b_col];
				} else {
					result[i+j] = key[5*a_col + b_row];
				}
			}
			else {
				if (j % 2 == 0){
					result[i+j] = key[5*a_row + b_row];
				} else {
					result[i+j] = key[5*a_col + b_col];
				}
			}
        }
    }
    result[i] = '\0';
    return result;
}

// do fisher yeates shuffle      
static char *shuffleKey(char *in){
    int i,j;
    char temp;
    for (i = 24; i >= 1; i--){
        j = rand() % (i+1);
        temp = in[j];
        in[j] = in[i];
        in[i] = temp;
    }
    return in;
} 


