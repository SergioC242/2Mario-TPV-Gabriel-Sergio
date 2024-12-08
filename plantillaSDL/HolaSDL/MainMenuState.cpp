#include "MainMenuState.h"
#include "Game.h"



MainMenuState::MainMenuState(Game* g) : game(g)
{
	start = new Button(g, 2, 2, 2, 2, game->getTexture(Game::TXT_Lv1));
	start->connect([this]() { onClick(); });
}

void MainMenuState::onClick()
{
	game->statePlay();
}