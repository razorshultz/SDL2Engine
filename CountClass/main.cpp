
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "CountClass.h"
#include "FunctionButton.h"
#include "FunctionButtonDisplay.h"
#include "SDLWindow.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

//surface contained by the window
SDL_Surface* gScreenSurface = nullptr;




int main(int argc, char* args[])
{		
		SDLWindow mywindow;
		int count =0;

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
	
	thedisplayedbutton.SetSprite("pngimage.png", mywindow.GetRenderer());

		SDL_Surface* thesurf = IMG_Load("pngimage.png"); //don't forget to initialise PNG loading extension! here we're just loading a text image.
		if(thesurf != nullptr)
			{
				//std::cout << "surf is null! error! " << SDL_GetError();
				std::cout << "surf is good!";
			}

	SDL_Texture* thetext = SDL_CreateTextureFromSurface(mywindow.GetRenderer(), thesurf); //don't try to load an image before initialising the renderer! (We initialise it in the Init() function). Here, we create a texture from our test image.
	
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
		
			SDL_RenderCopy(mywindow.GetRenderer(), thetext, NULL, NULL); //here, we render our test image.
			thedisplayedbutton.Render(mywindow.GetRenderer()); //IHere our button is displaying itself.
				
			SDL_RenderPresent(mywindow.GetRenderer());
		}

//	delete thebutton;
	SDL_Quit();

	return 0;
}

