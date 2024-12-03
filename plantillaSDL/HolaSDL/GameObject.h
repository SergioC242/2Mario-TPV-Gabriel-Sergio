#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"

#pragma once
using namespace std;

class Game;

class GameObject
{
private:
	Game* game;
public:
	virtual void update() = 0;

	virtual void render() const{
		//cout << "Fallo de polimorfismo en Render para GameItem" << endl;
	}
};

#endif