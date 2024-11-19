#pragma once

#include <array>
#include <SDL.h>

#include "Texture.h"
#include "GameItem.h"

using uint = unsigned int;

class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		Tilemap,
		Blocks,
		Mario,
		Goomba,
		Koopa,
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
	static constexpr uint WIN_WIDTH = 800;
	static constexpr uint WIN_HEIGHT = 600;
	static constexpr uint FRAME_RATE = 50;

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}
