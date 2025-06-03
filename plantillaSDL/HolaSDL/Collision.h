#ifndef COLLISION_H
#define COLLISION_H

#include "checkML.h"

class SceneObject;

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
	SceneObject* obj;

public:
	Collision() {
		collision = false;
		dirV = Middle;
		tipo = None;
	}
	Collision(bool c, CollisionDir d, ObjetoTipo t, SceneObject* o = nullptr) : obj(o) {
		collision = c;
		dirV = d;
		tipo = t;
	}

	bool hasCollided() const { return collision; }
	CollisionDir directionV() const { return dirV; }
	ObjetoTipo object() const { return tipo; }
	SceneObject* getObject() const { return obj; }
};

#endif