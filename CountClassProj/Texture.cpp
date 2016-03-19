#include "Texture.h"
#include  <SDL.h>
#include <SDL_image.h>

Texture::Texture()
{
}

Texture::Texture(std::string& filename, SDL_Renderer* renderer)
{

	SDL_Texture* tex_cache = TextureMap[filename];

	if (tex_cache == nullptr)
	{
		SDL_Surface* loadedSurface = IMG_Load(filename.c_str());


		if (loadedSurface == nullptr)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
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

}

//this function allows us to set the Texture manually, in case the constructor fails
void Texture::SetTexture(std::string filename, SDL_Renderer* renderer)
{
	SDL_Texture* tex_cache = TextureMap[filename];

	if (tex_cache == nullptr)
	{
		SDL_Surface* loadedSurface = IMG_Load(filename.c_str());


		if (loadedSurface == nullptr)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
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

}


std::unordered_map<std::string, SDL_Texture*> Texture::TextureMap;