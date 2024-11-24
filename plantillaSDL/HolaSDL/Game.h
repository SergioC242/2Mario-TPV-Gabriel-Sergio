#ifndef GAME_H
#define GAME_H

#include <array>
#include <vector>
#include <SDL.h>

#include "Texture.h"
#include "GameObject.h"
#include "SceneObject.h"
#include "TileMap.h"
#include "Player.h"

#pragma once

using uint = unsigned int;

class TileMap;

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
		Goomba,
		Koopa,
		Piranha,
		Shell,
		Mushroom,
		Plant,
		Star,
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
	int mapOffset;
	bool lockOffset;

	// Elementos del juego
	TileMap* tilemap;
	Player* player;

	// Objetos del juego
	vector<SceneObject*> gameItems;

public:
	void run();

	void update();
	void render() const;
	void handleEvents();

	void loadMap(int worldN);
	Collision checkCollisions(SDL_Rect rect, bool fromPlayer);

	int offset_Return();
	void offset_Add(int n);
	void offset_Lock();
	bool offset_isLocked();

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