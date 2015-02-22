#ifndef Window_H
#define Window_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Window
{

	public:
	Window();
	~Window();
	
	
	SDL_Renderer* GetRenderer();

	private:
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;
		bool Init(); //this project uses SDL2's image extension libraries, so don't forget to initialise those too! In particular, the PNG image one. here we initialise the renderer, and create the window

};




#endif