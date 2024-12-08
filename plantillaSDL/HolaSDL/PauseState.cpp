#include "PauseState.h"
#include "Game.h"



PauseState::PauseState(Game* g) : game(g){
	//construir boton
	//pause = new Button(2, 2, 2, 2, nullptr, nullptr);

	
	continuar = new Button(g, game->WIN_WIDTH/2 - game->getTexture(Game::TXT_Continue)->getFrameWidth()/2, 100, 1, 1, game->getTexture(Game::TXT_Continue));
	continuar->connect([this]() { onClickCont(); });
	GameState::addObject(continuar);
	GameState::addEventListener(continuar);

	menu = new Button(g, game->WIN_WIDTH / 2 - game->getTexture(Game::TXT_ReturnMenu)->getFrameWidth() / 2, 200, 1, 1, game->getTexture(Game::TXT_ReturnMenu));
	menu->connect([this]() { onClickMen(); });
	GameState::addObject(menu);
	GameState::addEventListener(menu);

	ex = new Button(g, game->WIN_WIDTH / 2 - game->getTexture(Game::TXT_Salir)->getFrameWidth() / 2, 300, 1, 1, game->getTexture(Game::TXT_Salir));
	ex->connect([this]() { onClickEx(); });
	GameState::addObject(ex);
	GameState::addEventListener(ex);

}

void PauseState::render() {
	SDL_RenderClear(game->renderer);

	// Pinta los objetos del juego

	GameState::render();

	// Renderiza objetos del mapa

	SDL_RenderPresent(game->renderer);
}

void PauseState::onClickCont()
{
	game->stateNotPause();
}

void PauseState::onClickMen()
{
	game->stateMainMenu();
}

void PauseState::onClickEx() {
	game->gameExit();
}
