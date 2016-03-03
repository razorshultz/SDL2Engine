#include "SDLWindow.h"



SDLWindow::SDLWindow()
{	
	Init();
}

SDLWindow::~SDLWindow()
{
	SDL_Quit();
}

SDL_Renderer* SDLWindow::GetRenderer() const
{
	return mRenderer;
} 
//comment
bool SDLWindow::Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialise" << SDL_GetError();
		success = false;
	}
	else
	{
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) //set texture filtering to linear
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		//create window
		mWindow = SDL_CreateWindow("Counter Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);

		if (mWindow == nullptr)
		{
			std::cout << "Window creation error!" << SDL_GetError();
			success = false;
		}
		else	//setup the renderer
		{
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
			if(mRenderer == nullptr)
			{
				std::cout << "Failed to initialise renderer!" << SDL_GetError();
			}

			int imgFlags = IMG_INIT_JPG; //from SDL_image.h

			if(!(IMG_Init(imgFlags) & imgFlags))
			{
				std::cout << "SDL_image could not initialise! error: " << IMG_GetError();
				success = false;
			}



		}



	}

	return success;

}