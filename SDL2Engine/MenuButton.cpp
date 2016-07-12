#include "MenuButton.h"

MenuButton::MenuButton() 
{
	buttonFrame.h = 100;
	buttonFrame.w = 100;
	buttonFrame.x = 50;
	buttonFrame.y = 50;
}

MenuButton::~MenuButton()
{
}

void MenuButton::SetPosition(int Newx, int Newy)
{
	buttonFrame.x = Newx;
	buttonFrame.y = Newy;
}

SDL_Point MenuButton::GetPosition() const
{
	SDL_Point pos;
	pos.x = buttonFrame.x;
	pos.y = buttonFrame.y;

	return pos;
}

int MenuButton::GetHeight() const
{
	return buttonFrame.h;
}

int MenuButton::GetWidth() const
{
	return buttonFrame.w;
}

