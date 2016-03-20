#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <string>

class Player : public Entity
{
public:
	Player();
	Player(std::string texfilename, SDL_Renderer* renderer);
	Player(std::string texfilename, SDL_Renderer* renderer, float x, float y);
	~Player();
	bool GetDownPressed() { return downpressed; };
	bool GetUpPressed() { return uppressed; };
	void SetDownPressed(bool press) { downpressed = press; };
	void SetUpPressed(bool press) { uppressed = press; };





private:

	int score;
	bool downpressed;
	bool uppressed;



};


#endif

