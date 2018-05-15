typedef unsigned char uns8;
typedef unsigned short uns16;
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// PA-1 Part B for Tim Dorny u0829896
// CS 5490

// RC4 for substitution tables
static uns8 state[256], x, y, st1a[256], st1b[256], st2a[256], st2b[256], st3a[256], st3b[256], st4a[256], st4b[256], st5a[256], st5b[256], st6a[256], st6b[256], st7a[256], st7b[256], st8a[256], st8b[256]; /* 258 octets of state information */
void rc4init (key, length) /* initialize for encryption / decryption */
uns8 *key;
uns16 length;
{
    int i;
    uns8 t;
    uns8 j;
    uns8 k = 0;
    for (i = 256; i--; )
        state[i] = i;
    for (i = 0, j = 0; i < 256; i++, j = (j + 1) % length)
        t = state[i], state[i] = state[k += key[j] + t], state[k] = t;


    x = 0;
    y = 0;
}


uns8
rc4step () /* return next pseudo-random octet */
{
    uns8 t;


    t = state[y += state[++x]], state[y] = state[x], state[x] = t;
    // To fix the bug, I added the modulus to ensure
    // the array doesn't get indexed out of bounds
    return (state[(state[x] + state[y]) % 256]);
}

// Creates the state tables using the RC4 random octets (not refined sorry)
void state_table_init(){
    int i;
    for (i = 0; i < 256; i++){
		int val = rc4step();
        st1a[i] = val;
		st1b[val] = i;
    }
	for (i = 0; i < 256; i++){
		int val = rc4step();
        st2a[i] = val;
		st2b[val] = i;
    }
	for (i = 0; i < 256; i++){
		int val = rc4step();
        st3a[i] = val;
		st3b[val] = i;
    }
	for (i = 0; i < 256; i++){
		int val = rc4step();
        st4a[i] = val;
		st4b[val] = i;
    }
	for (i = 0; i < 256; i++){
		int val = rc4step();
        st5a[i] = val;
		st5b[val] = i;
    }
	for (i = 0; i < 256; i++){
		int val = rc4step();
        st6a[i] = val;
		st6b[val] = i;
    }
	for (i = 0; i < 256; i++){
		int val = rc4step();
        st7a[i] = val;
		st7b[val] = i;
    }
	for (i = 0; i < 256; i++){
		int val = rc4step();
        st8a[i] = val;
		st8b[val] = i;
    }
}
//assumes little endian
//void printBits(size_t const size, void const * const ptr)
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
// bitwise circular shifts an array to the left
void shift_left(void *object, size_t size)
{
   unsigned char *byte;
   for ( byte = object; size--; ++byte )
   {
      unsigned char bit = 0;
      if ( size )
      {
         bit = byte[1] & (1 << (7)) ? 1 : 0;
      }
      *byte <<= 1;
      *byte  |= bit;
   }
}
// bitwise circular shifts an array to the right
void shift_right(void *object, size_t size)
{
   unsigned char *byte;
   for ( byte = object; size--; ++byte )
   {
      unsigned char bit = 0;
      if ( size )
      {
         bit = byte[1] & (1) ? 1 : 0;
      }
      *byte >>= 1;
      *byte  |= bit;
   }
}
int main(int argc, char *argv[]){

    // Init RC4 for substitution table building
    rc4init("pleasework", 5);
    // ensure that a message is passed
    if (argc < 2){
        printf("Program requires an argument!\n");
        return;
    }
	// Setup output file
    FILE *fp;
    fp = fopen("pa1-b output.txt", "w");
    // input message
    uns8 * input = argv[1];
    printf("Input: %s\n", input);
	// Write input value to the output file
    fprintf(fp, "Input: %s\n", input);
    // Populate the tables with random octets
    state_table_init();
    // "password" key
    uns8 * key = "password";
    // Step 1: Take input and xor it with the key
    uns8 outputarr[8];
    int i;
    for (i = 0; i < 8; i++){
		printf("input : %u  ... key: %u\n", input[i], key[i]);
        outputarr[i] = input[i] ^ key[i];
    }
	//uns8 * output2 = outputarr;
	printBits(sizeof(outputarr), &outputarr);
	//printf("YO: %u\n", output2);
    // Step 2: Use output of step 1 to perform character by character
    // substitution using the substitution tables.
    outputarr[0] = st1a[outputarr[0]];
    outputarr[1] = st2a[outputarr[1]];
    outputarr[2] = st3a[outputarr[2]];
    outputarr[3] = st4a[outputarr[3]];
    outputarr[4] = st5a[outputarr[4]];
    outputarr[5] = st6a[outputarr[5]];
    outputarr[6] = st7a[outputarr[6]];
    outputarr[7] = st8a[outputarr[7]];
	unsigned long output = (unsigned long)outputarr;
	//printf("YO: %u\n", output[0]);
	printBits(sizeof(outputarr), &outputarr);
    // Step 3: Circular shift Left
	shift_right(outputarr, sizeof(outputarr));
	shift_right(outputarr, sizeof(outputarr));
	printBits(sizeof(outputarr), &outputarr);
	// Repeat Cycle 15 times, with output of each cycle serving as the input.
	int j;
	for (j = 0; j < 15; j++){
		// Write per round encrypted output to the output file
    	fprintf(fp, "Round %d Encryption Output: %u, %u, %u, %u, %u, %u, %u, %u\n", j + 1, outputarr[0], outputarr[1], outputarr[2], outputarr[3], outputarr[4], outputarr[5], outputarr[6], outputarr[7]);
		//input = outputarr;	
		// Step 1
		for (i = 0; i < 8; i++){
			//printf("input : %u  ... key: %u\n", input[i], key[i]);
        	outputarr[i] = outputarr[i] ^ key[i];
    	}
		// Step 2
		outputarr[0] = st1a[outputarr[0]];
    	outputarr[1] = st2a[outputarr[1]];
    	outputarr[2] = st3a[outputarr[2]];
    	outputarr[3] = st4a[outputarr[3]];
    	outputarr[4] = st5a[outputarr[4]];
    	outputarr[5] = st6a[outputarr[5]];
    	outputarr[6] = st7a[outputarr[6]];
    	outputarr[7] = st8a[outputarr[7]];
		// Step 3
		shift_left(outputarr, sizeof(outputarr));
	}

	// Decrypt
	for (j = 0; j < 16; j++){
		// Step 3
		shift_left(outputarr, sizeof(outputarr));
		// Step 2
		outputarr[0] = st1b[outputarr[0]];
    	outputarr[1] = st2b[outputarr[1]];
    	outputarr[2] = st3b[outputarr[2]];
    	outputarr[3] = st4b[outputarr[3]];
    	outputarr[4] = st5b[outputarr[4]];
    	outputarr[5] = st6b[outputarr[5]];
    	outputarr[6] = st7b[outputarr[6]];
    	outputarr[7] = st8b[outputarr[7]];	
		// Step 1
		for (i = 0; i < 8; i++){
			//printf("input : %u  ... key: %u\n", input[i], key[i]);
        	outputarr[i] = outputarr[i] ^ key[i];
    	}
		
		// Write per round decrypted output to the output file
    	fprintf(fp, "Round %d Decryption Output: %u, %u, %u, %u, %u, %u, %u, %u\n", j + 1, outputarr[0], outputarr[1], outputarr[2], outputarr[3], outputarr[4], outputarr[5], outputarr[6], outputarr[7]);
	}

}
