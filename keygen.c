#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned char byte;

int main() {
	srand(time(NULL));
	
	int keySize = 16;
	byte key[keySize];
	
	printf("Generating key of size %d\n", keySize);
	
	for (int i = 0; i < keySize; i++) {
		key[i] = rand() % 256;
	}
	
	FILE *f = fopen("key.txt", "wb");
	fwrite(key, 1, keySize, f);
	fclose(f);
}