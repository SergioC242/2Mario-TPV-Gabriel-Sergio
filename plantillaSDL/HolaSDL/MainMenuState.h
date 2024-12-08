
#include "GameState.h"
#include "Button.h"
#include "gameStateMachine.h"

class Game;

#pragma once
class MainMenuState : public GameState
{
private:
	Button* start1;
	Button* start2;
	Game* game;
public:
	MainMenuState(Game* g);
	virtual void render();
	void onClick(int w);

};

