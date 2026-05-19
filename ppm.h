#pragma once
#define ERROR(a) fprintf(stdout, "ERROR IN PPM READER!: %s", a)
#include <stdint.h>

typedef struct {
	int r, g, b;
} vec3;

typedef struct {

	FILE* file_ppm;
	char header[2];
	int image_width;
	int image_height;
	int color_max;
	vec3* vertices;

} ppm;

	// Careful of edianness, P16 = 0x00503136 in 32bit hexadecimal but is stored in reverse order 
	// in memory when in char array;
typedef enum {
 
	P3 = 0x00003350
} HEADER;

typedef struct {

	HEADER headers;
} tokens;

static /*__attribute__((always_inline))*/ void* read_file(ppm* PPM, tokens* tokenizer) {
	// Not sure if inlining is slowing render speeds or if its something else, 
	// So far, the speeds seem to be slightly faster.
	
	if(PPM->file_ppm == NULL) printf("error");
	PPM->vertices = (vec3*)malloc(sizeof(vec3) * 3);

	fscanf(PPM->file_ppm, "%s", PPM->header);
	int header;
	memcpy(&header, PPM->header, sizeof(int));
	switch(header) {
		case P3: printf("Token: P3\n"); break;
		default: ERROR("Invalid file magic number (only P3 is supported)\n"); return NULL; break;
	}

	// WARNING: Lots of if statements...

	if(fscanf(PPM->file_ppm, "%d %d", &PPM->image_width, &PPM->image_height) != 2) { 
		ERROR("Invalid file width and height (ensure .ppm file is ordered [width] [height] immediately under magic number)\n"); 
		return NULL;
	}

	printf("Width: %d. Height: %d.\n", PPM->image_width, PPM->image_height);

	if(!fscanf(PPM->file_ppm, "%d", &PPM->color_max)) {
		ERROR("Invalid maximum color value (must be 0-255 and immediately under width and height)\n");
		return NULL;
	}

	
	if(PPM->color_max > 255 || PPM->color_max < 0) {
		ERROR("Invalid maximum color value (must be 0-255 and immediately under width and height)\n");
		return NULL;

	}

	printf("Color Max: %d.\n", PPM->color_max);

	if(fscanf(PPM->file_ppm, "%d %d %d", &PPM->vertices[0].r, &PPM->vertices[0].g, &PPM->vertices[0].b) != 3) {
		ERROR("Invalid row 1 RGB data (must be 0-color_max for each RGB cell and be formatted [R] [G] [B])\n");
	 	return NULL;
	}
        printf("RGB: %d %d %d", PPM->vertices[0].r, PPM->vertices[0].g, PPM->vertices[0].b);	

	return PPM;


//	printf("%d", header);
}
