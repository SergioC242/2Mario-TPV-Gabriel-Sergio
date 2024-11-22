#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <iostream>
#include "Collision.h"
#include "Vector2D.h"

#include "SDL.h"
#include "SDL_image.h"

#pragma once
using namespace std;

class GameItem
{
private:
	enum Tipo {
		Block,
		Goomba,
		Koopa
	};

public:
	virtual void update() {
		cout << "Fallo de polimorfismo en Update para GameItem" << endl;
	}

	virtual void render() {
		cout << "Fallo de polimorfismo en Render para GameItem" << endl;
	}

	virtual void handleEvents() {
		cout << "Fallo de polimorfismo en HandleEvents para GameItem" << endl;
	}

	virtual Collision hit(SDL_Rect rect, bool fromPlayer) {
		cout << "Fallo de polimorfismo en Hit para GameItem" << endl;
		return Collision(false, Collision::CollisionDir::Middle, Collision::None);
	}

	virtual Point2D returnPos() {
		cout << "Fallo de polimorfismo en returnPos para GameItem" << endl;
		return Point2D(0, 0);
	}
};

#endif