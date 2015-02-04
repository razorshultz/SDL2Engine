#include "FunctionButton.h"



FunctionButton::FunctionButton() //initialising inherited protected member variables in a member initialiser list doesnt seem to work
{
	ButtonWidth = 100;
	ButtonHeight = 100;
	ButtonPressed = false;
	ButtonReleased = true;
}

FunctionButton::FunctionButton(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
	ButtonPressed = false;
	ButtonReleased = true;
}

FunctionButton::~FunctionButton()
{
}

 
 void FunctionButton::HandleEvent(SDL_Event* events)
 {
	if(events->type == SDL_MOUSEMOTION || events->type == SDL_MOUSEBUTTONDOWN || events->type == SDL_MOUSEBUTTONUP)
	{	//get mouse position
		int x, y;
		SDL_GetMouseState(&y, &y);

		//check if mouse is inside button
		bool inside = true;

		//mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//mouse is right of the button
		else if (x > mPosition.x + ButtonWidth)
		{
			inside = false;
		}
		//if mouse if above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//if mouse is below the button
		else if (y > mPosition.y + ButtonHeight)
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
				ButtonPressed = true;
			}

		}
		
		
			
	}
 }