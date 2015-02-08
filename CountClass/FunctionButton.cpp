#include "FunctionButton.h"



FunctionButton::FunctionButton()//initialising inherited protected member variables in a member initialiser list doesnt seem to work
{
	buttonFrame.h = 100;
	buttonFrame.w = 100;
	buttonFrame.x = 50;
	buttonFrame.y = 50;
	ButtonPressed = false;
	ButtonReleased = true;
}

FunctionButton::FunctionButton(int x, int y)
{	buttonFrame.h = 100;
	buttonFrame.w = 100;
	buttonFrame.x = x;
	buttonFrame.y = y;
	ButtonPressed = false;
	ButtonReleased = true;
}

FunctionButton::~FunctionButton()
{
}

bool FunctionButton::GetButtonPressed() const
{
	return ButtonPressed;
}

bool FunctionButton::GetButtonReleased() const
{
	return ButtonReleased;
}

 
 void FunctionButton::HandleEvent(SDL_Event* events)
 {
	if(events->type == SDL_MOUSEBUTTONDOWN || events->type == SDL_MOUSEBUTTONUP) //original:  SDL_MOUSEMOTION || events->type == SDL_MOUSEBUTTONDOWN || events->type == SDL_MOUSEBUTTONUP)
	{	//get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//check if mouse is inside button
		bool inside = true;

		//mouse is left of the button
		if (x < buttonFrame.x)
		{
			inside = false;
		}
		//mouse is right of the button
		else if (x > buttonFrame.x + buttonFrame.w)
		{
			inside = false;
		}
		//if mouse if above the button
		else if (y < buttonFrame.y)
		{
			inside = false;
		}
		//if mouse is below the button
		else if (y > buttonFrame.y + buttonFrame.h)
		{
			inside = false;
		}

		if(inside)
		{
			if (events->type == SDL_MOUSEBUTTONDOWN)
			{
				ButtonPressed = true; //will it hold true every frame and get spammed?
				ButtonReleased = false;
			}
			else if (events->type == SDL_MOUSEBUTTONUP)
			{
				ButtonPressed = false;
				ButtonReleased = true;
			}

		}
		
		
			
	}
 }