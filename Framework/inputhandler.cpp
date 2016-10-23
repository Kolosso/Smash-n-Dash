// COMP710 GP 2D Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
: m_pGameController0(0)
, m_pGameController1(0)
, m_pGameController2(0)
, m_pGameController3(0)
, JOYSTICK_DEAD_ZONE(8000)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController0)
	{
		SDL_JoystickClose(m_pGameController0);
		m_pGameController0 = 0;
	}
	if (m_pGameController1)
	{
		SDL_JoystickClose(m_pGameController1);
		m_pGameController1 = 0;
	}
	if (m_pGameController2)
	{
		SDL_JoystickClose(m_pGameController2);
		m_pGameController2 = 0;
	}
	if (m_pGameController3)
	{
		SDL_JoystickClose(m_pGameController3);
		m_pGameController3 = 0;
	}
}

bool 
InputHandler::Initialise()
{
	SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_NOPARACHUTE);  // Uncertain if required...
	SDL_JoystickEventState(SDL_ENABLE);
	
	m_pGameController0 = SDL_JoystickOpen(0);
	m_pGameController1 = SDL_JoystickOpen(1);
	m_pGameController2 = SDL_JoystickOpen(2);
	m_pGameController3 = SDL_JoystickOpen(3);

	// Handle controllers being assigned in inverse order
	/*SDL_Joystick* *m_joysticks[4] = { &m_pGameController0, &m_pGameController1, &m_pGameController2, &m_pGameController3 };*/
	//SDL_JoystickID
	//SDL_JoystickInstanceID
	
	                 // Uncertain if required...

	//int numControllers = SDL_NumJoysticks();
	//int c = 0;

	//for (int i = numControllers; i > 0; i--)
	//{
	//	*m_joysticks[c] = SDL_JoystickOpen(i-1);
	//	c++;
	//}

	//assert(m_pGameController0);
	//assert(m_pGameController1);
	//assert(m_pGameController2);
	//assert(m_pGameController3);

	return (true);
}

void 
InputHandler::ProcessInput(Game& game, Player* player0, Player* player1, Player* player2, Player* player3)
{
	SDL_JoystickUpdate();  // Uncertain if required...

	// Check movement for each player
	ControlStick(game, player0, m_pGameController0);
	ControlStick(game, player1, m_pGameController1);
	ControlStick(game, player2, m_pGameController2);
	ControlStick(game, player3, m_pGameController3);

	// Handle button press events
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.type == SDL_JOYBUTTONDOWN)
		{
			// Controller 1
			if (e.jaxis.which == SDL_JoystickInstanceID(m_pGameController0))
			{
				ControlABXY(e, game, player0, m_pGameController0);
			}
			// Controller 2
			else if (e.jaxis.which == SDL_JoystickInstanceID(m_pGameController1))
			{
				ControlABXY(e, game, player1, m_pGameController1);
			}
			// Controller 3
			if (e.jaxis.which == SDL_JoystickInstanceID(m_pGameController2))
			{
				ControlABXY(e, game, player2, m_pGameController2);
			}
			// Controller 4
			else if (e.jaxis.which == SDL_JoystickInstanceID(m_pGameController3))
			{
				ControlABXY(e, game, player3, m_pGameController3);
			}
		}
		// Keyboard controls
		else if (e.type == SDL_KEYDOWN)
		{
			// Restart Game
			if (e.key.keysym.sym == SDLK_F5) {
				game.NewGame();
			}
			// Quit Game
			if (e.key.keysym.sym == SDLK_F8) {
				game.Quit();
			}
			if (e.key.keysym.sym == SDLK_F1) {
				player0->SetState(BLOCKING);
			}
			if (e.key.keysym.sym == SDLK_F2) {
				player1->SetState(BLOCKING);
			}
			if (e.key.keysym.sym == SDLK_F3) {
				player2->SetState(BLOCKING);
			}
			if (e.key.keysym.sym == SDLK_F4) {
				player3->SetState(BLOCKING);
			}
			// Audio volume UP
			if (e.key.keysym.sym == SDLK_EQUALS) {
				game.VolumeAdjust(true);
			}
			// Audio volume DOWN
			if (e.key.keysym.sym == SDLK_MINUS) {
				game.VolumeAdjust(false);
			}
			//// Player 1
			//if (e.key.keysym.sym == SDLK_LEFT) {
			//	game.MovePlayerLeft(player0);
			//}
			//if (e.key.keysym.sym == SDLK_RIGHT) {
			//	game.MovePlayerRight(player0);
			//}
			//if (e.key.keysym.sym == SDLK_UP) {
			//	game.Jump(player0);
			//}
			//if (e.key.keysym.sym == SDLK_RALT)
			//{
			//	game.Punch(player0);
			//}
			//if (e.key.keysym.sym == SDLK_RCTRL)
			//{
			//	game.Block(player0);
			//}
			//// Player 2
			//if (e.key.keysym.sym == SDLK_a) {
			//	game.MovePlayerLeft(player1);
			//}
			//if (e.key.keysym.sym == SDLK_d) {
			//	game.MovePlayerRight(player1);
			//}
			//if (e.key.keysym.sym == SDLK_w) {
			//	game.Jump(player1);
			//}
			//if (e.key.keysym.sym == SDLK_w) {
			//	game.Jump(player1);
			//}
			//if (e.key.keysym.sym == SDLK_c)
			//{
			//	game.Punch(player1);
			//}
			//if (e.key.keysym.sym == SDLK_v)
			//{
			//	game.Block(player1);
			//}
		}
	}
}

// Check Joystick position of given controller. Move character
void
InputHandler::ControlStick(Game& game, Player* player, SDL_Joystick* gameController)
{
	// Stop player movement if Joystick is within JOYSTICK_DEAD_ZONE
	if (GetXAxis(gameController) <= JOYSTICK_DEAD_ZONE && GetXAxis(gameController) >= -JOYSTICK_DEAD_ZONE)
	{
		game.StopPlayer(player);
	}
	if (GetXAxis(gameController) > JOYSTICK_DEAD_ZONE)
	{
		game.MovePlayerRight(player);
	}
	if (GetXAxis(gameController) < -JOYSTICK_DEAD_ZONE)
	{
		game.MovePlayerLeft(player);
	}
}

void
InputHandler::ControlABXY(SDL_Event e, Game& game, Player* player, SDL_Joystick* gameController)
{
	// Jump
	if (e.jbutton.button == 10 ) // A
	{
		game.Jump(player);
	}
	// Punch
	if (e.jbutton.button == 11) // B
	{
		game.Punch(player);
	}
	// Dash
	if (e.jbutton.button == 12) // X
	{
		game.Dash(player, GetXAxis(gameController), GetYAxis(gameController));
	}
	// Block
	if (e.jbutton.button == 13) // Y
	{
		game.Block(player);
	}
}

int
InputHandler::GetJoystickDeadZone()
{
	return JOYSTICK_DEAD_ZONE;
}

int
InputHandler::GetXAxis(SDL_Joystick* gameController)
{
	return SDL_JoystickGetAxis(gameController, 0);
}

int
InputHandler::GetYAxis(SDL_Joystick* gameController)
{
	return SDL_JoystickGetAxis(gameController, 1);
}