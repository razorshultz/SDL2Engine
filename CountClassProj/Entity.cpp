#include "Entity.h"
#include <exception>



Entity::Entity(std::string texfilename, SDL_Renderer* renderer) : mTexFilename(texfilename), mTexture(texfilename, renderer), Clickable(true)
{

	mRectFrame.x = 0;
	mRectFrame.y = 0;

}

Entity::Entity(std::string texfilename, SDL_Renderer* renderer, float& x, float& y) : mTexFilename(texfilename), mTexture(texfilename, renderer), Clickable(false)
{
	
	mRectFrame.x = x; 
	mRectFrame.y = y;

//use SDL_QueryTexture to look at the entity's Texture file, and use its actual size to set the collision frame up! we declare 2 ints to store the info
	int w, h;
	SDL_QueryTexture(mTexture.GetTexture(), nullptr, nullptr, &w, &h);
	 
	//use stored info from SDL_QueryTexture to set the collision frame
	mRectFrame.w = w ;
	mRectFrame.h = h ;

	
	

}


Entity::Entity()
{

}
Entity::~Entity()
{

}



void Entity::draw(SDL_Renderer* renderer) const //draw without render extrapolation
{
	SDL_RenderCopy(renderer, mTexture.GetTexture(), nullptr, &mRectFrame);

}

void Entity::HandleEvents(SDL_Event* events) //can take code out of here to put it into a different ui class derived from entity, which can be clicked on.
{
	bool Clickable = false;

	if (events->type == SDL_MOUSEBUTTONDOWN || events->type == SDL_MOUSEBUTTONUP) //original:  SDL_MOUSEMOTION || events->type == SDL_MOUSEBUTTONDOWN || events->type == SDL_MOUSEBUTTONUP)
	{	//get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//check if mouse is inside button
		bool inside = true;

		//mouse is left of the button
		if (x < mRectFrame.x)
		{
			inside = false;
		}
		//mouse is right of the button
		else if (x > mRectFrame.x + mRectFrame.w)
		{
			inside = false;
		}
		//if mouse if above the button
		else if (y < mRectFrame.y)
		{
			inside = false;
		}
		//if mouse is below the button
		else if (y > mRectFrame.y + mRectFrame.h)
		{
			inside = false;
		}

		if (inside)
		{
			if (events->type == SDL_MOUSEBUTTONDOWN)
			{
				ClickedOn = true; //will it hold true every frame and get spammed? Yes, but we take care of that in the main program
				ClickReleased = false;

			}
			else if (events->type == SDL_MOUSEBUTTONUP)
			{
				ClickedOn = false;
				ClickReleased = true;
			}


		
		}
	}

}







