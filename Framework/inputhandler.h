// COMP710 GP 2D Framework
#ifndef __INPUTHANDER_H__
#define __INPUTHANDER_H__

// Library includes:
#include <SDL.h>
#include "player.h"

// Forward Declarations:
class Game;

class InputHandler
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise();
	void ProcessInput(Game& game, Player* player0, Player* player1, Player* player2, Player* player3);

	int  GetJoystickDeadZone();

	int  GetXAxis(SDL_Joystick* gameController);
	int  GetYAxis(SDL_Joystick* gameController);

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);


	void ControlStick(Game& game, Player* player, SDL_Joystick* gameController);
	void ControlABXY(SDL_Event e, Game& game, Player* player, SDL_Joystick* gameController);
	void CheckPlayerMovement(Game& game, Player* player);

	//Member Data:
public:

protected:
	const int JOYSTICK_DEAD_ZONE;
	SDL_Joystick* m_pGameController0;
	SDL_Joystick* m_pGameController1;
	SDL_Joystick* m_pGameController2;
	SDL_Joystick* m_pGameController3;

private:

};

#endif // __INPUTHANDER_H__
