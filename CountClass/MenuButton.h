#ifndef MenuButton_H
#define MenuButton_H

#include "SDL.h"
class MenuButton
{
	public:
		MenuButton();
		~MenuButton();
		void SetPosition(int x, int y);
		SDL_Point GetPosition();

		virtual void HandleEvent(SDL_Event* events) =0;

	protected:
		SDL_Point mPosition;
		int ButtonWidth;
		int ButtonHeight;


};


#endif