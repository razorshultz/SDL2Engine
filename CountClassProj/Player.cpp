#include "Player.h"
#include <iostream>
#include <math.h>

Player::Player(std::string texfilename, SDL_Renderer* renderer, float x, float y) : Entity(texfilename, renderer, x, y), downpressed(false), uppressed(false), rightpressed(false), leftpressed(false)
{
	score = 0;
	mAccelerationX = 100.0f;
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
	

	if(GetRightPressed())
	{	//called lots
		OffsetVelocityX(this->GetAccelerationX(), UPDATE_INTERVAL);
	}

	if (GetLeftPressed())
	{
		OffsetVelocityX(-this->GetAccelerationX(), UPDATE_INTERVAL);
	}

	if (GetDownPressed())
	{
		OffsetVelocityY(this->GetAccelerationX(), UPDATE_INTERVAL);
	}

	if (GetUpPressed())
	{
		OffsetVelocityY(-this->GetAccelerationX(), UPDATE_INTERVAL);
	}


	/* If the player goes over the max velocity, take away 1 to keep him at the limit*/

	if (GetVelocityX() > 10.0f)
		//OffsetVelocityX(-mVelocityX+1.0f, UPDATE_INTERVAL);
		OffsetVelocityX(-mVelocityX + 1.0f, UPDATE_INTERVAL);
	else if (GetVelocityX() < -10.0f)
		OffsetVelocityX(-mVelocityX+1.0f, UPDATE_INTERVAL);

	if (GetVelocityY() > 0.5f)
		SetVelocityY(0.5f, UPDATE_INTERVAL);
	else if (GetVelocityY() < -0.5f)
		SetVelocityY(-0.5f, UPDATE_INTERVAL);


	/* Apply friction - if the player is travelling and the opposite movement control is not pressed, constantly lose speed
	* until the the speed is its own distance (or more) from 0. In this case, the velocity instantly gets set to zero to brake it. */
	if (!GetLeftPressed() && !GetRightPressed())
	{
		if (GetVelocityX() < 0)
		{
			OffsetVelocityX(0.4f, UPDATE_INTERVAL);

			if (0 + GetVelocityX() > 0.0f)
			{
				SetVelocityX(0.0f, UPDATE_INTERVAL);

			}
		}

		if (GetVelocityX() > 0)
		{
			OffsetVelocityX(-0.4f, UPDATE_INTERVAL);

			if (0 + GetVelocityX() < 0.0f)
				SetVelocityX(0.0f, UPDATE_INTERVAL);
		}
	}


	if (!GetUpPressed() && !GetDownPressed())
	{
		if (GetVelocityY() < 0)
		{
			OffsetVelocityY(0.004f, UPDATE_INTERVAL);

			if (0 + GetVelocityY() > 0.0f)
				SetVelocityY(0.0f, UPDATE_INTERVAL);
		}

		if (GetVelocityY() > 0)
		{
			OffsetVelocityY(-0.004f, UPDATE_INTERVAL);

			if (0 + GetVelocityY() < 0.0f)
				SetVelocityY(0.0f, UPDATE_INTERVAL);
		}
	}

	/* Increment position based on velocity */
	OffsetPositionX(GetVelocityX() * UPDATE_INTERVAL);
	OffsetPositionY(GetVelocityY() * UPDATE_INTERVAL);

	/* use positions to set the render position, finally!  */
	SetMove();

}



