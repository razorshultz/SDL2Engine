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
	auto& tex_cache = TextureMap[filename];
	try {
		if (tex_cache.expired())
		{
			//SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
			auto& loadedSurface = std::make_shared<SDL_Surface>();


			if (loadedSurface == nullptr)
			{
				if (filename == "default.jpg")
					throw NoDefaultTexture();

				//printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError())
				SetTexture("default.jpg", renderer);

			}
			else
			{	//convert to screen format
				mTexture = std::make_shared<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, loadedSurface.get()));

				if (mTexture == nullptr)
					printf("Unable to create texture from %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());


			}

			tex_cache = mTexture;
		}
		else
		{
			mTexture = tex_cache.lock();

		}
	}
	catch (NoDefaultTexture& e) { std::cout << e.what(); }

}


//std::unordered_map<std::string, SDL_Texture*> Texture::TextureMap;
static std::unordered_map<std::string, std::weak_ptr<SDL_Texture>> TextureMap;