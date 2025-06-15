#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "gameList.h"

#pragma once
using namespace std;

class Game;

class GameObject
{
private:
	Game* game;
	GameList<GameObject>::anchor listAnchor;
public:
	void setListAnchor(GameList<GameObject>::anchor a) { listAnchor = move(a); }

	virtual void update() = 0;

	virtual void render() const{
		//cout << "Fallo de polimorfismo en Render para GameItem" << endl;
	}

	virtual ~GameObject()
	{
		// El destructor del anchor se encargará del unlink automáticamente
	}
	// Método seguro para eliminar el objeto
	void destroy() {
		delete this; // Llama al destructor que maneja el anchor
	}
};

#endif