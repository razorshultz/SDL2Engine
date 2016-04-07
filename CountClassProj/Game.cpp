#include "Game.h"
#include "SDLWindow.h"
#include <SDL.h>
#include <cmath>

#define MAXIMUM_FRAME_RATE 120
#define MINIMUM_FRAME_RATE 15
#define UPDATE_INTERVAL (1.0 / MAXIMUM_FRAME_RATE)
#define MAX_CYCLES_PER_FRAME (MAXIMUM_FRAME_RATE / MINIMUM_FRAME_RATE)

float speed = 0.009f;
float minusspeed = -0.009f;
float zero = 0;

const float& TimePerFrame = 1.0f / 60.0f;






Game::Game() :  mWindow(), mPlayer("be.jpg", mWindow.GetRenderer(), 0.0f, 0), mPlayer2("be.jpg", mWindow.GetRenderer(), 300.0f, 300.0f)
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

	if (mPlayer.GetClickedOn() == true && mPlayer.GetClickable() == true)
	{
		std::cout << "Pressed" << std::endl;
		mPlayer.SetClickable(false);

	}

	if (mPlayer.GetClickReleased() == true)
	{
		mPlayer.SetClickable(true);
	}

	if (mPlayer.GetRightPressed())
	{	
		//if the player is moving in the opposite direction (in which case its acceleration will be in the negative, set the acceleration to 0 so we can begin moving in the positive direction
		//if (mPlayer.GetAccelerationX() < 0)
		//	mPlayer.SetAccelerationX(0);

		//after acceleration is stopped, we now need to start moving in the positive. We increment the acceleration, rather than replacing the value. (i.e, acceleration += acceleration * interval
		mPlayer.OffsetAccelerationX(0.5f * UPDATE_INTERVAL);

		//then we set the velocity (change of position) using acceleration and multiplying it by the interval
		mPlayer.SetVelocityX(mPlayer.GetAccelerationX(), UPDATE_INTERVAL);
	}

	if (mPlayer.GetLeftPressed())
	{ 	
	//	if (mPlayer.GetAccelerationX() > 0)
		//	mPlayer.SetAccelerationX(0);

		mPlayer.OffsetAccelerationX(-0.5f * UPDATE_INTERVAL);
		mPlayer.SetVelocityX(mPlayer.GetAccelerationX(),   UPDATE_INTERVAL);

	}

	if (mPlayer.GetDownPressed())
	{
		if (mPlayer.GetAccelerationY() < 0)
			mPlayer.SetAccelerationY(0);

		mPlayer.OffsetAccelerationY(0.5f * UPDATE_INTERVAL);
		mPlayer.SetVelocityY(mPlayer.GetAccelerationY(), UPDATE_INTERVAL);
	}

	if (mPlayer.GetUpPressed())
	{
		if (mPlayer.GetAccelerationY() > 0)
			mPlayer.SetAccelerationY(0);

		mPlayer.OffsetAccelerationY(-0.5f * UPDATE_INTERVAL);
		mPlayer.SetVelocityY(mPlayer.GetAccelerationY(), UPDATE_INTERVAL);	
	}
	
	if (mPlayer.GetDownPressed() && mPlayer.GetUpPressed())
	{
		mPlayer.SetVelocityY(0.0f,  UPDATE_INTERVAL);
	}

	if (!mPlayer.GetDownPressed() && !mPlayer.GetUpPressed())
	{
		mPlayer.SetVelocityY(0.0f, UPDATE_INTERVAL);
	}

	if (!mPlayer.GetLeftPressed() && !mPlayer.GetRightPressed())
	{

		//mPlayer.SetAccelerationX(0);
	}

	if (!mPlayer.GetDownPressed() && !mPlayer.GetUpPressed() && !mPlayer.GetLeftPressed() && !mPlayer.GetRightPressed())
	{
	
	}

	//we use this function to set the final position which we'll render at 
	mPlayer.SetMove(UPDATE_INTERVAL);
}

void Game::Render()
{
	SDL_RenderClear(mWindow.GetRenderer());
	mPlayer.draw(mWindow.GetRenderer());
	mPlayer2.draw(mWindow.GetRenderer());
	SDL_RenderPresent(mWindow.GetRenderer());
}