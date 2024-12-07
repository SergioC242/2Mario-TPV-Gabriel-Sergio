#include "GameState.h"
#include "Player.h"

#pragma once
class PlayState : public GameState
{
private:
	GameList<SceneObject> sceneObjects;
	int mapOffset;
	bool lockOffset;
	int score;

public:
	void loadMap(int worldN) {
		
	}

	void addVisibleObjects() {

	}

	Collision checkCollisions(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {

	}

	void createMushrooms(int x, int y) {

	}

	void createShell(int x, int y) {

	}

	void map_reload() {

	}

	void map_next() {

	}

	int offset_Return() const { return mapOffset; }


	void offset_Add(int n) {
		if (!lockOffset) {
			mapOffset += n;
		}
	}

	void offset_Lock() { lockOffset = true; }

	bool offset_isLocked() const { return lockOffset; }

	bool isSuperMario() { return player->isSuperMario(); }

	void addScore(int n) { score += n; }

};

