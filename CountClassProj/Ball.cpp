#include "Ball.h"






Ball::Ball(std::string texfilename, SDL_Renderer* renderer, float x, float y,  float accelerationX, float accelerationY) : Entity(texfilename, renderer, x, y, accelerationX, accelerationY)
{


}

void Ball::Update(const float& interval)
{
	OffsetVelocityX(GetAccelerationX(), interval);

	/*if ((mBall.GetPositionX() > mWindow.GetXSize() - 100) && !ballSpeedZeroed)
	{
	mBall.SetVelocityX(-10.0f, UPDATE_INTERVAL);
	mBall.SetAccelerationX(-90.5, UPDATE_INTERVAL);
	ballSpeedZeroed = true;
	}*/

	//if x position is greater
/*	if (GetPositionX() + GetTextureWidth() > mPlayer2.GetPositionX())
	{	//if ball.Y greater than Player2.Y + player2.height, or ball.y + ball.height greater than player2.y
		if (GetPositionY() >= mPlayer2.GetPositionY() && GetPositionY() <= mPlayer2.GetPositionY() + mPlayer2.GetTextureHeight()
			|| GetPositionY() + GetTextureHeight() >= mPlayer2.GetPositionY())
		{
			mBall.SetVelocityX(-10.0f, UPDATE_INTERVAL);
			mBall.SetAccelerationX(-90.5);
			ballSpeedZeroed = true;
		}
	}*/



	if (GetVelocityX() > 20.5f)
		SetVelocityX(20.5f);

	if (GetVelocityX() < -20.5f)
		SetVelocityX(20.5f);


	OffsetPositionX(GetVelocityX(), interval);

	SetMove();
}