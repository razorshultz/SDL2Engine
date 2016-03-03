#ifndef TEXTURE_H
#define TEXTURE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <SDL.h>

class Texture
{
	public:
		Texture();
		Texture(std::string& filename, SDL_Renderer* renderer);
		SDL_Texture* GetTexture() const { return mTexture; } ;

private:
	SDL_Texture* mTexture;
	static std::unordered_map <std::string, SDL_Texture*> TextureMap;
	
};

#endif
