#include "Vector2D.h"
#include "Texture.h"
#include "Pickable.h"
#include "Game.h"


#pragma once
class Shell : public Pickable
{
private:
	Vector2D<float> position;
	bool dirIzq; //si no se esta moviendo a la izquierda se esta moviendo a la derecha
	bool moving;
	Texture* texture;
	Game* game;
	int moveX;
	int moveY;
	bool onGround;
	bool active;

public:
	static constexpr uint WALK_POWER = 4;
	static constexpr uint GRAVITY = 2;
	static constexpr uint MAX_FALL_SPEED = 8;

	Shell(Texture* tex, Game* g, int posX, int posY);
	void update();
	void render();
	Collision hit(SDL_Rect rect, bool fromPlayer);
	Vector2D<float> returnPos() { return position; }
};

