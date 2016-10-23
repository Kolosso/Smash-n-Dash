// COMP710 GP 2D Framework

// This include:
#include "tile.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>

Tile::Tile(Sprite* sprite, float posX, float posY)
: m_pSprite(0)
, m_pSpriteWidth(0)
, m_pSpriteHeight(0)
, m_x(0.0f)
, m_y(0.0f)
, body(0)
{

}

Tile::~Tile()
{

}

bool
Tile::Initialise(Sprite* sprite, int widthSize, int heightSize)
{
	assert(sprite);
	m_pSprite = sprite;

	// Tiles that do not have physics bodies do not need to be processed each loop
	//m_pSprite->SetX(m_x);
	//m_pSprite->SetY(m_y);

	return (true);
}

bool
Tile::Initialise(Sprite* sprite, b2World* gameWorld, int widthSize, int heightSize)
{
	assert(sprite);
	m_pSprite = sprite;
	//m_pSpriteWidth = m_pSprite->GetWidth(); // currently returns full length of sprite atlas

	box2DBodyCreate(gameWorld, widthSize, heightSize);

	return (true);
}

void
Tile::box2DBodyCreate(b2World* gameWorld, int widthSize, int heightSize)
{

	b2BodyDef entityBodyDef;
	entityBodyDef.position.Set(m_x * 0.1, m_y * 0.1); // initial position based of sprite creation
	entityBodyDef.angle = 0;
	entityBodyDef.allowSleep = false;
	entityBodyDef.gravityScale = 0.0f;

	body = gameWorld->CreateBody(&entityBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(widthSize * 0.1, heightSize * 0.1); // position relative to body position

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.friction = 1000;

	body->CreateFixture(&boxFixtureDef); // add fixture to the body
}

void
Tile::Process(float deltaTime)
{
	if (body != 0)
	{
		m_pSprite->SetX((float)body->GetPosition().x * 10);
		m_pSprite->SetY((float)body->GetPosition().y * 10);
		m_x = (float)body->GetPosition().x * 10;
		m_y = (float)body->GetPosition().y * 10;
	}

	m_pSprite->SetX(m_x);
	m_pSprite->SetY(m_y);
}

void
Tile::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}


// Getters
float
Tile::GetPositionX()
{
	return (m_x);
}

float
Tile::GetPositionY()
{
	return (m_y);
}

float
Tile::GetGravity()
{
	return m_gravity;
}

b2Body*
Tile::GetBox2DBody()
{
	return body;
}

// Setters
void
Tile::SetPositionX(float x)
{
	m_x = x;
}

void
Tile::SetPositionY(float y)
{
	m_y = y;
}

void
Tile::SetGravity(float y)
{

}
