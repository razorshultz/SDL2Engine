#ifndef TEXTURE_H
#define TEXTURE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <SDL.h>
#include <stdexcept>

class Texture
{
public:
	Texture();
	Texture(std::string& filename, SDL_Renderer* renderer);
	auto& GetTexture() const { return mTexture; };
	void SetTexture(std::string filename, SDL_Renderer* renderer);

private:
	std::shared_ptr<SDL_Texture> mTexture;

	//static std::unordered_map <std::string, SDL_Texture*> TextureMap;
	static std::unordered_map<std::string, std::weak_ptr<SDL_Texture>> TextureMap;

};







#endif

class NoDefaultTexture : public std::exception
{
public:
	NoDefaultTexture()
	{};
	virtual const char* what() const throw()
	{
		return "texture missing. tried to load default texture, but default.jpg was missing";
	};
};
#pragma once
