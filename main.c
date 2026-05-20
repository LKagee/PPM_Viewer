#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "ppm.h"
#include "main.h"


/* Modified to remove gcc warnin g "cast from pointer to integer of different type" because doing uint32_t pixel
 *  = (uint32_t)... does not guarentee the value of the 'pixels' address might be too large on some systems and
 *  doing arithmatic might give unexpected results 
 */
 


int main( void )
{
	sdl SDL;
	tokens *TOKEN;
	ppm *PPM = (ppm*)malloc(sizeof(ppm));
	PPM->file_ppm = fopen("test.ppm", "r");
	read_file(PPM, TOKEN);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL.window = SDL_CreateWindow("render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 400, SDL_WINDOW_RESIZABLE);
//	SDL_Surface* main = SDL_GetWindowSurface(SDL.window);
	if(SDL.window == NULL) return 1;
/*
	SDL.surface = SDL_CreateRGBSurfaceWithFormat(0, 640, 400, 32, SDL_PIXELFORMAT_RGBA8888);


	for(int i = 0; i < 400; i++) {
	   for(int k = 0; k < 640; k++) {   
	
	   put_pixel(&SDL, k, i);
	   }
	}
	   SDL_BlitSurface(SDL.surface, 0, main, 0); // For some reason just using SDL.surface is not good enough for SDL_UpdateWindowSurface? What the shit?
	   int ret=SDL_UpdateWindowSurface(SDL.window);
	   if(ret<0) fprintf(stdout, "Failed to render: %s\n", SDL_GetError());
	
			// ###
			// ###
			// ###
	

*/
	render_ppm(&SDL, PPM, TOKEN);
	SDL_Delay(1000);
	SDL_Quit();
	SDL_DestroyWindow(SDL.window);
	return 0;
}
