#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_POW (27)
#define MIN_POW (4)

typedef unsigned char byte;

int main(int argc, char **argv) {
	srand(time(NULL));
	
	int power = atoi(argv[1]);
	if (power > MAX_POW) {
		power = MAX_POW;
	} else if (power < MIN_POW) {
		power = MIN_POW;
	}
	
	unsigned int payloadSize = 1 << power;
	byte *buffer = (byte *) malloc(sizeof(byte) * payloadSize);
	
	printf("Generating payload of size %d\n", payloadSize);
	
	for (unsigned int i = 0; i < payloadSize; i++) {
		buffer[i] = rand() % 256;
	}
	
	FILE *f = fopen("payload.txt", "wb");
	fwrite(buffer, 1, payloadSize, f);
	fclose(f);
	
	free(buffer);
}