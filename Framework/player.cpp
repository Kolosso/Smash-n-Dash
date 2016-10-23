// This include:
#include "player.h"

Player::Player(Sprite* sprite, float posX, float posY, float velX, float velY, bool isAnimated)
: score(0)
, scoreText(0)
, resourceMax(4)
, resourceCurrent(0)
, resourceRegenRate(1)
, resourceRegenDelay(2)
, movementSpeed(1.5)
, jumpHeight(1500)
, facingAngle(0)
, dashSpeedX(2000)
, dashSpeedY(3000)
, blockDuration(0)
{
	m_pSprite = sprite;
	m_pIsAnimated = isAnimated;
	m_x = posX;
	m_y = posY;
	m_velocityX = velX;
	m_velocityX = velY;
	state = INACTIVE;
}

Player::Player(AnimatedSprite* sprite, float posX, float posY, float velX, float velY, bool isAnimated)
: score(0)
, resourceMax(4)
, resourceCurrent(0)
, resourceRegenRate(1)
, resourceRegenDelay(2)
, movementSpeed(1.5)
, jumpHeight(1500)
, facingAngle(0)
, dashSpeedX(2000)
, dashSpeedY(3000)
, blockDuration(0)
{
	scoreText = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
	m_pSpriteAnimated = sprite;
	m_pIsAnimated = isAnimated;
	m_x = posX;
	m_y = posY;
	m_velocityX = velX;
	m_velocityX = velY;
	state = INACTIVE;

}

Player::~Player()
{
	// delete score board values
	std::vector<char*>().swap(scoreText);

	Entity::~Entity();
}

void
Player::addScorePoint(int x)
{
	score += x;
}

// Getters
int
Player::GetScore()
{
	return score;
}

char*
Player::GetScoreText()
{
	if (score <= 10)
	{
		return scoreText[score];
	}
	else
	{
		return "10";
	}
}

float
Player::GetMovementSpeed()
{
	return movementSpeed;
}

float
Player::GetJumpHeight()
{
	return jumpHeight;
}

float 
Player::GetDashSpeedX()
{
	return dashSpeedX;
}

float
Player::GetDashSpeedY()
{
	return dashSpeedY;
}

float
Player::GetBlockDuration()
{
	return blockDuration;
}

// Setters
void
Player::SetScore(int x)
{
	scoreText[x];
	score = x;
}

void
Player::SetMovementSpeed(float speed)
{
	movementSpeed = speed;
}

void
Player::SetJumpHeight(float height)
{
	jumpHeight = height;
}

void
Player::SetDashSpeedX(float dashSpeedX)
{
	dashSpeedX = dashSpeedX;
}

void
Player::SetDashSpeedY(float dashSpeedY)
{
	dashSpeedY = dashSpeedY;
}

void
Player::SetBlockDuration(float duration)
{
	blockDuration = duration;
}
