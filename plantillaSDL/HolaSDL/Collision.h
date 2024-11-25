#ifndef COLLISION_H
#define COLLISION_H

#pragma once
class Collision
{
public: 
enum ObjetoTipo {
	None,
	Tilemap,
	Block,
	Goomba,
	Koopa,
	Mushroom,
	Shell
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

	bool hasCollided() { return collision; }
	CollisionDir directionV() { return dirV; }
	ObjetoTipo object() { return tipo; }
};

#endif