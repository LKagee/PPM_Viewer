#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include "SDL2-devel-2.32.6-mingw/SDL2-2.32.6/x86_64-w64-mingw32/include/SDL2/SDL.h" // For Windows compilation
#include <SDL2/SDL.h>
#include "include/ppm.h"
#include "include/render.h"



/* Modified to remove gcc warning "cast from pointer to integer of different type" because doing uint32_t pixel
 *  = (uint32_t)... does not guarentee the value of the 'pixels' address might be too large on some systems and
 *  doing arithmatic might give unexpected results 
 */
 


int main(int argc, char* argv[] )
{
	sdl SDL;
	ppm PPM;

	r_setupSDL(&SDL, 1280, 840);
	p_setupPPM(&PPM, argv[1]);
	p_readPPM(&PPM);
	r_renderSDL(&SDL, &PPM);

	// For some reason just using SDL.surface is not good enough for SDL_UpdateWindowSurface? What the shit?

	SDL_BlitSurface(SDL.surface, 0, SDL.window_surface, 0); 

	
	int ret=SDL_UpdateWindowSurface(SDL.window);
	if(ret<0) {
		SDL_ERROR(SDL_GetError());
		return 0;
	   }

	// Main Loop

	while(true) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT: {r_quitSDL(&SDL); return 0; break;}
			default: break;
		}
	}
	SDL_Delay(10);
}
return 0;
}
