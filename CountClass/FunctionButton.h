#include "MenuButton.h"

#ifndef FunctionButton_H
#define FunctionButton_H




class FunctionButton : public MenuButton
{
	public:
		FunctionButton();
		FunctionButton(int x, int y);
		~FunctionButton();
		bool GetButtonPressed();
		bool GetButtonReleased();

		virtual void HandleEvent(SDL_Event* events);


		private:
			bool ButtonPressed;
			bool ButtonReleased;

};

#endif
