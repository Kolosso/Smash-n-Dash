// COMP710 GP 2D Framework
#ifndef __TILE_H__
#define __TILE_H__

#include <Box2D.h>

// Forward Declarations:
class BackBuffer;
class Sprite;
class AnimatedSprite;

class Tile
{
	// Member Methods:
public:
	Tile(Sprite* sprite, float posX, float posY);
	~Tile();

	bool Initialise(Sprite* sprite, b2World* gameWorld, int width, int height);
	bool Initialise(Sprite* sprite, int width, int height);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	// PositionX
	float GetPositionX();					// getPosX()
	void  SetPositionX(float x);			// setPosX(float x)
	// PositionY
	float GetPositionY();					// getPosY()
	void  SetPositionY(float y);			// setPosY(float y)

	// Gravity
	float GetGravity();
	void  SetGravity(float y);

	// Box2DBody
	b2Body* GetBox2DBody();

protected:

private:
	Tile(const Tile& tile);
	Tile& operator=(const Tile& tile);

	void box2DBodyCreate(b2World* gameWorld, int width, int height);

	// Member Data:
public:

protected:
	Sprite* m_pSprite;	// sprite

	int m_pSpriteWidth;
	int m_pSpriteHeight;

	float m_x;			// mf_posX
	float m_y;			// mf_posY

	float m_gravity;

	// Player body
	b2BodyDef entityBodyDef;
	b2Body* body;

private:

};

#endif //__TILE_H__
