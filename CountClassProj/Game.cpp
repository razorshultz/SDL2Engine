#include "Game.h"
#include "SDLWindow.h"
#include <SDL.h>
#include <memory>
#include <windows.h>


float UPDATE_INTERVAL = 0;


float frameend = 0;
float framestart = 0;
bool ballSpeedZeroed = false;



Game::Game() : mWindow(1280, 720), mPlayer("scorpion.png", mWindow.GetRenderer(), 500.0f, 500.0f), mPlayer2("bg.png", mWindow.GetRenderer(), 0.0f, 0.0f),
mBall("be.jpg", mWindow.GetRenderer(), 100, 100, 0.001, 0)
{
	mQuit = false;
	EntityList.push_back(&mPlayer2);
	EntityList.push_back(&mPlayer);
	EntityList.push_back(&mBall);
	//what to do here to make it all smart pointers?
	

}
void Game::Run()
{
	while (!mQuit)
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
	UPDATE_INTERVAL /= 1000;
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
//std::vector<std::shared_ptr<Entity>> Game::EntityList;
//using smart pointers


