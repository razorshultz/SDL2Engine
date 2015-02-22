
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "CountClass.h"
#include "FunctionButton.h"
#include "FunctionButtonDisplay.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
//window to render to
SDL_Window* gWindow = nullptr;

//surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

SDL_Renderer* gRenderer = nullptr;

bool Init();

int main(int argc, char* args[])
{	int count =0;

		SDL_Event events;
		bool quit = false;
		bool increased = false;

		
	FunctionButton thebutton(100,100);
		FunctionButtonDisplay thedisplayedbutton(thebutton);

		SDL_Point thepoint = thedisplayedbutton.GetPosition();

		int theint = thepoint.x;
		int hi = thepoint.y;
		std::cout << theint << " " << thepoint.y << std::endl;

  	


//End testing the classes
	if (!Init())
	{
		std::cout << "Initialisation error";
	}
	else
	{	thedisplayedbutton.SetSprite("pngimage.png", gRenderer);

		SDL_Surface* thesurf = IMG_Load("pngimage.png"); //don't forget to initialise PNG loading extension! here we're just loading a text image.
		if(thesurf != nullptr)
			{
				//std::cout << "surf is null! error! " << SDL_GetError();
				std::cout << "surf is good!";
			}

	SDL_Texture* thetext = SDL_CreateTextureFromSurface(gRenderer, thesurf); //don't try to load an image before initialising the renderer! (We initialise it in the Init() function). Here, we create a texture from our test image.
	if (thetext == NULL)
	{
		std::cout << "thetext is null, error! " << SDL_GetError();
		//std::cout << "thetext is good!";
	}
		//handle events til we quit
		while(!quit)
		{
			while(SDL_PollEvent(&events) != 0)
			{
				

			}

				thebutton.HandleEvent(&events);
				if(thebutton.GetButtonPressed() == true && increased == false)
					{
						count++;
						increased = true;
						std::cout << count << " ";
					}

					if(thebutton.GetButtonReleased() == true)
					{
						
						increased = false;
						
					}
		


			SDL_RenderCopy(gRenderer, thetext, NULL, NULL); //here, we render our test image.
			thedisplayedbutton.Render(gRenderer); //IHere our button is displaying itself.
				
			SDL_RenderPresent(gRenderer);
		}
		


	}

//	delete thebutton;
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

			//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//create window
		gWindow = SDL_CreateWindow("Counter Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == nullptr)
		{
			std::cout << "Window creation error" << SDL_GetError();
			success = false;
		}
		else
		{
		//Setup our renderer to render to our window
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if(gRenderer == nullptr)
		{
			std::cout << "failed to initialise renderer! " << SDL_GetError();
		}

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
		}

	}

	return success;

}