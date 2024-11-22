#ifndef COLLISION_H
#define COLLISION_H

#pragma once
class Collision
{
private:
	bool collision;
	int directionV; // -1 = below, 0 = middle, 1 = above

public:
	Collision(bool c, int dir) {
		collision = c;
		directionV = dir;
	}

	bool HasCollided() { return collision; }
	bool DirectionV() { return directionV; }
	//bool Object() { return /*object*/; }
};

#endif