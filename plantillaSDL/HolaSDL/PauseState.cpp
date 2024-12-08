#include "PauseState.h"
#include "Game.h"



PauseState::PauseState(Game* g) : game(g){
	//construir boton
	//pause = new Button(2, 2, 2, 2, nullptr, nullptr);
	pause = new Button(g, 100, 100, 1, 1, game->getTexture(Game::TXT_Lv1));
	pause->connect([this]() { onClick(); });


}

void PauseState::onClick()
{
	game->statePause();
}
