#include "FunctionButtonDisplay.h"

FunctionButtonDisplay::FunctionButtonDisplay() : buttonTexture(nullptr)
{
	FunctionButtonDisplayPosition.x = 100;
	FunctionButtonDisplayPosition.y = 200;
}

FunctionButtonDisplay::~FunctionButtonDisplay()
{	delete buttonTexture;
	buttonTexture = nullptr;
}

void FunctionButtonDisplay::SetPosition(MenuButton* menubutton)
{
	FunctionButtonDisplayPosition = menubutton->GetPosition();
	
}

SDL_Point FunctionButtonDisplay::GetPosition()
{
	return FunctionButtonDisplayPosition;
}

void FunctionButtonDisplay::SetSprite(std::string path, SDL_Renderer* Renderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path into surface, we need to do this in order to eventually create a texture
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels! This is how we actually get our texture
        newTexture = SDL_CreateTextureFromSurface( Renderer, loadedSurface );
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