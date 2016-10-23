// This includes:
#include "powerorb.h"

#include <stdlib.h>
#include <time.h>

PowerOrb::PowerOrb(Sprite* sprite, float posX, float posY, float velX, float velY, bool isAnimated)
: m_frameSpeed(1.0f)
, m_timeElapsed(0.0f)
{
	m_pIsAnimated = isAnimated;
	SetGravityScale(0.0f);
	srand(time(NULL));
}

PowerOrb::PowerOrb(AnimatedSprite* sprite, float posX, float posY, float velX, float velY, bool isAnimated)
: m_frameSpeed(2.0f)
, m_timeElapsed(0.0f)
{
	m_pIsAnimated = isAnimated;
	SetGravityScale(0.0f);
	srand(time(NULL));
}

void
PowerOrb::ProcessAI(float deltaTime)
{
	m_timeElapsed += deltaTime;

	// W02.4: If the time elapsed is greater than the frame speed.
	// Frame Counter:
	if (m_timeElapsed >= m_frameSpeed)
	{
		//m_FPS = m_frameCount;
		//m_frameCount = 0;

		// W02.4: Move to the next frame.
		if (m_x < 200)
		{
			m_velocityX = rand() % 7 + (3);
		}
		else if (m_x > 600)
		{
			m_velocityX = rand() % -7 + (-3);
		}
		else
		{
			m_velocityX = rand() % 3 + (-1);
		}

		if (m_y < 200)
		{
			m_velocityY = rand() % 7 + (3);
		}
		else if (m_y > 400)
		{
			m_velocityY = rand() % -7 + (-3);
		}
		else
		{
			m_velocityY = rand() % 3 + (-1);
		}

		// W02.4: Reset the time elapsed counter.
		m_timeElapsed = 0;
		// W02.4: If the current frame is greater than the number 
		//          of frame in this animation...
		// W02.4: Reset to the first frame.
		// W02.4: Stop the animation if it is not looping...
	}
}