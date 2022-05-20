
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


#define STEP 25

#define TENMAXPOW 9
#define TENPOW9 1000000000
#define TENPOW8 100000000
#define TENPOW7 10000000
#define TENPOW6 1000000
#define TENPOW5 100000
#define TENPOW4 10000
#define TENPOW3 1000
#define TENPOW2 100
#define TENPOW1 10
#define TENPOW0 1


// for division by zero.
static char errorstr[] = "ERROR";

// length of above string
static uint8_t errorstrsize = 5; 

static uint32_t powersof10[10] = {TENPOW0, TENPOW1, TENPOW2, TENPOW3, TENPOW4, TENPOW5, TENPOW6, TENPOW7, TENPOW8, TENPOW9};


// make the log base 10
// function faster
// by making it have
// more dynamic increments.
uint8_t logBase10(uint32_t val)
{


	uint8_t log = 0;


	while (val >= TENPOW9) {

		val /= TENPOW9;
		log += 9;

	}

	while (val >= TENPOW8) {

		val /= TENPOW8;
		log += 8;


	}

	while (val >= TENPOW7) {

		val /= TENPOW7;
		log += 7;

	}

	while (val >= TENPOW6) {

		val /= TENPOW6;
		log += 6;

	}

	while (val >= TENPOW5) {

		val /= TENPOW5;
		log += 5;


	}


	while (val >= TENPOW4) {

		val /= TENPOW4;
		log += 4;

	}


	while (val >= TENPOW3) {

		val /= TENPOW3;
		log += 3;


	}


	while (val >= TENPOW2) {

		val /= TENPOW2;
		log += 2;

	}


	while (val >= TENPOW1) {

		val /= TENPOW1;
		log += 1;

	}

	return log;

}

// calculates powers of ten
uint32_t powOfTen(uint8_t pow)
{


	if (pow <= TENMAXPOW) {

		return powersof10[pow];

	}


	// error code zero for invalid input
	// in the case which overflow occurs 
	// signals that power is not creator than 0
	return 0;

}


// returns a string representation of a rational number which is the result of a division
// of two uint32_ts
void floatStr(char* string, uint8_t buffsize, uint32_t numerator, uint32_t denominator)
{

	if (denominator == 0) {

		
		uint8_t c = 0;

		// errorstrsize is always smaller than buffsize.
		for (c = 0; c < errorstrsize; c++) {

			string[c] = errorstr[c];

		}

		string[c] = '\0';
		return;

	}


	uint8_t power = logBase10(numerator / denominator);

	uint32_t result = numerator / denominator;

	
	// note numdigits is always smaller than
	// the length of the string (even inlcuding the .)
	uint8_t numdigits = 6;
	uint8_t stridx = 0;

	char facevalue = 0;
	
	uint32_t facevalidx = powOfTen(power);

	while (power > 0 && numdigits > 0 && stridx < buffsize) {


		facevalue = (char)(((result / facevalidx) % 10) + '0');
		power--;
		numdigits--;

		string[stridx] = facevalue;
		stridx++;

		facevalidx = powOfTen(power);

	}

	if (numdigits > 0) {

		facevalue = (char)((result % 10) + '0');
		numdigits--;

		if (stridx < buffsize) {

			string[stridx] = facevalue;
			stridx++;

		}

	}

	if (numdigits > 0) {

		facevalue = '.';

		if (stridx < buffsize) {


			string[stridx] = facevalue;
			stridx++;

		}

		

		while (numdigits > 0) {

			numerator *= 10;
			result = numerator / denominator;
			facevalue = (char)((result % 10) + '0');
			numdigits--;

			if (stridx < buffsize) {

				string[stridx] = facevalue;
				stridx++;

			}
			

		}

	}

	string[stridx] = 0;


}


// we use a buffer size of 32 when we only add up to five digits
// plus a dot (in floatStr) so we should have heaps of room.
void percentage(char* string, uint8_t buffsize, uint32_t numerator, uint32_t denominator)
{


	numerator *= 100;
	floatStr(string, buffsize, numerator, denominator);

	uint8_t c;

	// for the added c++ used as the index for the null terminator.
	// And the . and number after the dot.
	for (c = 0; c < buffsize - 3; c++) {

		if (string[c] == '.') {
			c++;
			c++;
			string[c] = '\%';
			c++;
			break;

		}

	}


	string[c] = '\0';

}


int main(int argc, char** argv)
{

	if (argc < 3) {

		printf("Type two numbers\n");
		return 0;

	}


	char string[32] = {0};


	uint32_t num = (uint32_t)atoi(argv[1]);
	uint32_t denom = (uint32_t)atoi(argv[2]);


	floatStr(string, 32, num, denom);

	printf("Expected : %0.5f\n", (float)num / (float)denom);
	printf("Got      : %s\n", string);

	percentage(string, 32, num, denom);

	printf("percent  : %s\n", string);


}


