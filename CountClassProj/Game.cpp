#include "Game.h"
#include "SDLWindow.h"
#include <SDL.h>
#include <cmath>

#define MAXIMUM_FRAME_RATE 120
#define MINIMUM_FRAME_RATE 15
#define UPDATE_INTERVAL (float)(1.0 / MAXIMUM_FRAME_RATE)
#define MAX_CYCLES_PER_FRAME (MAXIMUM_FRAME_RATE / MINIMUM_FRAME_RATE)

const float& TimePerFrame = 1.0f / 60.0f;
bool ballSpeedZeroed = false;

Game::Game() :  mWindow(1024, 720), mPlayer("paddle.jpg", mWindow.GetRenderer(), 500.0f, 500.0f), mPlayer2("paddle.jpg", mWindow.GetRenderer(), 900.0f, 100.0f),
				mBall("be.jpg", mWindow.GetRenderer(), 100, 100, 1, 0)
{
	mQuit = false;
}

void Game::Run()
{
	while (!mQuit)
	{
		ProcessEvents();

		static double lastFrameTime = SDL_GetTicks();
		static double cyclesLeftOver = 0.0;
		double currentTime;
		double updateIterations;

		currentTime = SDL_GetTicks();
		updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);

		if (updateIterations > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
			updateIterations = (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL);
		}

		while (updateIterations > UPDATE_INTERVAL) {
			updateIterations -= UPDATE_INTERVAL;

			Update(); // Update game state a variable number of times
		}

		cyclesLeftOver = updateIterations;
		lastFrameTime = currentTime;

		Render(); // Draw the scene only once
	}
}

Game::~Game()
{

}

void Game::ProcessEvents()
{
	

	while (SDL_PollEvent(&mEvent))
	{
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (mEvent.type == SDL_QUIT)
			mQuit = true;

		if (mEvent.type == SDL_KEYDOWN)
		{
			switch(mEvent.key.keysym.sym)
			{
			case SDLK_s:
				mPlayer.SetDownPressed(true);
				break;
			case SDLK_w:
				mPlayer.SetUpPressed(true);
				break;
			case SDLK_a:
				mPlayer.SetLeftPressed(true);
				break;
			case SDLK_d:
				mPlayer.SetRightPressed(true);
				break;
			}
		}

		if (mEvent.type == SDL_KEYUP)
		{
			switch (mEvent.key.keysym.sym)
			{
			case SDLK_s:
				mPlayer.SetDownPressed(false);
				break;
			case SDLK_w:
				mPlayer.SetUpPressed(false);
				break;
			case SDLK_a:
				mPlayer.SetLeftPressed(false);
				break;
			case SDLK_d:
				mPlayer.SetRightPressed(false);
				break;
			}
		}
	}
}

