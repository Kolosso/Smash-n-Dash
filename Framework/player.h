#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"

#include <vector>

class Player : public Entity
{
	// Member Methods:
public:
	Player(Sprite* sprite, float posX, float posY, float velX, float velY, bool isAnimated);
	Player(AnimatedSprite* sprite, float posX, float posY, float velX, float velY, bool isAnimated);
	~Player();

	// General
	int GetScore();
	char* GetScoreText();
	void SetScore(int x);
	void addScorePoint(int x);
	// Character specific
	//int  GetResourceMax();
	//void SetResourceMax(int resMax);

	//int  GetResourceCurrent();
	//void SetResourceCurrent(int resCur);

	//float GetResourceRegenRate();
	//void  SetResourceRegenRate(float resRegR);

	//float GetResourceRegenDelay();
	//void  SetResourceRegenDelay(float resRegD);
	// Movement specific
	float GetMovementSpeed();
	void  SetMovementSpeed(float speed);

	float GetJumpHeight();
	void  SetJumpHeight(float height);

	//float GetFacingAngle();
	//void  SetFacingAngle();
	// Ability specific

	float GetDashSpeedX();
	void  SetDashSpeedX(float x);
	float GetDashSpeedY();
	void  SetDashSpeedY(float y);

	float GetBlockDuration();
	void  SetBlockDuration(float duration);

private:

protected:

	// Member Variables
public:

private:

protected:
	// General
	std::vector<char*> scoreText;
	int score;
	// Character specific
	int resourceMax;
	int resourceCurrent;
	float resourceRegenRate;
	float resourceRegenDelay;
	// Movement specific
	float movementSpeed;
	float jumpHeight;
	float facingAngle;
	// Ability specific
	float dashSpeedX;
	float dashSpeedY;
	float blockDuration;

};

#endif // __PLAYER_H__