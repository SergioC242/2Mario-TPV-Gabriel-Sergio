#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "SDL_image.h"


class Game;

#pragma once


using uint = unsigned int;

class Player
{
private:
	Point2D position;
	Texture* texture;
	Game* game;
	int vidas;
	int currentWalkingFrame;
	enum class Estado {
		Quieto,
		Caminando,
		Aire
	};
	enum class Forma {
		Mario,
		Super
	};
	Forma forma;
	Estado estado;
	int moveX;
	int moveY;
	
	SDL_RendererFlip flipH;

	bool onGround;

public:
	static constexpr uint walkPower = 8;
	static constexpr uint jumpPower = 24; 
	static constexpr uint gravity = 2;
	static constexpr uint maxVerticalDown = -8; //hay que comprobar si se queda que es negativo



};

