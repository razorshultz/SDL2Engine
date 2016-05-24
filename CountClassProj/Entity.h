#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <vector>
#include "Texture.h"
#include <SDL.h>


class Entity
{
public:
	Entity();
	Entity(std::string texfilename, SDL_Renderer* renderer);
	Entity(std::string texfilename, SDL_Renderer* renderer, float& x, float& y);
	Entity(std::string texfilename, SDL_Renderer* renderer, float& x, float& y, float mAccelerationX, float mAccelerationY);
	virtual ~Entity();

	
	void draw(SDL_Renderer* renderer) const;

	

	//set velocity of x, multiply it by our constant UPDATE_INTERVAL
	 void SetVelocityX(const float& acceleration, const float& interval);
	
	//set velocity and multiply it by our constant UPDATE_INTERVAL
	 void SetVelocityY(const float& acceleration,  const float& interval);

	 void HandleEvents(SDL_Event* event);
	
	//Used at the end of each update cycle so we know the final position of our entity, which should be used for rendering
	 void SetMove(float dt);

	 void OffsetVelocityX(float accel, const float& interval);
	 void OffsetVelocityY(float accel, const float& interval);


	 inline float GetPositionX() const { return mPositionX; };
	 inline float GetPositionY() const { return mPositionY; };

	 void OffsetPositionX(float offset);
	 void OffsetPositionY(float offset);

	 inline int GetTextureHeight() const { return mRectFrame.h; };
	 inline int GetTextureWidth() const { return mRectFrame.w; };

	//these should probably be protected, to detect clicks of derived classes 
	inline bool GetClickedOn() const { return ClickedOn; };
	inline bool GetClickReleased() const { return ClickReleased; };
	inline bool GetClickable() const { return Clickable; };
	inline void SetClickable(bool boolean) { Clickable = boolean; }
	inline float GetAccelerationX() const { return mAccelerationX; };
	inline float GetAccelerationY() const { return mAccelerationY; };
	inline float GetVelocityX() const { return mVelocityX; };
	inline float GetVelocityY() const { return mVelocityY; };

	 void SetAccelerationX(float accel, const float& interval);
	 void SetAccelerationY(float accel, const float& interval);
	 void OffsetAccelerationX(float accel, const float& interval);
	 void OffsetAccelerationY(float accel, const float& interval);
	
	 



protected:

	std::string mTexFilename;
	Texture mTexture;
	float friction;
	float mAccelerationX =0;
	float mAccelerationY =0;
	float mVelocityY =0;
	float mVelocityX = 0;
	float mPositionX = 0;
	float mPositionY = 0;

private:
	//these should probably be protected, to detect clicks of derived classes 
	SDL_Rect mRectFrame; 
	bool ClickedOn;
	bool ClickReleased;
	bool Clickable = true;
};

#endif