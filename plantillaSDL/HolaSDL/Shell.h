#include "Vector2D.h"
#include "Texture.h"
#include "Pickable.h"
#include "Game.h"
#include "checkML.h"

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
	int hitCD;

public:
	static constexpr uint WALK_POWER = 16;
	static constexpr uint GRAVITY = 2;
	static constexpr uint MAX_FALL_SPEED = 8;

	Shell(Texture* tex, Game* g, int posX, int posY);
	Shell(const Shell&);
	Shell* clone() const { return new Shell(*this); }

	void update();
	void render();
	Collision hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj);
	Vector2D<float> returnPos() { return position; }
	 
	void startMove(bool dir);
	void stopMove() { moveX = 0; }
};

