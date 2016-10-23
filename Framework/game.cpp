// COMP710 GP 2D Framework

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "audiomanager.h"
#include "levelmanager.h"
#include "logmanager.h"
#include "entity.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

// Static Members:
Game* Game::sm_pInstance = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_pAudioManager(0)
, m_pLevelManager(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
, m_pointToWin(10)
, isWon(false)
, width(800)
, height(600)
, p0TextCol({ 90, 236, 13 })
, p1TextCol({ 246, 147, 79 })
, p2TextCol({ 75, 126, 235 })
, p3TextCol({ 209, 13, 236 })
{
	
}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
	delete m_pInputHandler;
	m_pInputHandler = 0;
	delete m_pAudioManager;
	m_pAudioManager = 0;
	delete m_pLevelManager;
	m_pLevelManager = 0;

	delete player0;
	player0 = 0;
	delete player1;
	player1 = 0;
	delete player2;
	player2 = 0;
	delete player3;
	player3 = 0;
	
	gameWorld->DestroyBody(gameWorld->GetBodyList());
	delete gameWorld;
	gameWorld = 0;

	
}

bool 
Game::Initialise()
{
	srand(time(NULL));

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}
	
	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	m_pAudioManager = new AudioManager();
	if (!m_pAudioManager->Initialise())
	{
		LogManager::GetInstance().Log("AudioManager Init Fail!");
		return (false);
	}

	m_pLevelManager = new LevelManager();
	if (!m_pLevelManager->Initialise())
	{
		LogManager::GetInstance().Log("LevelManager Init Fail!");
		return (false);
	}

	// Music
	m_pAudioManager->PlayMusic();
	
	// Box2D
	const b2Vec2 gravity(0, 300.0f);

	gameWorld = new b2World(gravity);

	LevelBuild();
	tiles = m_pLevelManager->GetTiles();
		
	// W02.1: Load the player sprite.
	AnimatedSprite* pPlayerSprite0 = m_pBackBuffer->CreateSpriteAnimated("assets\\player1.png");
	AnimatedSprite* pPlayerSprite1 = m_pBackBuffer->CreateSpriteAnimated("assets\\player2.png");
	AnimatedSprite* pPlayerSprite2 = m_pBackBuffer->CreateSpriteAnimated("assets\\player3.png");
	AnimatedSprite* pPlayerSprite3 = m_pBackBuffer->CreateSpriteAnimated("assets\\player4.png");

	AnimatedSprite* pPowerOrbSprite0 = m_pBackBuffer->CreateSpriteAnimated("assets\\powerOrb.png");
	AnimatedSprite* pPowerOrbSprite1 = m_pBackBuffer->CreateSpriteAnimated("assets\\powerOrb.png");

	assert(pPlayerSprite0);
	assert(pPlayerSprite1);
	assert(pPlayerSprite2);
	assert(pPlayerSprite3);

	// W02.1: Create the player.
	player0 = new Player(pPlayerSprite0, 0.0f, 0.0f, 0.0f, 0.0f, true);
	player1 = new Player(pPlayerSprite1, 0.0f, 0.0f, 0.0f, 0.0f, true);
	player2 = new Player(pPlayerSprite2, 0.0f, 0.0f, 0.0f, 0.0f, true);
	player3 = new Player(pPlayerSprite3, 0.0f, 0.0f, 0.0f, 0.0f, true);

	powerOrb0 = new PowerOrb(pPowerOrbSprite0, 0.0f, 0.0f, 0.0f, 0.0f, true);
	powerOrb1 = new PowerOrb(pPowerOrbSprite1, 0.0f, 0.0f, 0.0f, 0.0f, true);
	
	player0->SetPositionX(160);
	player0->SetPositionY(50);
	player0->Initialise(pPlayerSprite0, gameWorld);
	
	player1->SetPositionX(608);
	player1->SetPositionY(50);
	player1->Initialise(pPlayerSprite1, gameWorld);

	player2->SetPositionX(160);
	player2->SetPositionY(525);
	player2->Initialise(pPlayerSprite2, gameWorld);

	player3->SetPositionX(608);
	player3->SetPositionY(525);
	player3->Initialise(pPlayerSprite3, gameWorld);

	powerOrb0->SetPositionX(width / 2 -48);
	powerOrb0->SetPositionY(height / 2 -16);
	powerOrb0->Initialise(pPowerOrbSprite0, gameWorld);

	powerOrb1->SetPositionX(width / 2 +16);
	powerOrb1->SetPositionY(height / 2 -16);
	powerOrb1->Initialise(pPowerOrbSprite1, gameWorld);
	
	// W02.2: Fill the container with these new objects.

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	return (true);
}

