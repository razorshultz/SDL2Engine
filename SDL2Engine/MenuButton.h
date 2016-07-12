#ifndef MenuButton_H
#define MenuButton_H

#include "SDL.h"
class MenuButton
{
	public:
		MenuButton();
	virtual	~MenuButton();
		void SetPosition(int x, int y);
		SDL_Point GetPosition() const;
		int GetHeight() const;
		int GetWidth() const;

		virtual void HandleEvent(SDL_Event* events) =0;

	protected:
		SDL_Rect buttonFrame;


};


#endif