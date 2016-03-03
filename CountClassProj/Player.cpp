#include "Player.h"
#include <iostream>

Player::Player(std::string texfilename, SDL_Renderer* renderer, float x, float y) : Entity(texfilename, renderer, x, y)
{
	score = 0;



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



