#include "FunctionButtonDisplay.h"

FunctionButtonDisplay::FunctionButtonDisplay() : buttonTexture(nullptr)
{
	buttonFrame.x = 100;
	buttonFrame.y = 200;
	buttonFrame.h = 50;
	buttonFrame.w = 50;
	buttonTexture = nullptr;
	
}

FunctionButtonDisplay::FunctionButtonDisplay(FunctionButton functionbutton) 
{
	buttonFrame.x = functionbutton.GetPosition().x;
	buttonFrame.y =functionbutton.GetPosition().y;
	buttonTexture = nullptr;
	buttonFrame.h = functionbutton.GetHeight();
	buttonFrame.w = functionbutton.GetWidth();

}


FunctionButtonDisplay::~FunctionButtonDisplay()
{	delete buttonTexture;
	buttonTexture = nullptr;
}

void FunctionButtonDisplay::SetPosition(MenuButton* menubutton)
{
	buttonFrame.x = menubutton->GetPosition().x;
	buttonFrame.y = menubutton->GetPosition().y;
	
}

SDL_Point FunctionButtonDisplay::GetPosition()
{	SDL_Point pos;
	
	pos.x = buttonFrame.x;
	pos.y = buttonFrame.y;

	return pos;
}

void FunctionButtonDisplay::SetSprite(std::string path, SDL_Renderer* Renderer)
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path into surface, we need to do this in order to eventually create a texture
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels! This is how we actually get our texture
        newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface, since we already made a texture
		SDL_FreeSurface( loadedSurface );
	}
	//set our texture to be the texture we just created
	buttonTexture = newTexture;
}

void FunctionButtonDisplay::Render(SDL_Renderer* renderer, SDL_Texture* thetext)
{
	SDL_RenderCopy(renderer, thetext, NULL, &buttonFrame);
}