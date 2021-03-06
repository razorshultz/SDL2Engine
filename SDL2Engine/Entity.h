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
	Entity(std::string texfilename, SDL_Renderer* renderer, float& x, float& y, float naturalvelocityx, float naturalvelocityy, float friction);

	virtual ~Entity();

	
	virtual void draw(SDL_Renderer* renderer) const;
	virtual void Update(const float& UPDATE_INTERVAL) = 0;
	

	//set velocity of x, multiply it by our constant UPDATE_INTERVAL
	 void SetVelocityX(const float& acceleration);
	
	//set velocity and multiply it by our constant UPDATE_INTERVAL
	 void SetVelocityY(const float& acceleration);


	 void HandleEvents(SDL_Event* event);
	
	//Used at the end of each update cycle so we know the final position of our entity, which should be used for rendering
	 void SetMove();

	 void OffsetVelocityX(float accel, const float& interval);

	 void OffsetVelocityY(float accel, const float& interval);


	 inline float GetPositionX() const { return mPositionX; };
	 inline float GetPositionY() const { return mPositionY; };

	 void OffsetPositionX(float velocity, const float& interval);
	 void OffsetPositionY(float velocity, const float& interval);

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

	 void SetAccelerationX(float accel);
	 void SetAccelerationY(float accel);
	 void OffsetAccelerationX(float accel, const float& interval);
	 void OffsetAccelerationY(float accel, const float& interval);
	
	 



protected:

	std::string mTexFilename;
	Texture mTexture;
	float mFriction;
	float mAccelerationX =0;
	float mAccelerationY =0;
	float mVelocityY =0;
	float mVelocityX = 0;
	float mPositionX = 0;
	float mPositionY = 0;

	float mNaturalVelocityLimitX;
	float mNaturalVelocityLimitY;


private:
	//these should probably be protected, to detect clicks of derived classes 
	SDL_Rect mRectFrame; 
	bool ClickedOn = false;
	bool ClickReleased = false;
	bool Clickable = true;
};

#endif