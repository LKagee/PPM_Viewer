#pragma once
#define ERROR(a) fprintf(stdout, "ERROR IN PPM READER!: %s", a)
#define SDL_ERROR(a) fprintf(stdout, "ERROR IN SDL!: %s", a)



/* 
 *  ________________________
 * |                        |
 * |	    Structs         |
 * |			    |
 * **************************
 *
 */


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


	// Careful of edianness, P16 = 0x01503136 in 32bit hexadecimal but is stored in reverse order 
	// in memory when in char array;


typedef enum {
 
	P3 = 0x01003350
} HEADER;

typedef struct {

	HEADER headers;
} tokens;


/* 
 *  ________________________
 * |                        |
 * |   Main PPM functions   |
 * |			    |
 * **************************
 *
 * Pipeline for PPM goes: p_setupPPM(&PPM, argv[1]) -> p_readPPM(PPM)
 * 
 * Error Checking: Since each function returns a pointer to NULL if something goes wrong, 
 * checking if the return of the function is NULL is sufficient for error checking, if desired you may print out more error info 
 * and exit the program safely by calling r_quitSDL() depending on where the function call for the failed function was called,
 * or simply continue the program with garbage info, 
 * (in this case the SDL window will likely just stay blank or the program will SEG Fault).
 */



static void* p_setupPPM(ppm* PPM, char* filename) {


	if(PPM == NULL) return NULL;

	PPM->file_ppm = fopen(filename, "r");
	if(PPM->file_ppm == NULL) return NULL;
	
	return PPM;

}

static void* p_readPPM(ppm* PPM) {

	// Not sure if inlining is slowing render speeds or if its something else, 
	// So far, the speeds seem to be slightly faster.
	
	if(PPM->file_ppm == NULL) return NULL;

	fscanf(PPM->file_ppm, "%s", PPM->header);
	int header;
	memcpy(&header, PPM->header, sizeof(int));
	switch(header) {
		case P3: {break;}
		default: ERROR("Invalid file magic number (only P3 is supported)\n"); return NULL; break;
	}


	// WARNING: Lots of if statements...

	if(fscanf(PPM->file_ppm, "%d %d", &PPM->image_width, &PPM->image_height) != 2) { 
		ERROR("Invalid file width and height (ensure .ppm file is ordered [width] [height] immediately under magic number)\n"); 
		return NULL;
	}


	if(!fscanf(PPM->file_ppm, "%d", &PPM->color_max)) {
		ERROR("Invalid maximum color value (must be 0-255 and immediately under width and height)\n");
		return NULL;
	}

	
	if(PPM->color_max > 255 || PPM->color_max < 0) {
		ERROR("Invalid maximum color value (must be 0-255 and immediately under width and height)\n");
		return NULL;

	}

	PPM->vertices = (vec3*)malloc(sizeof(vec3) * PPM->image_height * PPM->image_width);

	for(int i = 0; i < PPM->image_height * PPM->image_width; i++) {

	if(fscanf(PPM->file_ppm, "%d %d %d", &PPM->vertices[i].r, &PPM->vertices[i].g, &PPM->vertices[i].b) != 3) {
		ERROR("Invalid RGB data (must be 0-color_max for each RGB cell and be formatted [R] [G] [B])\n");
		printf("Row: %d\n", i);
	 	return NULL;
	} 
}	

	return PPM;


}












