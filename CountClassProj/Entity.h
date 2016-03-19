#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <vector>
#include "Texture.h"
#include <SDL.h>


class Entity
{
public:
	Entity();
	Entity(std::string texfilename, SDL_Renderer* renderer);
	Entity(std::string texfilename, SDL_Renderer* renderer, float& x, float& y);
	~Entity();
	void draw(SDL_Renderer* renderer) const;
	void SetVelocityX(float x) { mVelocityX = x;  };
	void SetVelocityY(float y) { mVelocityY = y; };
	void HandleEvents(SDL_Event* event);
	bool GetClickedOn() const { return ClickedOn; };
	bool GetClickReleased() const { return ClickReleased; };
	bool GetClickable() const { return Clickable; };
	bool Clickable = true;

protected:

	std::string mTexFilename;
	Texture mTexture;
	



private:

	float mVelocityX;
	float mVelocityY;
	//these should probably be protected, to detect clicks of derived classes 
	SDL_Rect mRectFrame; 
	bool ClickedOn;
	bool ClickReleased;
	
};

#endif