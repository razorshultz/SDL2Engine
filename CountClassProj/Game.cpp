#include "Game.h"
#include "SDLWindow.h"
#include <SDL.h>
#include <cmath>

#define MAXIMUM_FRAME_RATE 60
#define MINIMUM_FRAME_RATE 15
#define UPDATE_INTERVAL (1.0 / MAXIMUM_FRAME_RATE)
#define MAX_CYCLES_PER_FRAME (MAXIMUM_FRAME_RATE / MINIMUM_FRAME_RATE)



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
	float speed = 10.0f;


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
		//in all our movement update code, we multiply the speed by the update_interval
		mPlayer.SetVelocityX(speed, UPDATE_INTERVAL);

	}


	if (mPlayer.GetLeftPressed())
	{

		mPlayer.SetVelocityX(-speed, UPDATE_INTERVAL);

	}




	if (mPlayer.GetDownPressed())
	{
		
		mPlayer.SetVelocityY(speed, UPDATE_INTERVAL);
		
	}

	if (mPlayer.GetUpPressed())
	{
		mPlayer.SetVelocityY(-speed, UPDATE_INTERVAL);
			
	}
	
	if (mPlayer.GetDownPressed() && mPlayer.GetUpPressed())
	{
		mPlayer.SetVelocityY(0.0f, UPDATE_INTERVAL);
	}

	if (!mPlayer.GetDownPressed() && !mPlayer.GetUpPressed())
	{
		mPlayer.SetVelocityY(0.0f, UPDATE_INTERVAL);
	}

	//we use this function to set the final position which we'll render at 
	mPlayer.SetMove();
}

void Game::Render()
{
	
	SDL_RenderClear(mWindow.GetRenderer());

	
	mPlayer.draw(mWindow.GetRenderer());
	mPlayer2.draw(mWindow.GetRenderer());

	SDL_RenderPresent(mWindow.GetRenderer());
}