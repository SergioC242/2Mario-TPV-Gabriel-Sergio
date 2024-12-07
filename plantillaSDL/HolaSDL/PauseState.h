#include "Button.h"
#include "GameState.h"

#pragma once
class PauseState : public GameState
{
private:
	Button pause;
public:

	PauseState() {
		//addObject(new Button(100, 100, 200, 50, "Resume"));
		//addObject(new Button(100, 300, 200, 50, "Exit")); 
		pause.connect([this]() { onClick(); });
		
	}

	void onClick()
	{

	}

	

};

