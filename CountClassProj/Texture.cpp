#include "Texture.h"
#include  <SDL.h>
#include <SDL_image.h>
#include <iostream>

Texture::Texture()
{
}

Texture::Texture(std::string& filename, SDL_Renderer* renderer)
{

	SetTexture(filename, renderer);

	//if (mTexture == nullptr)
	//	SetTexture("default.jpg", renderer);




}

//this function allows us to set the Texture manually, in case the constructor fails
void Texture::SetTexture(std::string filename, SDL_Renderer* renderer)
{
	SDL_Texture* tex_cache = TextureMap[filename];
	try {
		if (tex_cache == nullptr)
		{
			SDL_Surface* loadedSurface = IMG_Load(filename.c_str());


			if (loadedSurface == nullptr)
			{
				if (filename == "default.jpg")
				throw DefaultTextureIsMissing();


				//printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
				SetTexture("default.jpg", renderer);
			}
			else
			{	//convert to screen format
				mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

				if (mTexture == nullptr)
					printf("Unable to create texture from %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());


			}

			tex_cache = mTexture;
		}
		else
		{
			mTexture = TextureMap[filename];

		}
	} catch (DefaultTextureIsMissing& e) { std::cout << e.what(); }

}


std::unordered_map<std::string, SDL_Texture*> Texture::TextureMap;


