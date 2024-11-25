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
};