void Game::Update()
{
	
    mPlayer.HandleEvents(&mEvent);

	if (mPlayer.GetRightPressed())
	{	
		mPlayer.SetAccelerationX(35.0f, UPDATE_INTERVAL);
	}

	if (mPlayer.GetLeftPressed())
	{ 	
		mPlayer.SetAccelerationX(-35.0f, UPDATE_INTERVAL);
	}

	if (mPlayer.GetDownPressed())
	{
		mPlayer.SetAccelerationY(35.0f, UPDATE_INTERVAL);
	}

	if (mPlayer.GetUpPressed())
	{
		mPlayer.SetAccelerationY(-35.0f, UPDATE_INTERVAL);	
	}
	
	

	/*if ((mBall.GetPositionX() > mWindow.GetXSize() - 100) && !ballSpeedZeroed)
	{
		mBall.SetVelocityX(-10.0f, UPDATE_INTERVAL);
		mBall.SetAccelerationX(-90.5, UPDATE_INTERVAL);
		ballSpeedZeroed = true;
	}*/
	
	if (mBall.GetPositionX() >= mPlayer2.GetPositionX() - mPlayer2.GetTextureWidth() && mBall.GetPositionY() >= mPlayer2.GetPositionY() && mBall.GetPositionY() <= mPlayer2.GetPositionY() + mPlayer2.GetTextureHeight())
	{
		mBall.SetVelocityX(-10.0f, UPDATE_INTERVAL);
		mBall.SetAccelerationX(-90.5, UPDATE_INTERVAL);
		ballSpeedZeroed = true;
	}



	/*if ((mBall.GetPositionX() < mWindow.GetXSize() - 100) && ballSpeedZeroed)
	{
		
		ballSpeedZeroed = false;
	}*/

	/* If the player goes over the max velocity, take away 1 to keep him at the limit*/
	if (mPlayer.GetVelocityX() > 20.5f)
		mPlayer.OffsetVelocityX(-1.0f, UPDATE_INTERVAL);

	if (mPlayer.GetVelocityX() < -20.5f)
		mPlayer.OffsetVelocityX(1.0f, UPDATE_INTERVAL);

	if (mPlayer.GetVelocityY() > 20.5f)
		mPlayer.OffsetVelocityY(-1.0f, UPDATE_INTERVAL);

	if (mPlayer.GetVelocityY() < -20.5f)
		mPlayer.OffsetVelocityY(1.0f, UPDATE_INTERVAL);

	if (mBall.GetVelocityX() > 10.5f)
		mBall.OffsetVelocityX(-1.0f, UPDATE_INTERVAL);

	if (mBall.GetVelocityX() < -10.5f)
		mBall.OffsetVelocityX(1.0f, UPDATE_INTERVAL);

	/* Increment player velocity by acceleration*/
	mPlayer.OffsetVelocityX(mPlayer.GetAccelerationX(), UPDATE_INTERVAL);
	mPlayer.OffsetVelocityY(mPlayer.GetAccelerationY(), UPDATE_INTERVAL);

	mBall.OffsetVelocityX(mBall.GetAccelerationX(), UPDATE_INTERVAL);

	/* Apply friction - if the player is travelling and the opposite movement control is not pressed, constantly lose speed
	** until the the speed is its own distance (or more) from 0. In this case, the velocity instantly gets set to zero to brake it. */
	if (!mPlayer.GetLeftPressed() && !mPlayer.GetRightPressed())
	{
		if (mPlayer.GetVelocityX() < 0)
		{
			mPlayer.OffsetVelocityX(0.8f, UPDATE_INTERVAL);

			if (0 + mPlayer.GetVelocityX() >= 0.0f)
				mPlayer.SetVelocityX(0.0f, UPDATE_INTERVAL);
		}
		
		 if (mPlayer.GetVelocityX() > 0)
		{
			mPlayer.OffsetVelocityX(-0.8f, UPDATE_INTERVAL);

			if (0 + mPlayer.GetVelocityX() <= 0.0f)
				mPlayer.SetVelocityX(0.0f, UPDATE_INTERVAL);
		}
	}


	if (!mPlayer.GetUpPressed() && !mPlayer.GetDownPressed())
	{
		if (mPlayer.GetVelocityY() < 0)
		{
			mPlayer.OffsetVelocityY(0.4f, UPDATE_INTERVAL);

			if (0 + mPlayer.GetVelocityY() >= 0.0f)
				mPlayer.SetVelocityY(0.0f, UPDATE_INTERVAL);
		}

		if (mPlayer.GetVelocityY() > 0)
		{
			mPlayer.OffsetVelocityY(-0.4f, UPDATE_INTERVAL);

			if (0 + mPlayer.GetVelocityY() <= 0.0f)
				mPlayer.SetVelocityY(0.0f, UPDATE_INTERVAL);
		}
	}




	/* Increment position based on velocity */
	//mPlayer's X Position += mPlayer.GetVelocityX() * UPDATE_INTERVAL;
	mPlayer.OffsetPositionX(mPlayer.GetVelocityX() * UPDATE_INTERVAL);
	mPlayer.OffsetPositionY(mPlayer.GetVelocityY() * UPDATE_INTERVAL);

	mBall.OffsetPositionX(mBall.GetVelocityX() * UPDATE_INTERVAL);
	
	/* use position to render, finally! */
	mPlayer.SetMove(UPDATE_INTERVAL);
	mBall.SetMove(UPDATE_INTERVAL);
}

void Game::Render()
{
	SDL_RenderClear(mWindow.GetRenderer());
	mPlayer.draw(mWindow.GetRenderer());
	mPlayer2.draw(mWindow.GetRenderer());
	mBall.draw(mWindow.GetRenderer());
	SDL_RenderPresent(mWindow.GetRenderer());
}