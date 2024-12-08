#include "MainMenuState.h"
#include "Game.h"




MainMenuState::MainMenuState(Game* g) : game(g)
{
	start = new Button(g, 100, 100, 100, 100, game->getTexture(Game::TXT_Lv1));
	start->connect([this]() { onClick(); });
	GameState::addObject(start);
}

void MainMenuState::onClick()
{
	game->statePlay();
}