#include "Button.h"
#include "GameState.h"

#pragma once
class PauseState : public GameState
{
private:
	Button pause;
public:
	
	PauseState(): pause(2, 2, 2, 2, nullptr, nullptr){
		//construir boton
		//pause = new Button(2, 2, 2, 2, nullptr, nullptr);
		pause.connect([this]() { onClick(); });
		
		
	}

	void onClick()
	{

	}

	

};

