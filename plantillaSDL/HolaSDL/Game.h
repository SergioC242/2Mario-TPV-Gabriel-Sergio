#ifndef GAME_H
#define GAME_H

#include <array>
#include <vector>
#include <SDL.h>
#include "checkML.h"

#include "Texture.h"
#include "GameObject.h"
#include "SceneObject.h"
#include "TileMap.h"
#include "Player.h"
#include "gameList.h"

#pragma once

using uint = unsigned int;

class TileMap;
class Mushroom;
class Shell;
class Coin;

class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		Background,
		Blocks,
		SmallMario,
		SuperMario,
		FireMario,
		GoombaTex,
		KoopaTex,
		PiranhaTex,
		ShellTex,
		CoinTex,
		MushroomTex,
		Plant,
		Star,
		Lift,
		Numbers,
		NUM_TEXTURES
	};

private:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Interruptor para terminar el juego
	bool exit;

	// Datos del juego
	int world;
	int mapOffset;
	bool lockOffset;
	int score;
	Game* prevWorld;

	// Elementos del juego
	TileMap* tilemap;
	Player* player;

	//lista de objetos (gamelist)
	GameList<SceneObject> lista;
	vector<SceneObject*> createdItems;
	int objectVectorPos;

	// Objetos del juego
	//vector<SceneObject*> gameItems;
	//vector<SceneObject*> activeItems; //objetos que se spawnean

public:
	void run();

	void update();
	void render() const;
	void handleEvents();

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

	Texture* getTexture(TextureName name) const { return textures[name]; }
	TileMap* getTileMap() { return tilemap; }

	// Constante globales
	static constexpr uint WIN_WIDTH = 544;
	static constexpr uint WIN_HEIGHT = 480;
	static constexpr uint FRAME_RATE = 60;
	static constexpr uint TILE_SIZE = 32;

	Game(int worldN);
	~Game();
};

#endif