#ifndef TEXTURE_H
#define TEXTURE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <SDL.h>
#include <exception>
#include <iostream>

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








#endif

class DefaultTextureIsMissing : public std::exception
{
public:
	DefaultTextureIsMissing() {};
	virtual const char* what()
	{
		return "texture was missing - tried loading default texture, but default.jpg is missing";
	};
};