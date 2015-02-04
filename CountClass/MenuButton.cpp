#include "MenuButton.h"

MenuButton::MenuButton() : ButtonWidth(100), ButtonHeight(100)
{
	mPosition.x = 100;
	mPosition.y = 100;
}

MenuButton::~MenuButton()
{
}

void MenuButton::SetPosition(int Newx, int Newy)
{
	mPosition.x = Newx;
	mPosition.y = Newy;
}

SDL_Point MenuButton::GetPosition()
{
	return mPosition;
}

