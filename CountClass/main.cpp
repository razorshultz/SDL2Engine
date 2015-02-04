
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "CountClass.h"
#include "FunctionButton.h"
#include "FunctionButtonDisplay.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
//window to render to
SDL_Window* gWindow = nullptr;

//surface contained by the window
SDL_Surface* gScreenSurface = nullptr;


bool Init();

int main(int argc, char* args[])
{	
	SDL_Event events;
	bool quit = false;
	

		FunctionButton* thebutton = new FunctionButton(100,150);
		FunctionButtonDisplay thedisplayedbutton;

		thedisplayedbutton.SetPosition(thebutton);

		
		SDL_Point thepoint = thedisplayedbutton.GetPosition();

		int theint = thepoint.x;
		int hi = thepoint.y;
		std::cout << theint << " " << thepoint.y << std::endl;


//End testing the classes
// X: 100
//Y: 100

	if (!Init())
	{
		std::cout << "Initialisation error";
	}
	else
	{
		//handle events til we quit
		while(!quit)
		{
			while(SDL_PollEvent(&events) != 0)
			{
				
			}
		}
		


	}

	SDL_Quit();



	return 0;
}

bool Init()
{
	bool success = true;

	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialise! Error:" << SDL_GetError();
		success = false;
	}
	else
	{
		//create window
		gWindow = SDL_CreateWindow("Counter Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == nullptr)
		{
			std::cout << "Window creation error" << SDL_GetError();
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}

	}

	return success;

}