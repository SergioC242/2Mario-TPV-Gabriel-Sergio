#include "GameState.h"


void GameState::update() {
	for (GameObject* elem : gameObj) {
		elem->update();
	}
}

void GameState::render() {
	for (GameObject* elem : gameObj) {
		elem->render();
	}

}

void GameState::handleEvent(SDL_Event e) {
	for (EventHandler* elem : eventObj) {
		elem->handleEvent(e);
	}
}

void GameState::clearGameList(GameList<GameObject>& gameList)
{
	while (!gameList.empty()) {
		GameObject* obj = *gameList.begin();  // Obtenemos el primer elemento
		obj->destroy();  // Lo destruimos
		// El destructor se encarga de sacarlo de la lista
	}


}


