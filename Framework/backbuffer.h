// COMP710 GP 2D Framework
#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Forward Declarations:
class TextureManager;
class Sprite;
class AnimatedSprite;
struct SDL_Window;
struct SDL_Renderer;

class BackBuffer
{
	//Member Methods:
public:
	BackBuffer();
	~BackBuffer();

	bool Initialise(int width, int height);

	void Clear();
	void Present();

	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);

	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void DrawText(SDL_Color colour, const char* string, int posX, int posY, int width, int height);
	void DrawSprite(Sprite& sprite);
	void DrawSpriteAnimated(AnimatedSprite& sprite, int currentFrameX, int frameWidth);
	void DrawRectangle(int x1, int y1, int x2, int y2);
	void DrawLine(int x1, int y1, int x2, int y2);

	Sprite* CreateSprite(const char* pcFilename);
	AnimatedSprite* CreateSpriteAnimated(const char* pcFilename);
	
protected:
	void LogSDLError();

private:
	BackBuffer(const BackBuffer& backBuffer);
	BackBuffer& operator=(const BackBuffer& backBuffer);

	//Member Data:
public:

protected:
	TextureManager* m_pTextureManager;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	//SDL_Surface* surface;
	//SDL_Texture* texture;
	TTF_Font* font;

	int m_width;
	int m_height;

	unsigned char m_clearRed;
	unsigned char m_clearGreen;
	unsigned char m_clearBlue;
	
private:

};

#endif // __BACKBUFFER_H__
