// COMP710 GP 2D Framework
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <Box2D.h>

// Forward Declarations:
class BackBuffer;
class Sprite;
class AnimatedSprite;

// Enumeration types
enum EntityState
{
	ALIVE, DEAD, INACTIVE, BLOCKING
};

class Entity
{
	// Member Methods:
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite, b2World* gameWorld);		// setSprite(Sprite* sprite)
	bool Initialise(AnimatedSprite* sprite, b2World* gameWorld);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead() const;					// TODO May be redundant due to EntityState. Remove variable too

	bool IsCollidingWith(Entity& e);
	bool IsCollidingWithOrb(Entity& e);

	// PositionX
	float GetPositionX();					// getPosX()
	void  SetPositionX(float x);			// setPosX(float x)
	// PositionY
	float GetPositionY();					// getPosY()
	void  SetPositionY(float y);			// setPosY(float y)

	// VelocityX
	float GetHorizontalVelocity();			// getVelX()
	void  SetHorizontalVelocity(float x);	// setVelX(float x)
	// VelocityY
	float GetVerticalVelocity();			// getVelY()
	void  SetVerticalVelocity(float y);		// setVelY(float y)

	// Gravity
	float SetGravityScale();
	void  SetGravityScale(float g);

	// Box2DBody
	b2Body* GetBox2DBody();

	// AliveState
	EntityState GetState();
	void		SetState(EntityState state);

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	void box2DBodyCreate(b2World* gameWorld);

	// Member Data:
public:

protected:
	Sprite* m_pSprite;	// sprite
	AnimatedSprite* m_pSpriteAnimated;

	int m_pSpriteWidth;

	float m_x;			// mf_posX
	float m_y;			// mf_posY

	float m_velocityX;	// mf_velocityX
	float m_velocityY;	// mf_velocityY

	float m_gravityScale;
	
	bool m_pIsAnimated;
	bool m_dead;		// TODO May be redundant due to EntityState. Remove method too

	// Player body
	b2Body* dynamicBody;

	EntityState state;

private:

};

#endif //__ENTITY_H__
