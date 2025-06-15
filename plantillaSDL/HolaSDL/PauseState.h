#include "Button.h"
#include "GameState.h"



#pragma once
class PauseState : public GameState
{
private:
	Button* continuar;
	Button* menu;
	Button* ex;
	Game* game;
public:
	
	PauseState(Game* g);
	virtual void render();
	void onClickCont();
	void onClickMen();
	void onClickEx();
	//destructor
	virtual ~PauseState() {
	}

};

