#pragma once
#define ERROR(a) fprintf(stdout, "ERROR IN PPM READER!: %s", a)
#define SDL_ERROR(a) fprintf(stdout, "ERROR IN SDL!: %s", a)
#include <stdint.h>
#include "main.h"


static /*__attribute__((always_inline))*/ void* read_file(ppm* PPM, tokens* tokenizer) {
	// Not sure if inlining is slowing render speeds or if its something else, 
	// So far, the speeds seem to be slightly faster.
	
	if(PPM->file_ppm == NULL) printf("error");

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
	PPM->vertices = (vec3*)malloc(sizeof(vec3) * PPM->image_height * PPM->image_width);

	for(int i = 0; i < PPM->image_height * PPM->image_width; i++) {

	if(fscanf(PPM->file_ppm, "%d %d %d", &PPM->vertices[i].r, &PPM->vertices[i].g, &PPM->vertices[i].b) != 3) {
		ERROR("Invalid RGB data (must be 0-color_max for each RGB cell and be formatted [R] [G] [B])\n");
		printf("Row: %d\n", i);
	 	return NULL;
	}
        printf("RGB: %d %d %d\n", PPM->vertices[i].r, PPM->vertices[i].g, PPM->vertices[i].b);
	}	

	return PPM;


}

static void* render_ppm(sdl* SDL, ppm* PPM) {

	int offset = 0;

	for(int y = 0; y < SDL->viewport_height; y++) {
		int Vy = (y*PPM->image_height)/SDL->viewport_height;


		for(int x = 0; x < SDL->viewport_width; x++) {
			int Vx = (x*PPM->image_width)/SDL->viewport_width;
			
			printf("X: %d, Y: %d\n", x, y);
			put_pixel(SDL, x, y, PPM->vertices[Vx+Vy*PPM->image_width]); 
		}
	} 
/*	vec3 color = {.r=255,.g=0, .b=0};

	for(int i =0; i < SDL->viewport_height; i++) {
		for(int k =0; k < SDL->viewport_width; k++) {	
		put_pixel(SDL, k, i, color);
		}
	} */
}











/*
	printf("\nIteration: %d\n", x);

	  if(x >= (((SDL->viewport_width/PPM->image_width) *3)-1)) {
		PPM->color_ptr=3;
 		x = 0;
  		y++;
}
  	  if(y >= SDL->viewport_height) {
		  PPM->color_ptr =0;
		  return SDL;
}

	  if(y < (((SDL->viewport_height/PPM->image_height) *2)-1) && (x >= (((SDL->viewport_width/PPM->image_width) *3)-1))) {
		PPM->color_ptr=0;
	  }

	printf("Through the check: %d\n", x);
 for(int i=x; i < x + (SDL->viewport_width/PPM->image_width); i++) {
	printf("Color_ptr = %d\n", PPM->color_ptr);
 	put_pixel(SDL, i, y, PPM->vertices[PPM->color_ptr]);
 }
	   PPM->color_ptr++;
	   return render_ppm(SDL, PPM, x+(SDL->viewport_width/PPM->image_width), y);



} */

/* int render(int x, int y, ppm* PPM, sdl* SDL, int color_ptr) {
 * if(x >= (((width/image_width) *3)-1)) {
 * 	x = 0;
 * 	y++;
 * }
 * if(y >= height) return 0;
 *	for(int i=x, i < x + width/image_width; i++) {
 *		put_pixel(SDL, i, y, PPM->vertices[color_ptr].r, PPM->vertices[color_ptr].g, PPM->vertices[color_ptr].b);
 *	}
 *	
 *	return render(x+(width/image_width), y, PPM, SDL, color_ptr++);
 *
 * }
 *
 *
 *
 *
 * */
