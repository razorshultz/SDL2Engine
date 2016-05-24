#ifndef SDLWindow_H
#define SDLWindow_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class SDLWindow
{

	public:
	SDLWindow();
	SDLWindow(int x, int y);
	~SDLWindow();
	
	inline int GetXSize() const { return mXSize; };
	inline int GetYSize() const { return mYSize; };
	SDL_Renderer* GetRenderer() const;

	private:
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;
		bool Init(); //this project uses SDL2's image extension libraries, so don't forget to initialise those too! In particular, the PNG image one. here we initialise the renderer, and create the window
		int mXSize;
		int mYSize;
};




#endif