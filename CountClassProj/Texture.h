#ifndef TEXTURE_H
#define TEXTURE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <SDL.h>
#include <exception>

class Texture
{
	public:
		Texture();
		Texture(std::string& filename, SDL_Renderer* renderer);
		SDL_Texture* GetTexture() const { return mTexture; };
		void SetTexture(std::string filename, SDL_Renderer* renderer);

private:
	SDL_Texture* mTexture;

	static std::unordered_map <std::string, SDL_Texture*> TextureMap;
	
};



/*class NoDefaultTexture : public std::runtime_error 
{
	public:
		NoDefaultTexture() : std::runtime_error("texture was missing - tried loading default texture, but default.jpg is missing")
		{};
}
*/



#endif
