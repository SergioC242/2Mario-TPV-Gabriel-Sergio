
#include "GameState.h"
#include "Button.h"
#include "gameStateMachine.h"

class Game;

#pragma once
class MainMenuState : public GameState
{
private:
	Button* start;
	Game* game;
public:
	MainMenuState(Game* g);
	void onClick();

};

