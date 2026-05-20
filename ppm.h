#pragma once
#define ERROR(a) fprintf(stdout, "ERROR IN PPM READER!: %s", a)
#define SDL_ERROR(a) fprintf(stdout, "ERROR IN SDL!: %s", a)
#include <stdint.h>
#include "main.h"


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

	for(int i = 0; i < PPM->image_height * PPM->image_width; i++) {

	if(fscanf(PPM->file_ppm, "%d %d %d", &PPM->vertices[i].r, &PPM->vertices[i].g, &PPM->vertices[i].b) != 3) {
		ERROR("Invalid row 1 RGB data (must be 0-color_max for each RGB cell and be formatted [R] [G] [B])\n");
	 	return NULL;
	}
        printf("RGB: %d %d %d\n", PPM->vertices[i].r, PPM->vertices[i].g, PPM->vertices[i].b);
	}	

	return PPM;


//	printf("%d", header);
}

static void* render_ppm(sdl* SDL, ppm* PPM, tokens *tokenizer) {

	SDL_Surface* main = SDL_GetWindowSurface(SDL->window);
	SDL->surface = SDL_CreateRGBSurfaceWithFormat(0, 640, 400, 32, SDL_PIXELFORMAT_RGBA8888);


	for(int i = 0; i < 400; i++) {
	   for(int k = 0; k < 640; k++) {   
	
	   put_pixel(SDL, k, i);
	   }
	}
	   SDL_BlitSurface(SDL->surface, 0, main, 0); // For some reason just using SDL.surface is not good enough for SDL_UpdateWindowSurface? What the shit?
	   int ret=SDL_UpdateWindowSurface(SDL->window);
	   if(ret<0) {
		SDL_ERROR(SDL_GetError());
		return NULL;
	   }

	   return SDL;


}

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
