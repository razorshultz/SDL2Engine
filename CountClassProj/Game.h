#ifndef GAME_H
#define GAME_H

#include "Sound.h"
#include "Player.h"
#include <assert.h>
#include "SDLWindow.h"
#include <SDL.h>
#include "Ball.h"
#include <vector>
#include <memory>

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
	//for smart pointers, i guess this should be std::shared_ptr<Player>
	bool mQuit;
	Ball mBall;
	
	


	static std::vector<Entity*> EntityList;
	//static std::vector<std::shared_ptr<Entity>> EntityList;
	//Trying to convert my EntityList into smart pointers


};
#endif