bool
Game::NewGame()
{
	isWon = false;

	// Reposition Players and Reset scores
	player0->GetBox2DBody()->SetTransform(b2Vec2(160 / 10, 50 / 10), true);
	player0->SetScore(0);

	player1->GetBox2DBody()->SetTransform(b2Vec2(608 / 10, 50 / 10), true);
	player1->SetScore(0);

	player2->GetBox2DBody()->SetTransform(b2Vec2(160 / 10, 525 / 10), true);
	player2->SetScore(0);

	player3->GetBox2DBody()->SetTransform(b2Vec2(608 / 10, 525 / 10), true);
	player3->SetScore(0);

	powerOrb0->GetBox2DBody()->SetTransform(b2Vec2((width / 2 - 48) / 10, (height / 2 - 16) / 10), true);
	powerOrb1->GetBox2DBody()->SetTransform(b2Vec2((width / 2 + 16) / 10, (height / 2 - 16) / 10), true);

	return (true);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;
	const int velocityIterations = 6;
	const int positionIterations = 2;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this, player0, player1, player2, player3);
	
	if (m_looping)
	{
		int x = rand() % (4 - 1 + 1);
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_pAudioManager->Update();

			gameWorld->Step(stepSize, velocityIterations, positionIterations); // box2d
			
			m_lag -= stepSize;

			++m_numUpdates;
		}
		
		Draw(*m_pBackBuffer);
	}

	// Victory Condition Check
	VictoryCond(player0, player1, player2, player3);

	SDL_Delay(1);

	return (m_looping);
}

void 
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Update the game world simulation:
	
	// Update tile (Primarily for tiles with physics bodies
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->Process(deltaTime);
	}

	// W02.1: Update player...
	player0->Process(deltaTime);
	player1->Process(deltaTime);
	player2->Process(deltaTime);
	player3->Process(deltaTime);

	// Update power orb
	powerOrb0->ProcessAI(deltaTime);
	powerOrb1->ProcessAI(deltaTime);
	powerOrb0->Process(deltaTime);
	powerOrb1->Process(deltaTime);
	MovePowerOrb(powerOrb0);
	MovePowerOrb(powerOrb1);

	CollideWithOrb(player0);
	CollideWithOrb(player1);
	CollideWithOrb(player2);
	CollideWithOrb(player3);
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	// Draw all tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->Draw(backBuffer);
	}

	// Trying to change score int to char*. Cant get score to increment.
	//std::string s = std::to_string(player1->GetScore());
	//const char* str = s.c_str();

	// W02.1: Draw the player...
	player0->Draw(backBuffer);
	player1->Draw(backBuffer);
	player2->Draw(backBuffer);
	player3->Draw(backBuffer);
	
	// Draw Power orb
	powerOrb0->Draw(backBuffer);
	powerOrb1->Draw(backBuffer);

	// Draw scores text
	m_pBackBuffer->DrawText(p0TextCol, player0->GetScoreText(), (width / 2) - 60 - 20, 7, 20, 20);
	m_pBackBuffer->DrawText(p1TextCol, player1->GetScoreText(), (width / 2) - 15 - 20, 7, 20, 20);
	m_pBackBuffer->DrawText(p2TextCol, player2->GetScoreText(), (width / 2) + 15, 7, 20, 20);
	m_pBackBuffer->DrawText(p3TextCol, player3->GetScoreText(), (width / 2) + 60, 7, 20, 20);

	// Victory screen
	if (isWon)
	{
		VictoryScreen();
		m_pBackBuffer->DrawText({ 255, 255, 255 }, "F5 to Restart. F8 to Quit.", 250, 520, 300, 60);
	}
	// Music credits // // Music by Eric Matyas    www.soundimage.org
	m_pBackBuffer->DrawText({ 0, 0, 0 }, "Music by Eric Matyas: www.soundimage.org", 480, 580, 300, 15);

	backBuffer.Present();
}

