#ifndef COLLISION_H
#define COLLISION_H

#pragma once
class Collision
{
public: 
enum ObjetoTipo {
	Tilemap,
	Block,
	Goomba,
	Koopa
};

private:
	bool collision;
	int dirV; // -1 = below, 0 = middle, 1 = above
	ObjetoTipo tipo;

public:
	Collision(bool c, int d, ObjetoTipo t) {
		collision = c;
		dirV = d;
		tipo = t;
	}

	bool hasCollided() { return collision; }
	bool directionV() { return dirV; }
	ObjetoTipo object() { return tipo; }
};

#endif