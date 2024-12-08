#include "Button.h"
#include "GameState.h"

class Game;

#pragma once
class EndState : public GameState
{
private:
	Button* ex;
	Button* menu;
	Game* game;
public:
	EndState(Game* g);

	virtual void render();
	
	void onClickMen();
	void onClickEx();


};

