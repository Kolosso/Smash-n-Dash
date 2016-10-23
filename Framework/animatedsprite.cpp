// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"

AnimatedSprite::AnimatedSprite()
: m_frameSpeed(0.075)
, m_frameWidth(32)
, m_timeElapsed(0.0f)
, m_currentFrame(0)
, m_frameCountSprite(0)
, frameCoords(0)
, m_paused(false)
, m_loop(false)
, m_animating(false)
{

}

AnimatedSprite::~AnimatedSprite()
{
	//std::vector<int>().swap(frameCoords);
	//Sprite::~Sprite();
}

bool
AnimatedSprite::Initialise(Texture& texture)
{

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	int numOfFrames = texture.GetWidth() / m_frameWidth;
	int frameCoord = 0;
	for (int f = 0; f < numOfFrames; f++)
	{
		frameCoord = f * m_frameWidth;
		AddFrame( frameCoord );
	}

	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	// W02.4: Add the x coordinate to the frame coordinate container.
	frameCoords.push_back( x );
}

void
AnimatedSprite::Process(float deltaTime)
{
	// W02.4: If not paused...
	// W02.4: Count the time elapsed.
	m_timeElapsed += deltaTime;

	// W02.4: If the time elapsed is greater than the frame speed.
	// Frame Counter:
	if (m_timeElapsed >= m_frameSpeed)
	{
		//m_FPS = m_frameCount;
		//m_frameCount = 0;

		// W02.4: Move to the next frame.
		m_currentFrame = frameCoords[m_frameCountSprite];
		++m_frameCountSprite;
		
		// W02.4: Reset the time elapsed counter.
		m_timeElapsed = 0;
		// W02.4: If the current frame is greater than the number 
		//          of frame in this animation...
		// W02.4: Reset to the first frame.
		if (m_frameCountSprite >= 5)
		{
			m_frameCountSprite = 0;
		}
		// W02.4: Stop the animation if it is not looping...
	}
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	
	
	// W02.4: Draw the particular frame into the backbuffer.
	backbuffer.DrawSpriteAnimated(*this, m_currentFrame, m_frameWidth);
	//          What is the current frame's x coordinate?
	//          What is the frame width?
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}