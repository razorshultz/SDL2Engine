#ifndef GAME_H
#define GAME_H


#include "Player.h"
#include <assert.h>
#include "SDLWindow.h"
#include <SDL.h>
#include "Ball.h"

class Game
{

public:
	Game();
	~Game();
	void Run();
	SDL_Renderer* GetRenderer() const { return mWindow.GetRenderer(); };


private:
	void ProcessEvents();
	void Update();
	void Render();

	SDLWindow mWindow;
	SDL_Event mEvent;
	Player mPlayer;
	Player mPlayer2;
	bool mQuit;
	Ball mBall;
	




};
#endif