#ifndef FunctionButtonDisplay_H
#define FunctionButtonDisplay_H

#include  <SDL.h>
#include <SDL_image.h>
#include "MenuButton.h"
#include <string>
class FunctionButtonDisplay
{
	public:
		FunctionButtonDisplay();
		~FunctionButtonDisplay();

		void SetPosition(MenuButton* menubutton);
		void SetSprite(std::string path, SDL_Renderer* renderer);
		SDL_Point GetPosition();
		void Render(SDL_Renderer* renderer)



		private:
		SDL_Texture* buttonTexture;
		SDL_Rect buttonFrame;
		SDL_Point FunctionButtonDisplayPosition;
	
};


#endif
