#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "ppm.h"
#include "main.h"


/* Modified to remove gcc warnin g "cast from pointer to integer of different type" because doing uint32_t pixel
 *  = (uint32_t)... does not guarentee the value of the 'pixels' address might be too large on some systems and
 *  doing arithmatic might give unexpected results 
 */
 


int main(int argc, char* argv[] )
{
	sdl SDL;
	tokens *TOKEN;
	ppm *PPM = (ppm*)malloc(sizeof(ppm));
	PPM->file_ppm = fopen(argv[1], "r");
	read_file(PPM, TOKEN);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL.viewport_width = 1280;
	SDL.viewport_height = 840;
	SDL.window = SDL_CreateWindow("render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL.viewport_width, SDL.viewport_height, SDL_WINDOW_RESIZABLE);
//	SDL_Surface* main = SDL_GetWindowSurface(SDL.window);
	if(SDL.window == NULL) return 1;
/*
	SDL.surface = SDL_CreateRGBSurfaceWithFormat(0, 640, 420, 32, SDL_PIXELFORMAT_RGBA8888);


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
	SDL_Surface* main = SDL_GetWindowSurface(SDL.window);
	SDL.surface = SDL_CreateRGBSurfaceWithFormat(0, 1280, 840, 32, SDL_PIXELFORMAT_RGBA8888);

	
	render_ppm(&SDL, PPM);

	SDL_BlitSurface(SDL.surface, 0, main, 0); // For some reason just using SDL.surface is not good enough for SDL_UpdateWindowSurface? What the shit?
	int ret=SDL_UpdateWindowSurface(SDL.window);
	if(ret<0) {
		SDL_ERROR(SDL_GetError());
		return 0;
	   }
	printf("\nCustom Surface W/H: %d/%d, Window Surface W/H: %d/%d", SDL.surface->w, SDL.surface->h, main->w, main->h);

	while(true) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT: {return 0; break;}
			default: break;
		}
	}
	SDL_Delay(10);
}
	SDL_Quit();
	SDL_DestroyWindow(SDL.window);
	return 0;
}
