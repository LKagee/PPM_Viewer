#pragma once

typedef struct {
	SDL_Window *window;
	SDL_Surface *surface;

} sdl;

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
/* Modified to remove gcc warnin g "cast from pointer to integer of different type" because doing uint32_t pixel
 *  = (uint32_t)... does not guarentee the value of the 'pixels' address might be too large on some systems and
 *  doing arithmatic might give unexpected results 
 */
 
static void put_pixel(sdl* SDL, int x, int y) {
	
	if(SDL_MUSTLOCK(SDL->surface))SDL_LockSurface(SDL->surface);
	uint32_t* pixels = (uint32_t*)SDL->surface->pixels;


	uint32_t* pixel = (uint32_t*)((uint8_t*)pixels + y*SDL->surface->pitch + x*sizeof(uint32_t)); 
	*pixel = SDL_MapRGBA(SDL->surface->format, 0xff, 0xff, 0xff, 0xff);
	if(SDL_MUSTLOCK(SDL->surface))SDL_UnlockSurface(SDL->surface);

}


