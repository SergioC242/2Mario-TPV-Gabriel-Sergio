#include "EndState.h"
#include "Game.h"



EndState::EndState(Game* g) : game(g) {
	//construir boton
	//pause = new Button(2, 2, 2, 2, nullptr, nullptr);

	menu = new Button(g, game->WIN_WIDTH / 2 - game->getTexture(Game::TXT_ReturnMenu)->getFrameWidth() / 2, 200, 1, 1, game->getTexture(Game::TXT_ReturnMenu));
	menu->connect([this]() { onClickMen(); });
	GameState::addObject(menu);
	GameState::addEventListener(menu);


	ex = new Button(g, game->WIN_WIDTH / 2 - game->getTexture(Game::TXT_Continue)->getFrameWidth() / 2, 300, 1, 1, game->getTexture(Game::TXT_Continue));
	ex->connect([this]() { onClickEx(); });
	GameState::addObject(ex);
	GameState::addEventListener(ex);

}

void EndState::render() {
	SDL_RenderClear(game->renderer);

	// Pinta los objetos del juego

	GameState::render();

	// Renderiza objetos del mapa

	SDL_RenderPresent(game->renderer);
}

void EndState::onClickMen() {
	game->stateMainMenu();
}

void EndState::onClickEx() {
	game->gameExit();
}