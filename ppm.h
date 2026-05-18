#pragma once
#define ERROR(a) printf("ERROR IN PPM READER!: %s", a);
#include <stdint.h>


typedef struct {

	FILE* file_ppm;
	char header[2];
	int image_width;
	int image_height;
	int color_max;
	int* vertices;

} ppm;

// Careful of edianness, P16 = 0x00503136 in 32bit hexadecimal but is stored in reverse order 
// in memory when in char array;
typedef enum {
 
	P16 = 0x00363150
} HEADER;

typedef struct {

	HEADER headers;
} tokens;

static __attribute__((always_inline)) void read_file(ppm* PPM, tokens* tokenizer) {
	
	if(PPM->file_ppm == NULL) printf("error");

	fscanf(PPM->file_ppm, "%s", PPM->header);
	int header;
	memcpy(&header, PPM->header, sizeof(int));
	switch(header) {
		case P16: printf("Token: P16\n"); break;
		default: break;
	}

//	printf("%d", header);
}
