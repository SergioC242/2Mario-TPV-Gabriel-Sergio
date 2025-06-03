#ifndef COLLISION_H
#define COLLISION_H

#include "checkML.h"

#pragma once
class Collision
{
public: 
	enum ObjetoTipo {
	None,
	Player,
	Tilemap,
	Block,
	Goomba,
	Koopa,
	Mushroom,
	Shell,
	moveShell,
	Coin,
	MovingPlatform
	};
enum CollisionDir {
	Above,
	Middle,
	Below
};

private:
	bool collision;
	CollisionDir dirV;
	ObjetoTipo tipo;

public:
	Collision() {
		collision = false;
		dirV = Middle;
		tipo = None;
	}
	Collision(bool c, CollisionDir d, ObjetoTipo t) {
		collision = c;
		dirV = d;
		tipo = t;
	}

	bool hasCollided() const { return collision; }
	CollisionDir directionV() const { return dirV; }
	ObjetoTipo object() const { return tipo; }
};

#endif