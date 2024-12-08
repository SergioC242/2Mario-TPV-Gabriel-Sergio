#include "PauseState.h"
#include "Game.h"



PauseState::PauseState(Game* g) : game(g){
	//construir boton
	//pause = new Button(2, 2, 2, 2, nullptr, nullptr);

	pause = new Button(g, 200, 200, 1, 1, game->getTexture(Game::TXT_Lv1));
	pause->connect([this]() { onClick(); });
	GameState::addObject(pause);
	GameState::addEventListener(pause);

}

void PauseState::render() {
	SDL_RenderClear(game->renderer);

	// Pinta los objetos del juego

	GameState::render();

	// Renderiza objetos del mapa

	SDL_RenderPresent(game->renderer);
}

void PauseState::onClick()
{
	game->stateNotPause();
}
