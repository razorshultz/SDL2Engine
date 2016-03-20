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
	bool GetDownPressed() const { return downpressed; };
	bool GetUpPressed() const  { return uppressed; };
	void SetDownPressed(bool press) { downpressed = press; };
	void SetUpPressed(bool press) { uppressed = press; };
	bool GetLeftPressed() const { return leftpressed; };
	bool GetRightPressed() const { return rightpressed; };
	void SetLeftPressed(bool press) { leftpressed = press; };
	void SetRightPressed(bool press) { rightpressed = press; };





private:

	int score;
	bool downpressed;
	bool uppressed;
	bool leftpressed;
	bool rightpressed;



};


#endif

