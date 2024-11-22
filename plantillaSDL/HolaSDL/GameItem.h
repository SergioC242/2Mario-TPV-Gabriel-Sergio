#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <iostream>

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

	virtual void hit() {
		cout << "Fallo de polimorfismo en Hit para GameItem" << endl;
	}
};

#endif