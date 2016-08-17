#ifndef BALL_H
#define BALL_H

#include "Entity.h"


class Ball : public Entity
{
	public:
		Ball(std::string texfilename, SDL_Renderer* renderer, float x, float y, float accelerationX, float accelerationY);
		void Update(const float& UPDATE_INTERVAL) override;


};

#endif
