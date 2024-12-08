#include "MainMenuState.h"
#include "Game.h"




MainMenuState::MainMenuState(Game* g) : game(g)
{
	start = new Button(g, 100, 100, 1, 1, game->getTexture(Game::TXT_Lv1));
	start->connect([this]() { onClick(); });
	GameState::addObject(start);
	GameState::addEventListener(start);
}

void MainMenuState::render(){
	SDL_RenderClear(game->renderer);

	// Pinta los objetos del juego

	GameState::render();

	// Renderiza objetos del mapa

	SDL_RenderPresent(game->renderer);
}

void MainMenuState::onClick()
{
	game->statePlay(1);
}