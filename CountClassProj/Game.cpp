#include "Game.h"
#include "SDLWindow.h"
#include <SDL.h>

#define MAXIMUM_FRAME_RATE 120
#define MINIMUM_FRAME_RATE 15
#define UPDATE_INTERVAL (1.0 / MAXIMUM_FRAME_RATE)
#define MAX_CYCLES_PER_FRAME (MAXIMUM_FRAME_RATE / MINIMUM_FRAME_RATE)



const float& TimePerFrame = 1.0f / 60.0f;






Game::Game() :  mWindow(), mPlayer("jb.jpg", mWindow.GetRenderer(), 0.0f, 0), mPlayer2("be.jpg", mWindow.GetRenderer(), 300.0f, 300.0f)
{
	mQuit = false;

}

void Game::Run()
{
	while (!mQuit)
	{
		ProcessEvents();

		static double lastFrameTime = 0.0;
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

		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
				mPlayer.SetDownPressed(true);

		}


	}
}

void Game::Update()
{
	


	mPlayer.HandleEvents(&mEvent);

	if (mPlayer.GetClickedOn() == true && mPlayer.GetClickable() == true)
	{
		std::cout << "Pressed" << std::endl;
		mPlayer.Clickable = false;

	}

	if (mPlayer.GetClickReleased() == true)
	{

		mPlayer.Clickable = true;

	}


	if (mPlayer.GetDownPressed())
		mPlayer.SetVelocityX(300.0f);



}

void Game::Render()
{
	
	mPlayer.draw(mWindow.GetRenderer());
	mPlayer2.draw(mWindow.GetRenderer());

	SDL_RenderPresent(mWindow.GetRenderer());
}