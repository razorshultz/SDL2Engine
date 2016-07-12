#include "Entity.h"
#include <exception>



Entity::Entity(std::string texfilename, SDL_Renderer* renderer) : mTexFilename(texfilename), mTexture(texfilename, renderer), Clickable(true), mPositionX(0), mPositionY(0), mVelocityX(0), mVelocityY(0), mAccelerationX(0.0f), mAccelerationY(0.0f)
{
	mRectFrame.y = 0;
	mRectFrame.x = 0;

	//use SDL_QueryTexture to look at the entity's Texture file, and use its actual size to set the collision frame up! we declare 2 ints to store the info
	int w = 0, h = 0;
	SDL_QueryTexture(mTexture.GetTexture(), nullptr, nullptr, &w, &h);

	//use stored info from SDL_QueryTexture to set the collision frame
	mRectFrame.w = w;
	mRectFrame.h = h;
}

Entity::Entity(std::string texfilename, SDL_Renderer* renderer, float& x, float& y) : mTexFilename(texfilename), mTexture(texfilename, renderer), Clickable(false), mPositionX(x), mPositionY(y), mVelocityX(0), mVelocityY(0), mAccelerationX(0.0f), mAccelerationY(0.0f)
{
	mRectFrame.x = static_cast<int>(x); 
	mRectFrame.y = static_cast<int>(y);

//use SDL_QueryTexture to look at the entity's Texture file, and use its actual size to set the collision frame up! we declare 2 ints to store the info
	int w =0, h = 0;
	SDL_QueryTexture(mTexture.GetTexture(), nullptr, nullptr, &w, &h);
	 
	//use stored info from SDL_QueryTexture to set the collision frame
	mRectFrame.w = w ;
	mRectFrame.h = h ;
}

Entity::Entity(std::string texfilename, SDL_Renderer* renderer, float& x, float& y, float AccelerationX, float AccelerationY) : mTexFilename(texfilename), mTexture(texfilename, renderer), Clickable(false), mPositionX(x), mPositionY(y), mVelocityX(0), mVelocityY(0), mAccelerationX(AccelerationX), mAccelerationY(AccelerationY)
{	
	mRectFrame.x = static_cast<int>(x);
	mRectFrame.y = static_cast<int>(y);

	//use SDL_QueryTexture to look at the entity's Texture file, and use its actual size to set the collision frame up! we declare 2 ints to store the info
	int w = 0, h = 0;
	SDL_QueryTexture(mTexture.GetTexture(), nullptr, nullptr, &w, &h);

	//use stored info from SDL_QueryTexture to set the collision frame
	mRectFrame.w = w;
	mRectFrame.h = h;
}

Entity::Entity(std::string texfilename, SDL_Renderer* renderer, float& x, float& y,  float naturalvelocitylimitx, float naturalvelocitylimity, float friction) : mTexFilename(texfilename), mTexture(texfilename, renderer), Clickable(false), mPositionX(x), mPositionY(y), mVelocityX(0), mVelocityY(0), mAccelerationX(0), mAccelerationY(0), mNaturalVelocityLimitX(naturalvelocitylimitx), mNaturalVelocityLimitY(naturalvelocitylimity), mFriction(friction)
{
	mRectFrame.x = static_cast<int>(x);
	mRectFrame.y = static_cast<int>(y);

	//use SDL_QueryTexture to look at the entity's Texture file, and use its actual size to set the collision frame up! we declare 2 ints to store the info
	int w = 0, h = 0;
	SDL_QueryTexture(mTexture.GetTexture(), nullptr, nullptr, &w, &h);

	//use stored info from SDL_QueryTexture to set the collision frame
	mRectFrame.w = w;
	mRectFrame.h = h;


}



Entity::Entity()
{

}
Entity::~Entity()
{

}

void Entity::SetVelocityX(const float& acceleration) //set velocity with acceleration. pass in 1 for no change. // interval is deltatime
{ 
	mVelocityX = acceleration; 
}

void Entity::SetVelocityY(const float& acceleration)
{
	mVelocityY = acceleration;
};

void Entity::OffsetVelocityX(float accel, const float& interval)
{
	mVelocityX += accel * interval;
}


void Entity::OffsetVelocityY(float accel, const float& interval)
{
	mVelocityY += accel * interval;
}

void Entity::SetAccelerationX(float accel)
{
	mAccelerationX = accel;
}

void Entity::SetAccelerationY(float accel)
{
	mAccelerationY = accel;
}

void Entity::OffsetAccelerationX(float accel, const float& interval)
{	
	
	mAccelerationX += accel * interval;
}


void Entity::OffsetAccelerationY(float accel, const float& interval)
{

	mAccelerationY += accel * interval;
}

void Entity::OffsetPositionX(float velocity, const float& interval )
{	//old method using euler integration
	//mPositionX += velocity * interval;

	//now we use verlet integration
	mPositionX += interval * (velocity + interval * mAccelerationX / 2);
}

void Entity::OffsetPositionY(float velocity, const float& interval)
{	//as above, this is old, we use euler integration here
	//mPositionY += velocity ;

	mPositionY += interval * (velocity + interval * mAccelerationY / 2);
}


//use our velocities that we've received from the update cycle to set a final position which we use as the position to render our destination rectangle (mRectFrame) at
void Entity::SetMove()
{	//really important! Since SD_Rects and pixels can both only increment by whole integers, we cast our float values as integers, and update x and y position of our destination rectangle with those

	mRectFrame.y = static_cast<int>(mPositionY);
	mRectFrame.x = static_cast<int>(mPositionX);
};

void Entity::draw(SDL_Renderer* renderer) const //draw without render extrapolation
{

	SDL_RenderCopy(renderer, mTexture.GetTexture(), nullptr, &mRectFrame);
}



void Entity::HandleEvents(SDL_Event* events) //can take code out of here to put it into a different ui class derived from entity, which can be clicked on.
{
	
	if (events->type == SDL_MOUSEBUTTONDOWN || events->type == SDL_MOUSEBUTTONUP) //original:  SDL_MOUSEMOTION || events->type == SDL_MOUSEBUTTONDOWN || events->type == SDL_MOUSEBUTTONUP)
	{	//get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		
		bool inside = true;
		//check if mouse is inside button
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
		/*	else if (events->type == SDL_MOUSEBUTTONUP)
			{
				ClickedOn = false;
				ClickReleased = true;
			}*/ //this code means it'll only count if we release the mouse whilst inside of the sprite
		}

		 if (events->type == SDL_MOUSEBUTTONUP)
		{
			ClickedOn = false;
			ClickReleased = true;
		} //here we can move the mouse outside of the button and release it, and it'll still work

		//In the Entity object's constructor, Clickable is by default set to false. 
		if (this->GetClickedOn() == true && this->GetClickable() == true)
		{
			std::cout << "Pressed" << std::endl;
			this->SetClickable(false);
		}


		if (this->GetClickReleased() == true)
		{
			this->SetClickable(true);
		}

	}
}







