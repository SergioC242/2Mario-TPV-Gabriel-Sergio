#include "MainMenuState.h"
#include "Game.h"




MainMenuState::MainMenuState(Game* g) : game(g)
{
	start1 = new Button(g, game->WIN_WIDTH / 2 - game->getTexture(Game::TXT_Lv1)->getFrameWidth() / 2, 100, 1, 1, game->getTexture(Game::TXT_Lv1));
	start1->connect([this]() { onClick(1); });
	GameState::addObject(start1);
	GameState::addEventListener(start1);

	start2 = new Button(g, game->WIN_WIDTH / 2 - game->getTexture(Game::TXT_Lv2)->getFrameWidth() / 2, 200, 1, 1, game->getTexture(Game::TXT_Lv2));
	start2->connect([this]() { onClick(2); });
	GameState::addObject(start2);
	GameState::addEventListener(start2);

	ex = new Button(g, game->WIN_WIDTH / 2 - game->getTexture(Game::TXT_Salir)->getFrameWidth() / 2, 300, 1, 1, game->getTexture(Game::TXT_Salir));
	ex->connect([this]() { onClickEx(); });
	GameState::addObject(ex);
	GameState::addEventListener(ex);
}

void MainMenuState::render(){
	SDL_RenderClear(game->renderer);

	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);

	// Pinta los objetos

	GameState::render();

	// Renderiza objetos

	SDL_RenderPresent(game->renderer);
}

void MainMenuState::onClick(int w)
{
	game->statePlay(w);
}

void MainMenuState::onClickEx() {
	game->gameExit();
}