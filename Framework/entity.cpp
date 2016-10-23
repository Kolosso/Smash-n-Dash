// COMP710 GP 2D Framework

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "backbuffer.h"
#include <math.h>

// Library includes:
#include <cassert>

Entity::Entity()
: m_pSprite(0)
, m_pSpriteAnimated(0)
, m_pSpriteWidth(16)
, m_pIsAnimated(true)
, m_gravityScale(1)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
, state(INACTIVE)
, dynamicBody(0)
{

}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = 0;
	delete m_pSpriteAnimated;
	m_pSpriteAnimated = 0;
	
	//dynamicBody->DestroyFixture(dynamicBody->GetFixtureList());
	//delete &dynamicBody;
	//dynamicBody = 0;
}

bool
Entity::Initialise(Sprite* sprite, b2World* gameWorld)
{
	assert(sprite);
	m_pSprite = sprite;

	box2DBodyCreate(gameWorld);

	return (true);
}

bool
Entity::Initialise(AnimatedSprite* sprite, b2World* gameWorld)
{
	assert(sprite);
	m_pSpriteAnimated = sprite;

	box2DBodyCreate(gameWorld);

	return (true);
}

void
Entity::box2DBodyCreate(b2World* gameWorld)
{
	b2BodyDef entityBodyDef;
	entityBodyDef.type = b2_dynamicBody;
	entityBodyDef.position.Set(m_x * 0.1, m_y * 0.1);
	entityBodyDef.angle = 0;
	entityBodyDef.allowSleep = false;
	entityBodyDef.gravityScale = m_gravityScale;

	dynamicBody = gameWorld->CreateBody(&entityBodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); // position relative to body position
	circleShape.m_radius = (m_pSpriteWidth *0.75 )* 0.1;

	b2FixtureDef circleFixtureDef;
	circleFixtureDef.shape = &circleShape;
	circleFixtureDef.density = 1.0f;
	circleFixtureDef.friction = 1000;

	dynamicBody->CreateFixture(&circleFixtureDef); // add fixture to the body
	
	dynamicBody->SetLinearDamping(5); // Used to bring moving objects to a stop

}

void 
Entity::Process(float deltaTime)
{
	if (!m_pIsAnimated) // NOT Animated Sprite
	{
		m_pSprite->SetX((float)dynamicBody->GetPosition().x * 10);
		m_pSprite->SetY((float)dynamicBody->GetPosition().y * 10);
		m_x = (float)dynamicBody->GetPosition().x * 10;
		m_y = (float)dynamicBody->GetPosition().y * 10;
	}
	if (m_pIsAnimated) // Animated Sprite
	{
		m_pSpriteAnimated->Process(deltaTime);
		m_pSpriteAnimated->SetX((float)dynamicBody->GetPosition().x * 10);
		m_pSpriteAnimated->SetY((float)dynamicBody->GetPosition().y * 10);
		m_x = (float)dynamicBody->GetPosition().x * 10;
		m_y = (float)dynamicBody->GetPosition().y * 10;
	}
}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	if (!m_dead) // Only draw alive entities
	{
		if (!m_pIsAnimated) // NOT Animated Sprite
		{
			assert(m_pSprite);
			m_pSprite->Draw(backBuffer);
		}
		if (m_pIsAnimated) // Animated Sprite
		{
			assert(m_pSpriteAnimated);
			m_pSpriteAnimated->Draw(backBuffer);
		}
	}
}

bool
Entity::IsCollidingWith(Entity& e)
{
	// parameters
	float extraPunchRange = 3;
	float r1 = m_pSpriteWidth + extraPunchRange;
	float r2 = m_pSpriteWidth + extraPunchRange;
	float x1 = GetPositionX();
	float x2 = e.GetPositionX();
	float y1 = GetPositionY();
	float y2 = e.GetPositionY();
	
	// W02.3: Generic Entity Collision routine.
	// W02.3: Check for intersection.
	// W02.3: Using circle-vs-circle collision detection.
	float num = sqrt( pow((x2-x1),2) + ( pow((y2-y1),2) ) )-r1-r2;
		
	// Also check player is not colliding with himself
	return (num<0 && this != &e); // W02.4 Change return value!
}

bool
Entity::IsCollidingWithOrb(Entity& e)
{
	// parameters
	float extraPunchRange = 0;
	float r1 = m_pSpriteWidth + extraPunchRange;
	float r2 = m_pSpriteWidth + extraPunchRange;
	float x1 = GetPositionX();
	float x2 = e.GetPositionX();
	float y1 = GetPositionY();
	float y2 = e.GetPositionY();

	// W02.3: Generic Entity Collision routine.
	// W02.3: Check for intersection.
	// W02.3: Using circle-vs-circle collision detection.
	float num = sqrt(pow((x2 - x1), 2) + (pow((y2 - y1), 2))) - r1 - r2;

	// Also check player is not colliding with himself
	return (num<0 && this != &e); // W02.4 Change return value!
}

// Getters
float 
Entity::GetPositionX()
{
	return (m_x);
}

float 
Entity::GetPositionY()
{
	return (m_y);
}

float 
Entity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity()
{
	return (m_velocityY);
}

float
Entity::SetGravityScale()
{
	return m_gravityScale;
}

b2Body*
Entity::GetBox2DBody()
{
	return dynamicBody;
}

EntityState
Entity::GetState()
{
	return state;
}

// Setters
void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

void
Entity::SetGravityScale(float g)
{
	m_gravityScale = g;
}

void
Entity::SetState(EntityState newState)
{
	if (state == BLOCKING)
	{
		state = ALIVE;
	}
	else
	{
		state = BLOCKING;
	}
}

void
Entity::SetDead(bool dead)
{
	m_dead = dead;
}
