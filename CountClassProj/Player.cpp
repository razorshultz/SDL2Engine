#include "Player.h"
#include <iostream>

Player::Player(std::string texfilename, SDL_Renderer* renderer, float x, float y) : Entity(texfilename, renderer, x, y), downpressed(false), uppressed(false), rightpressed(false), leftpressed(false)
{
	score = 0;
	mAccelerationX = 5.0f;
}

Player::Player(std::string texfilename, SDL_Renderer* renderer) : Entity(texfilename, renderer)
{
}

Player::Player()
{

}
Player::~Player()
{
}



