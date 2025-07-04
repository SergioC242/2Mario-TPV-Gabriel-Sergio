#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <iostream>
#include "Collision.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "gameList.h"

#pragma once
using namespace std;
class Game;


class SceneObject : public GameObject
{

protected:
	GameList<SceneObject>::anchor anchor;

	SDL_Rect rect;

public:

	SceneObject(){}
	SceneObject(const SceneObject&) {

	}

	void setListAnchor(GameList<SceneObject>::anchor&& anchor);

	virtual Collision hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {
		//cout << "Fallo de polimorfismo en Hit para GameItem" << endl;
		return Collision(false, Collision::CollisionDir::Middle, Collision::None);
	}

	virtual Point2D returnPos() {
		//cout << "Fallo de polimorfismo en returnPos para GameItem" << endl;
		return Point2D(0, 0);
	}
	virtual bool isActive() {
		//cout << "Fallo de polimorfismo en isActive para GameItem" << endl;
		return true;
	}

	virtual SceneObject* clone() const = 0;
};

#endif