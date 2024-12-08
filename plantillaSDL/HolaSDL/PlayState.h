#include "GameState.h"
#include "Player.h"
#include "TileMap.h"

#pragma once
class PlayState : public GameState
{
private:
	// Puntero a game
	Game* game;

	// Datos del juego
	int world;
	int mapOffset;
	bool lockOffset;
	int score;
	int vida;

	// Elementos del juego
	TileMap* tilemap;
	Player* storedPlayer;
	Player* player;

	//lista de objetos (gamelist)
	GameList<SceneObject> lista;
	vector<SceneObject*> createdItems;
	int objectVectorPos;

	// Objetos del juego
	//vector<SceneObject*> gameItems;
	//vector<SceneObject*> activeItems; //objetos que se spawnean

public:
	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event e);

	void loadMap(int worldN);
	void addVisibleObjects();
	Collision checkCollisions(SDL_Rect rect, Collision::ObjetoTipo tipoObj);
	void createMushrooms(int x, int y);
	void createShell(int x, int y);

	void map_reload();
	void map_next();

	int offset_Return() const;
	void offset_Add(int n);
	void offset_Lock();
	bool offset_isLocked() const;
	bool isSuperMario() { return player->isSuperMario(); }

	void addScore(int n);

	TileMap* getTileMap() { return tilemap; }

	PlayState(int worldN, Game* g);
	~PlayState();
};

