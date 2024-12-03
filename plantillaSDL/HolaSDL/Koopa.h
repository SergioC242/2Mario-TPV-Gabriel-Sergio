#ifndef KOOPA_H
#define KOOPA_H

#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"
#include "Game.h"
#include "Shell.h"
#include "checkML.h"

#pragma once
class TileMap;
class Koopa : public Enemy
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
	bool inShell;
	bool onGround;
	bool active;

public:
	static constexpr uint WALK_POWER = 4;
	static constexpr uint GRAVITY = 2;
	static constexpr uint MAX_FALL_SPEED = 8;

	Koopa(Texture* tex, Game* g, int posX, int posY);
	Koopa* clone() const { return new Koopa(*this); }

	void update();
	void render() const;
	Collision hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj);
	void die();
	Vector2D<float> returnPos() { return position; }
};

#endif