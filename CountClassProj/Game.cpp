#include "Game.h"
#include "SDLWindow.h"
#include <SDL.h>
#include <cmath>
#include <chrono>

double UPDATE_INTERVAL;
float frameend = 0;
float framestart = 0;
bool ballSpeedZeroed = false;

double MS_PER_UPDATE = 1000 / 60;


Game::Game() : mWindow(1024, 720), mPlayer("paddle.jpg", mWindow.GetRenderer(), 500.0f, 500.0f), mPlayer2("paddle.jpg", mWindow.GetRenderer(), 900.0f, 150.0f),
mBall("be.jpg", mWindow.GetRenderer(), 100, 100, 0.001, 0)
{
	mQuit = false;
	EntityList.push_back(&mPlayer);
	EntityList.push_back(&mPlayer2);
	EntityList.push_back(&mBall);
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

	for (auto it = EntityList.begin(); it < EntityList.end(); ++it)
	{
		(*it)->Update(UPDATE_INTERVAL);
	}
	
}

void Game::Render()
{
	SDL_RenderClear(mWindow.GetRenderer());

	for (auto it = EntityList.begin(); it < EntityList.end(); ++it)
	{
		(*it)->draw(mWindow.GetRenderer());
	}

	SDL_RenderPresent(mWindow.GetRenderer());
}

std::vector<Entity*> Game::EntityList;