void
Game::VictoryCond(Player* player0, Player* player1, Player* player2, Player* player3)
{
	if (player0->GetScore() >= m_pointToWin || player1->GetScore() >= m_pointToWin || player2->GetScore() >= m_pointToWin || player3->GetScore() >= m_pointToWin)
	{
		//m_looping = false;
		isWon = true;
	}
}

void
Game::VictoryScreen()
{
	if (player0->GetScore() >= m_pointToWin)
	{
		m_pBackBuffer->DrawText({ 255, 255, 255 }, "Player 1 WINS!", 275, 320, 250, 75);
	}
	else if (player1->GetScore() >= m_pointToWin)
	{
		m_pBackBuffer->DrawText({ 255, 255, 255 }, "Player 2 WINS!", 275, 320, 250, 75);
	}
	else if (player2->GetScore() >= m_pointToWin)
	{
		m_pBackBuffer->DrawText({ 255, 255, 255 }, "Player 3 WINS!", 275, 320, 250, 75);
	}
	else if (player3->GetScore() >= m_pointToWin)
	{
		m_pBackBuffer->DrawText({ 255, 255, 255 }, "Player 4 WINS!", 275, 320, 250, 75);
	}
}

void 
Game::Quit()
{
	m_looping = false;
}

void
Game::VolumeAdjust(bool v)
{
	if (v)
	{
		m_pAudioManager->VolumeUp();
	}
	else if (!v)
	{
		m_pAudioManager->VolumeDown();
	}
}

// Player movement
void 
Game::MovePlayerLeft(Player* player)
{
	// W02.1: Tell the player to move left.
	player->GetBox2DBody()->ApplyLinearImpulse(b2Vec2(-player->GetMovementSpeed(), 0), player->GetBox2DBody()->GetWorldCenter(), true);;
}

void
Game::MovePlayerRight(Player* player)
{
	player->GetBox2DBody()->ApplyLinearImpulse(b2Vec2(player->GetMovementSpeed(), 0), player->GetBox2DBody()->GetWorldCenter(), true);;
}

void
Game::StopPlayer(Player* player)
{
	// Linear damping currently controls bringing player to a stop
}

void
Game::PlayerDies(Player* player)
{
	int x = rand() % (5 - 1 +1);

	if (x == 4)
	{
		player->GetBox2DBody()->SetTransform(b2Vec2(160 / 10, 50 / 10), true);
	}
	else if (x == 3)
	{
		player->GetBox2DBody()->SetTransform(b2Vec2(608 / 10, 50 / 10), true);
	}
	else if (x == 2)
	{
		player->GetBox2DBody()->SetTransform(b2Vec2(160 / 10, 525 / 10), true);
	}
	else if (x == 1)
	{
		player->GetBox2DBody()->SetTransform(b2Vec2(608 / 10, 525 / 10), true);
	}
	else
	{
		player->GetBox2DBody()->SetTransform(b2Vec2(416 /10 , 316 / 10), true);
	}
}

void
Game::Jump(Player* player)
{
	// Only jump if currently in contact with another collision object.
	// Can currently jump off walls and other players.
	if (player->GetBox2DBody()->GetContactList() != 0)
	{
		player->GetBox2DBody()->ApplyLinearImpulse(b2Vec2(0, -player->GetJumpHeight()), player->GetBox2DBody()->GetWorldCenter(), true);

		m_pAudioManager->PlaySound(jumpSE);
	}
}

