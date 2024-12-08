#include "Button.h"
#include "GameState.h"

#pragma once
class PauseState : public GameState
{
private:
	Button pause;
	Game* game;
public:
	
	PauseState(Game* g): game(g), pause(game, 2, 2, 2, 2, nullptr) {
		//construir boton
		//pause = new Button(2, 2, 2, 2, nullptr, nullptr);
		pause.connect([this]() { onClick(); });
		
		
	}

	void onClick()
	{

	}

	

};

