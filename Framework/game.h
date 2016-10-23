// COMP710 GP 2D Framework
#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#include <Box2D.h>
#include <vector>

#include "tile.h"
#include "player.h"
#include "powerorb.h"

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class AnimatedSprite;
class AudioManager;
class LevelManager;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool NewGame();
	bool DoGameLoop();
	void VictoryCond(Player* player0, Player* player1, Player* player2, Player* player3);
	void VictoryScreen();
	void Quit();

	void VolumeAdjust(bool v);

	void MovePlayerLeft(Player* player);
	void MovePlayerRight(Player* player);
	void StopPlayer(Player* player);
	void PlayerDies(Player* player);

	void Jump(Player* player);
	void Dash(Player* player, int xAxis, int yAxis);
	void Punch(Player* player);
	void Block(Player* player);

	void MovePowerOrb(PowerOrb* powerOrb);
	void CollideWithOrb(Player* player);

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void LevelBuild();
	//void LevelCollisionObject(float bodyDefPosX, float bodyDefPosY, float bodyShapeWidth, float bodyShapeHeight);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:

protected:
	// Game resolution
	const float width;
	const float height;

	int m_pointToWin;
	bool isWon;

	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	AudioManager* m_pAudioManager;
	LevelManager* m_pLevelManager;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Game Entities:
	// W02.1: Add a PlayerShip field.
	Player* player0;
	Player* player1;
	Player* player2;
	Player* player3;

	PowerOrb* powerOrb0;
	PowerOrb* powerOrb1;

	std::vector<Tile*> tiles;

	SDL_Color p0TextCol;
	SDL_Color p1TextCol;
	SDL_Color p2TextCol;
	SDL_Color p3TextCol;

	// Game World
	b2World* gameWorld;
	// W02.2: Add an alien enemy container field.
	// W02.3: Add a bullet container field.

private:

};

#endif // __GAME_H__
