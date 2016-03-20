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

	//set velocity of x, multiply it by our constant UPDATE_INTERVAL
	void SetVelocityX(float x, float interval);
	
	//set velocity and multiply it by our constant UPDATE_INTERVAL
	void SetVelocityY(float y, float interval);


	void HandleEvents(SDL_Event* event);
	
	//Used at the end of each update cycle so we know the final position of our entity, which should be used for rendering
	void SetMove();

	

	//these should probably be protected, to detect clicks of derived classes 
	bool GetClickedOn() const { return ClickedOn; };
	bool GetClickReleased() const { return ClickReleased; };
	bool GetClickable() const { return Clickable; };
	void SetClickable(bool boolean) { Clickable = boolean; }

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
	bool Clickable = true;
};

#endif