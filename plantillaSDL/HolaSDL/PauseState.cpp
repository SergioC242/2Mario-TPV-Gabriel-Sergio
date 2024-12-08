#include "PauseState.h"
#include "Game.h"



PauseState::PauseState(Game* g) : game(g), pause(2, 2, 2, 2, game->getTexture(Game::TXT_Lv1), game->getTexture(Game::MushroomTex)) {
	//construir boton
	//pause = new Button(2, 2, 2, 2, nullptr, nullptr);
	pause.connect([this]() { onClick(); });


}

void PauseState::onClick()
{
	game->statePause();
}
