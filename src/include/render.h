#pragma once


	
/* 
 *  ________________________
 * |                        |
 * |	 Main SDL struct    |
 * |			    |
 * **************************
 *
 */


typedef struct {
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Surface *window_surface;
	int viewport_height, viewport_width;

} sdl;


/* 
 *  ________________________
 * |                        |
 * |   Main SDL functions   |
 * |			    |
 * **************************
 *
 * Pipeline for SDL goes like this: r_setupSDL(SDL, width, height) -> r_renderSDL(&SDL, &PPM) -> r_quitSDL(&SDL) before exiting
 * main().
 *
 * TIP: The lcoation of r_quit() does not matter as long as its after r_renderSDL() and before exiting main(),
 * but it is generally good practice to call r_quitSDL() right before exiting main() as to not prematurely destroy the window.
 *
 * Error Checking: Since every function returns a pointer to NULL if something goes wrong, simply check if the function returns NULL
 * and safely exit the program by calling r_quitSDL() then exiting main().
 */



static void* r_setupSDL(sdl* SDL, int viewport_width, int viewport_height) {

	SDL_SetMainReady();

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL->viewport_width = viewport_width;
	SDL->viewport_height = viewport_height;
	SDL->window = SDL_CreateWindow("render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL->viewport_width, SDL->viewport_height, SDL_WINDOW_RESIZABLE);

	if(SDL->window == NULL) return NULL;

	SDL->window_surface = SDL_GetWindowSurface(SDL->window);
	SDL->surface = SDL_CreateRGBSurfaceWithFormat(0, 1280, 840, 32, SDL_PIXELFORMAT_RGBA8888);
	return SDL;



}



static void r_quitSDL(sdl* SDL) {
	
	SDL_Quit();
	SDL_DestroyWindow(SDL->window);

}

/* Modified to remove gcc warnin g "cast from pointer to integer of different type" because doing uint32_t pixel
 *  = (uint32_t)... does not guarentee the value of the 'pixels' address might be too large on some systems and
 *  doing arithmatic might give unexpected results 
 */
 
static void r_putPixel(sdl* SDL, int x, int y, vec3 color) {
	
	if(SDL_MUSTLOCK(SDL->surface))SDL_LockSurface(SDL->surface);
	uint32_t* pixels = (uint32_t*)SDL->surface->pixels;

	uint32_t* pixel = (uint32_t*)((uint8_t*)pixels + y*SDL->surface->pitch + x*sizeof(uint32_t)); 
	*pixel = SDL_MapRGBA(SDL->surface->format, color.r, color.g, color.b, 0xff);
	if(SDL_MUSTLOCK(SDL->surface))SDL_UnlockSurface(SDL->surface);

}



static void* r_renderSDL(sdl* SDL, ppm* PPM) {

	int offset = 0;

	for(int y = 0; y < SDL->viewport_height; y++) {
		int Vy = (y*PPM->image_height)/SDL->viewport_height;


		for(int x = 0; x < SDL->viewport_width; x++) {
			int Vx = (x*PPM->image_width)/SDL->viewport_width;
			
		
			r_putPixel(SDL, x, y, PPM->vertices[Vx+Vy*PPM->image_width]); 
		}
	} 

}




