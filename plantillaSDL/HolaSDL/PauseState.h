#include "Button.h"
#include "GameState.h"

#pragma once
class PauseState : public GameState
{
private:
	Button pause;
	Game* game;
public:
	
	PauseState(Game* g);

	void onClick();

	

};

