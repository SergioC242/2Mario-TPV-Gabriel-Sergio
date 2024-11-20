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
	virtual void Update() {
		cout << "Fallo de polimorfismo en Update para GameItem";
	}

	virtual void Render() {
		cout << "Fallo de polimorfismo en Render para GameItem";
	}

	virtual void HandleEvents() {
		cout << "Fallo de polimorfismo en HandleEvents para GameItem";
	}

	virtual void Hit() {
		cout << "Fallo de polimorfismo en Hit para GameItem";
	}
};

#endif