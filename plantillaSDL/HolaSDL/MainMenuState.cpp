#include "MainMenuState.h"
#include "Game.h"



MainMenuState::MainMenuState(Game* g) : game(g), start(2, 2, 2, 2, game->getTexture(Game::TXT_Lv1), game->getTexture(Game::MushroomTex))
{
	start.connect([this]() { onClick(); });
}

void MainMenuState::onClick()
{
	game->statePlay();
}