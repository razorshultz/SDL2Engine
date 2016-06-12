#include "Game.h"
#include "SDLWindow.h"
#include <SDL.h>
#include <cmath>
#include <chrono>
#include <windows.h>


float UPDATE_INTERVAL = 1;
const int TICKS_PER_SECOND = 25;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;
int loops;
float interpolation;

Game::Game() : mWindow(1024, 720), mPlayer("paddle.jpg", mWindow.GetRenderer(), 500.0f, 500.0f), mPlayer2("paddle.jpg", mWindow.GetRenderer(), 900.0f, 150.0f),
mBall("be.jpg", mWindow.GetRenderer(), 100, 100, 0.001, 0)
{
	mQuit = false;
	EntityList.push_back(&mPlayer);
	EntityList.push_back(&mPlayer2);
	EntityList.push_back(&mBall);
}

void Game::Run()
{	DWORD nextGameTick = SDL_GetTicks();
	while (!mQuit)
	{

		loops = 0;
		while (SDL_GetTicks() > nextGameTick && loops < MAX_FRAMESKIP)
		{
			ProcessEvents();
			Update();
			nextGameTick += SKIP_TICKS;
			loops++;
		}

		interpolation = float(SDL_GetTicks() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);
		Render(interpolation);
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

void Game::Render(float interp)
{
	SDL_RenderClear(mWindow.GetRenderer());

	for (auto it = EntityList.begin(); it < EntityList.end(); ++it)
	{
		(*it)->draw(mWindow.GetRenderer(), interp);
	}

	SDL_RenderPresent(mWindow.GetRenderer());
}

std::vector<Entity*> Game::EntityList;
