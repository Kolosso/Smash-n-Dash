#ifndef __POWERORB_H__
#define __POWERORB_H__

#include "entity.h"

class Sprite;
class AnimatedSprite;

class PowerOrb : public Entity
{
	// Member Methods
public:
	PowerOrb(Sprite* sprite, float posX, float posY, float velX, float velY, bool isAnimated);
	PowerOrb(AnimatedSprite* sprite, float posX, float posY, float velX, float velY, bool isAnimated);
	~PowerOrb();

protected:

private:

	// Member Variables
public:
	void ProcessAI(float deltaTime);
protected:
	float m_timeElapsed;
	float m_frameSpeed;
private:

};



#endif // !__POWERORB_H__
