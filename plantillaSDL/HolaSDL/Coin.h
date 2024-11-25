#include "Vector2D.h"
#include "Texture.h"
#include "Pickable.h"
#include "Game.h"



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
	void update();
	void render();
	Collision hit(SDL_Rect rect, bool fromPlayer);
	Vector2D<float> returnPos() { return position; }

};

