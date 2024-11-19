#pragma once

#include <array>
#include <vector>
#include <SDL.h>

#include "Texture.h"
#include "GameItem.h"
#include "TileMap.h"

using uint = unsigned int;

class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		Tilemap,
		Blocks,
		Mario,
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
	bool seguir;

	// Objetos del juego
	vector<GameItem*> gameItems;

public:
	void run();

	void update();
	void render() const;
	void handleEvents();

	Texture* getTexture(TextureName name) const;

	// Constante globales
	static constexpr uint WIN_WIDTH = 544;
	static constexpr uint WIN_HEIGHT = 480;
	static constexpr uint FRAME_RATE = 60;

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}
