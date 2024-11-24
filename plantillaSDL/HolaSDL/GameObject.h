#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#pragma once
using namespace std;

class Game;

class GameObject
{
private:
	Game* game;
public:
	virtual void update() {
		cout << "Fallo de polimorfismo en Update para GameItem" << endl;
	}

	virtual void render() {
		cout << "Fallo de polimorfismo en Render para GameItem" << endl;
	}
};

#endif