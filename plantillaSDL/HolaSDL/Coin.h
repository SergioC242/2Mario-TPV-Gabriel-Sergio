#include "Vector2D.h"
#include "Texture.h"
#include "Pickable.h"
#include "Game.h"
#include "checkML.h"



#pragma once
class Coin : public Pickable
{
private:
	Vector2D<float> position;
	Texture* texture;
	Game* game;
	bool active;

public:
	Coin(Texture* tex, Game* g, int posX, int posY);
	Coin* clone() const { return new Coin(*this); }

	//~Coin();
	void update();
	void render() const;
	Collision hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj);
	Vector2D<float> returnPos() { return position; }
	bool isActive() { return active; }

};

