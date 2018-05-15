typedef unsigned char uns8;
typedef unsigned short uns16;
#include <stdio.h>
#include <stdlib.h>

// PA-1 Part A for Tim Dorny u0829896
// CS 5490

static uns8 state[256], x, y; /* 258 octets of state information */
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
// Encryption method
void encrypt(uns8 * message, uns16 length)
{
    // ignore 512 octets
    int i;
    for (i = 0; i < 512; i++)
    {
        rc4step();
    }
    // Setup output file
    FILE *fp;
    fp = fopen("pa1-a output.txt", "w");
    for (i = 0; i < length; i++)
    {
        // Key byte
        uns8 keyb = rc4step();
        // Message byte
        uns8 mesb = message[i];
        // Cypher byte
        uns8 cypb = mesb ^ keyb;
        // Write encrypted bytes to the output file
        fprintf(fp, "%u\n", cypb);
    }
}

int main(int argc, char *argv[])
{
    // init
    rc4init("mnbvc", 5);
    // encrypt the provided message
    encrypt("This class is not hard at all.", 30);
}
