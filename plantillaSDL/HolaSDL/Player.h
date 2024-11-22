#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "SDL_image.h"
#include <array>
#include <vector>
#include <SDL.h>


#pragma once

class Game;

using uint = unsigned int;

class Player
{
private:

	Point2D position;
	Game* game;
	int vidas;
	int currentWalkingFrame;
	enum Estado {
		Quieto,
		Caminando,
		Aire
	};
	enum Forma {
		Small,
		Super,
		Fire
	};
	Forma forma;
	Estado estado;
	std::array<Texture*, 3> textures;
	int moveX;
	int moveY;
	
	SDL_RendererFlip flipH;

	bool onGround;
	bool jumping;

public:
	static constexpr uint WALK_POWER = 8;
	static constexpr uint JUMP_POWER = 24; 
	static constexpr uint GRAVITY = 2;
	static constexpr uint MAX_FALL_SPEED = 8; //hay que comprobar si se queda que es negativo

	Player(Texture* tex1, Texture* tex2, Texture* tex3, Game* g, int posX, int posY, int lives);

	void handleEvent(SDL_KeyboardEvent& E);
	void update();
	void render();

	~Player();
};

