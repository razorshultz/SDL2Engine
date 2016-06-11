#include "Game.h"
#include "SDLWindow.h"
#include <SDL.h>
#include <cmath>


//float UPDATE_INTERVAL = 0;
double UPDATE_INTERVAL;
float frameend = 0;
float framestart = 0;
bool ballSpeedZeroed = false;

double MS_PER_UPDATE = 1000 / 60;


Game::Game() : mWindow(1024, 720), mPlayer("paddle.jpg", mWindow.GetRenderer(), 500.0f, 500.0f), mPlayer2("paddle.jpg", mWindow.GetRenderer(), 900.0f, 150.0f),
mBall("be.jpg", mWindow.GetRenderer(), 100, 100, 0.001, 0)
{
	mQuit = false;
}

void Game::Run()
{
	/*while (!mQuit)
	{

		if (UPDATE_INTERVAL < 1)
		{
			framestart = SDL_GetTicks();
			SDL_Delay(1);
			frameend = SDL_GetTicks();
			UPDATE_INTERVAL = frameend - framestart;
		}

		framestart = SDL_GetTicks();
		ProcessEvents();
		Update();
		Render();
		frameend = SDL_GetTicks();
		UPDATE_INTERVAL = frameend - framestart;

	}*/
	double previous = SDL_GetTicks();
	double lag = 0.0;
	
	while (!mQuit)
	{
		double current = SDL_GetTicks();
		UPDATE_INTERVAL = current - previous;
		previous = current;
		lag += UPDATE_INTERVAL;
		ProcessEvents();

		while (lag >= MS_PER_UPDATE)
		{
			Update();
			lag -= MS_PER_UPDATE;
		}
		
		Render();
		
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
			switch (mEvent.key.keysym.sym)
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
		mPlayer.OffsetVelocityX(mPlayer.GetAccelerationX(), UPDATE_INTERVAL);
	}

	if (mPlayer.GetLeftPressed())
	{
		mPlayer.OffsetVelocityX(-mPlayer.GetAccelerationX(), UPDATE_INTERVAL);
	}

	if (mPlayer.GetDownPressed())
	{
		mPlayer.SetAccelerationY(40.0f);
	}

	if (mPlayer.GetUpPressed())
	{
		mPlayer.SetAccelerationY(-40.0f);
	}

	
	mBall.OffsetVelocityX(mBall.GetAccelerationX(), UPDATE_INTERVAL);

	/*if ((mBall.GetPositionX() > mWindow.GetXSize() - 100) && !ballSpeedZeroed)
	{
	mBall.SetVelocityX(-10.0f, UPDATE_INTERVAL);
	mBall.SetAccelerationX(-90.5, UPDATE_INTERVAL);
	ballSpeedZeroed = true;
	}*/

	//if x position is greater
	if (mBall.GetPositionX() + mBall.GetTextureWidth() > mPlayer2.GetPositionX())
	{	//if ball.Y greater than Player2.Y + player2.height, or ball.y + ball.height greater than player2.y
		if (mBall.GetPositionY() >= mPlayer2.GetPositionY() && mBall.GetPositionY() <= mPlayer2.GetPositionY() + mPlayer2.GetTextureHeight()
			|| mBall.GetPositionY() + mBall.GetTextureHeight() >= mPlayer2.GetPositionY())
		{
			mBall.SetVelocityX(-10.0f, UPDATE_INTERVAL);
			mBall.SetAccelerationX(-90.5);
			ballSpeedZeroed = true;
		}
	}

	/* If the player goes over the max velocity, take away 1 to keep him at the limit*/
	if (mPlayer.GetVelocityX() > 5.0f)
		//mPlayer.OffsetVelocityX(-1.0f, UPDATE_INTERVAL);
		mPlayer.SetVelocityX(5.0f, UPDATE_INTERVAL);


	if (mPlayer.GetVelocityX() < -5.0f)
		mPlayer.SetVelocityX(-5.0f, UPDATE_INTERVAL);

	if (mPlayer.GetVelocityY() > 20.5f)
		mPlayer.OffsetVelocityY(-1.0f, UPDATE_INTERVAL);

	if (mPlayer.GetVelocityY() < -20.5f)
		mPlayer.OffsetVelocityY(1.0f, UPDATE_INTERVAL);

	if (mBall.GetVelocityX() > 20.5f)
		mBall.OffsetVelocityX(-1.0f, UPDATE_INTERVAL);

	if (mBall.GetVelocityX() < -20.5f)
		mBall.OffsetVelocityX(1.0f, UPDATE_INTERVAL);


	/* Apply friction - if the player is travelling and the opposite movement control is not pressed, constantly lose speed
	 * until the the speed is its own distance (or more) from 0. In this case, the velocity instantly gets set to zero to brake it. */
	if (!mPlayer.GetLeftPressed() && !mPlayer.GetRightPressed())
	{
		if (mPlayer.GetVelocityX() < 0)
		{
			mPlayer.OffsetVelocityX(0.4f, UPDATE_INTERVAL);

			if (0 + mPlayer.GetVelocityX() > 0.0f)
			{
				mPlayer.SetVelocityX(0.0f, UPDATE_INTERVAL);
				
			}
		}

		if (mPlayer.GetVelocityX() > 0)
		{
			mPlayer.OffsetVelocityX(-0.4f, UPDATE_INTERVAL);

			if (0 + mPlayer.GetVelocityX() < 0.0f)
				mPlayer.SetVelocityX(0.0f, UPDATE_INTERVAL);
		}
	}


	if (!mPlayer.GetUpPressed() && !mPlayer.GetDownPressed())
	{
		if (mPlayer.GetVelocityY() < 0)
		{
			mPlayer.OffsetVelocityY(0.004f, UPDATE_INTERVAL);

			if (0 + mPlayer.GetVelocityY() > 0.0f)
				mPlayer.SetVelocityY(0.0f, UPDATE_INTERVAL);
		}

		if (mPlayer.GetVelocityY() > 0)
		{
			mPlayer.OffsetVelocityY(-0.004f, UPDATE_INTERVAL);

			if (0 + mPlayer.GetVelocityY() < 0.0f)
				mPlayer.SetVelocityY(0.0f, UPDATE_INTERVAL);
		}
	}


	/* Increment position based on velocity */
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