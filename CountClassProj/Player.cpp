#include "Player.h"
#include <iostream>
#include <math.h>
bool repeatable = false;
int currentchan = 2;
Player::Player(std::string texfilename, SDL_Renderer* renderer, float x, float y) : Entity(texfilename, renderer, x, y, 7000.0f, 7000.0f, 5700.0f ),  downpressed(false), uppressed(false), rightpressed(false), leftpressed(false), mSound("defaultsound.wav"), mSound2("floop2.wav")
{

}

Player::Player(std::string texfilename, SDL_Renderer* renderer) : Entity(texfilename, renderer)
{
}

Player::Player()
{

}
Player::~Player()
{
}

void Player::Update(const float& UPDATE_INTERVAL)
{
	
	
	if (GetClickedOn() == true && repeatable == false)
	{
		if (Mix_Playing(1) == 0) //if channel 1 isnt playing a sound
		{
			Mix_PlayChannel(1, mSound.mSound.get(), 0); //play sound on channel 1
			repeatable = true;
		}
	}

	if (GetClickedOn() == true && Mix_Playing(1) == 1 && repeatable == true)
	{
		Mix_PlayChannel(2, mSound2.mSound.get(), 0); //play sound on channel 2
		//repeatable = false;
	}
	 

	
	


	if(GetRightPressed())
	{
		mAccelerationX = 9000.0f;
		OffsetVelocityX(this->GetAccelerationX(), UPDATE_INTERVAL);
	}

	if (GetLeftPressed())
	{
		mAccelerationX = 9000.0f;
		OffsetVelocityX(-this->GetAccelerationX(), UPDATE_INTERVAL);
	}

	if (GetDownPressed())
	{
		mAccelerationY = 9000.0f;
		OffsetVelocityY(this->GetAccelerationY(), UPDATE_INTERVAL);
	}

	if (GetUpPressed())
	{
		mAccelerationY = 9000.0f;
		OffsetVelocityY(-this->GetAccelerationY(), UPDATE_INTERVAL);
	}

	if (!GetRightPressed() && !GetLeftPressed())
	{
		mAccelerationX = 0.0f;
	}


	if (!GetDownPressed() && !GetUpPressed())
	{
		mAccelerationY = 0.0f;
	}


	/* If the player goes over the max velocity, take away 1 to keep him at the limit*/

	if (GetVelocityX() > mNaturalVelocityLimitX)
		SetVelocityX(mNaturalVelocityLimitX); //we dont want to adjust velocity by delta time when trying to set it explicity, afteral, 200.0f multiplied by a number much less than one will give us a really tiny value! 
	//this is what caused the sudden stopping
	else if (GetVelocityX() < -mNaturalVelocityLimitX)
		SetVelocityX(-mNaturalVelocityLimitX);


	if (GetVelocityY() > mNaturalVelocityLimitY)
		SetVelocityY(mNaturalVelocityLimitY);
	else if (GetVelocityY() < -mNaturalVelocityLimitY)
		SetVelocityY(-mNaturalVelocityLimitY);


	/* Apply friction - if the player is travelling and the opposite movement control is not pressed, constantly lose speed
	* until the the speed is its own distance (or more) from 0. In this case, the velocity instantly gets set to zero to brake it. */
	
		if (GetVelocityX() < 0)
		{
			OffsetVelocityX(mFriction, UPDATE_INTERVAL);

			if (0 + GetVelocityX() > 0.0f)
				SetVelocityX(0.0f);
		}

		if (GetVelocityX() > 0)
		{
			OffsetVelocityX(-mFriction, UPDATE_INTERVAL);

			if (0 + GetVelocityX() < 0.0f)
				SetVelocityX(0.0f);
		}



		if (GetVelocityY() < 0)
		{
			OffsetVelocityY(mFriction, UPDATE_INTERVAL);

			if (0 + GetVelocityY() > 0.0f)
				SetVelocityY(0.0f);
		}

		if (GetVelocityY() > 0)
		{
			OffsetVelocityY(-mFriction, UPDATE_INTERVAL);

			if (0 + GetVelocityY() < 0.0f)
				SetVelocityY(0.0f);
		}
	

	/* Increment position based on velocity */
	OffsetPositionX(GetVelocityX(), UPDATE_INTERVAL);
	OffsetPositionY(GetVelocityY(), UPDATE_INTERVAL);

	/* use positions to set the render position, finally!  */
	SetMove();

}



