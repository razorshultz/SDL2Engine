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
	void Update(double UPDATE_INTERVAL);
	inline bool GetDownPressed() const {  return downpressed;  };
	inline bool GetUpPressed() const  { return uppressed; };
	inline void SetDownPressed(bool press) { downpressed = press; };
	inline void SetUpPressed(bool press) { uppressed = press; };
	inline bool GetLeftPressed() const { return leftpressed; };
	inline bool GetRightPressed() const { return rightpressed; };
	inline void SetLeftPressed(bool press) { leftpressed = press; };
	inline void SetRightPressed(bool press) { rightpressed = press; };
	





private:

	int score;
	bool downpressed;
	bool uppressed;
	bool leftpressed;
	bool rightpressed;
	
	



};


#endif

