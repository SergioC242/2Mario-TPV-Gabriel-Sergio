#ifndef GOOMBA_H
#define GOOMBA_H

#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"
#include "Game.h"
#include "checkML.h"

#pragma once
class TileMap;
class Goomba : public Enemy
{
private:
	Vector2D<float> position;
	bool dirIzq; //si no se esta moviendo a la izquierda se esta moviendo a la derecha
	Texture* texture;
	Game* game;
	int frame;
	int moveX;
	int moveY;
	bool alive;
	bool onGround;
	bool active;
	bool dead;

public: 
	static constexpr uint WALK_POWER = 4;
	static constexpr uint GRAVITY = 2;
	static constexpr uint MAX_FALL_SPEED = 8;

	Goomba(Texture* tex, Game* g, int posX, int posY);
	//~Goomba();
	void update();
	void render();
	Collision hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj);
	void die();
	Vector2D<float> returnPos() { return position; }
	bool isActive() { return active; }
};

#endif