// Player abilities / combat
void
Game::Dash(Player* player, int xAxis, int yAxis)
{
	//Horizontal Dash
	if (xAxis > m_pInputHandler->GetJoystickDeadZone())
	{
		player->GetBox2DBody()->ApplyLinearImpulse(b2Vec2(player->GetDashSpeedX(), 0), player->GetBox2DBody()->GetWorldCenter(), true);
		m_pAudioManager->PlaySound(dashSE);
	}
	else if (xAxis < -m_pInputHandler->GetJoystickDeadZone())
	{
		player->GetBox2DBody()->ApplyLinearImpulse(b2Vec2(-player->GetDashSpeedX(), 0), player->GetBox2DBody()->GetWorldCenter(), true);
		m_pAudioManager->PlaySound(dashSE);
	}

	// Vertical Dash

	//if (yAxis > m_pInputHandler->GetJoystickDeadZone())
	//{
	//}
	//else if (yAxis < -m_pInputHandler->GetJoystickDeadZone())
	//{
	//}
}

void
Game::Punch(Player* player)
{
	m_pAudioManager->PlaySound(punchMissSE);
	
	// Test triggering players collision against all other players
	// IsCollidingWith checks player is not colliding with itself
	if (player->IsCollidingWith(*player0) && player0->GetState() != BLOCKING)
	{
		player->addScorePoint(1);	// Increment triggering players score
		//player0->GetBox2DBody()->SetTransform(b2Vec2(5, 5), true);	// Respawn killed player
		PlayerDies(player0);

		m_pAudioManager->PlaySound(punchSE);
	}
	if (player->IsCollidingWith(*player1) && player1->GetState() != BLOCKING)
	{
		player->addScorePoint(1);
		//player1->GetBox2DBody()->SetTransform(b2Vec2(5, 5), true);
		PlayerDies(player1);

		m_pAudioManager->PlaySound(punchSE);
	}
	if (player->IsCollidingWith(*player2) && player2->GetState() != BLOCKING)
	{
		player->addScorePoint(1);
		//player2->GetBox2DBody()->SetTransform(b2Vec2(5, 5), true);
		PlayerDies(player2);

		m_pAudioManager->PlaySound(punchSE);
	}
	if (player->IsCollidingWith(*player3) && player3->GetState() != BLOCKING)
	{
		player->addScorePoint(1);
		//player3->GetBox2DBody()->SetTransform(b2Vec2(5, 5), true);
		PlayerDies(player3);

		m_pAudioManager->PlaySound(punchSE);
	}
}

void
Game::Block(Player* player)
{
	//player->SetState(BLOCKING);
}

void
Game::MovePowerOrb(PowerOrb* powerOrb)
{

	powerOrb->GetBox2DBody()->ApplyLinearImpulse(b2Vec2(powerOrb->GetHorizontalVelocity(), powerOrb->GetVerticalVelocity()), powerOrb->GetBox2DBody()->GetWorldCenter(), true);
}

void
Game::CollideWithOrb(Player* player)
{
	if ((player->IsCollidingWithOrb(*powerOrb0) || player->IsCollidingWithOrb(*powerOrb1)) && player->GetState() != BLOCKING)
	{
		PlayerDies(player);
		m_pAudioManager->PlaySound(deathSE);
	}
}

// Level and collision creation
void
Game::LevelBuild()
{
	m_pLevelManager->CreateLevel(m_pBackBuffer, gameWorld);
}


// Currently Unused. Building of level moved to LevelManager

//void
//Game::LevelCollisionObject(float bodyDefPosX, float bodyDefPosY, float bodyShapeWidth, float bodyShapeHeight)
//{
//	b2BodyDef bodyDef;
//	bodyDef.position.Set(bodyDefPosX, bodyDefPosY);
//
//	b2Body* body = gameWorld->CreateBody(&bodyDef);
//
//	b2PolygonShape bodyShape;	// Collision shape
//	bodyShape.SetAsBox(bodyShapeWidth, bodyShapeHeight);
//
//	b2FixtureDef bodyFixture;	// Fixtures: Describe size, shape, and material properties
//	bodyFixture.shape = &bodyShape;
//	bodyFixture.friction = 1000;
//
//	body->CreateFixture(&bodyFixture);
//}

